#include <CBookmarksLib.h>
#include <CUrl.h>
#include <CStrUtil.h>

class CBookmarkGroupCmp {
 public:
  bool operator()(const CBookmarkGroup *group1, const CBookmarkGroup *group2);
};

class CBookmarkCmp {
 public:
  bool operator()(const CBookmark *bookmark1, const CBookmark *bookmark2);
};

//---------------------

CBookmarkFile::
CBookmarkFile(const std::string &filename) :
 filename_(filename)
{
  topGroup_ = new CBookmarkGroup(this);
}

CBookmarkFile::
~CBookmarkFile()
{
}

bool
CBookmarkFile::
read()
{
  CHtml html;

  CHtmlParserTokens tokens;

  if (! html.read(filename_, tokens))
    return false;

  inLink_   = false;
  inHeader_ = false;

  CBookmarkGroup *currentGroup = topGroup_;

  for (const auto &token : tokens) {
    if      (token->isText()) {
      if (! inLink_ && ! inHeader_)
        continue;

      CHtmlText *text = token->getText();

      std::string str = text->getText();

      if (inLink_) {
        cacheData_.linkName = str;
      }
      else {
        CBookmarkGroup *group = currentGroup->getGroup(str);

        if (! group)
          currentGroup = currentGroup->addGroup(str);
        else
          currentGroup = group;
      }
    }
    else if (token->isTag()) {
      CHtmlTag *tag = token->getTag();

      const CHtmlTagDef &tagDef = tag->getTagDef();

      CHtmlTagId id = tagDef.getId();

      if      (id == CHtmlTagId::A) {
        if (tag->isStartTag()) {
          cacheData_.linkValue    = "";
          cacheData_.lastModified = static_cast<time_t>(0);

          for (const auto &option : tag->getOptions()) {
            std::string optName = CStrUtil::toLower(option->getName());

            if      (optName == "href") {
              cacheData_.linkValue = option->getValue();

              inLink_ = true;
            }
            else if (optName == "last_modified") {
              int ti = std::stoi(option->getValue());

              cacheData_.lastModified = static_cast<time_t>(ti);
            }
          }
        }
        else {
          if (cacheData_.linkValue != "") {
            std::string linkValue = CUrl::replaceSpecialChars(cacheData_.linkValue);

            while (linkValue.size() > 0 && linkValue[linkValue.size() -1] == '/')
              linkValue = linkValue.substr(0, linkValue.size() - 1);

            CBookmark *bookmark = topGroup_->findUrl(linkValue);

            if (! bookmark) {
              bookmark = currentGroup->addBookmark(cacheData_.linkName, linkValue);
            }
            else {
              if (! isIgnoreDuplicates()) {
                std::cerr << "Duplicate Bookmark for " <<
                             currentGroup->getPath() << "/" << linkValue << " - ";
                std::cerr << "already in " << bookmark->getGroup()->getPath() << "\n";
              }
            }

            bookmark->setLastModified(std::max(bookmark->lastModified(), cacheData_.lastModified));
          }

          cacheData_.linkName  = "";
          cacheData_.linkValue = "";

          inLink_ = false;
        }
      }
      else if (id == CHtmlTagId::H1) {
        if (tag->isStartTag()) {
          for (const auto &option : tag->getOptions()) {
            std::string optName = CStrUtil::toLower(option->getName());

            if (optName == "last_modified") {
              int ti = std::stoi(option->getValue());

              lastModified_ = std::max(lastModified_, static_cast<time_t>(ti));
            }
          }
        }
      }
      else if (id == CHtmlTagId::H3) {
        if (tag->isStartTag()) {
          inHeader_ = true;

          for (const auto &option : tag->getOptions()) {
            std::string optName = CStrUtil::toLower(option->getName());

            if (optName == "last_modified") {
              int ti = std::stoi(option->getValue());

              lastModified_ = std::max(lastModified_, static_cast<time_t>(ti));
            }
          }
        }
        else
          inHeader_ = false;
      }
      else if (id == CHtmlTagId::OL || id == CHtmlTagId::UL || id == CHtmlTagId::DL) {
        if (tag->isEndTag()) {
          currentGroup = currentGroup->parentGroup();

          if (! currentGroup)
            currentGroup = topGroup_;
        }
      }
    }
  }

  return true;
}

bool
CBookmarkFile::
append(const CBookmarkFile &file)
{
  if (! file.topGroup_)
    return true;

  if (! topGroup_) {
    topGroup_ = new CBookmarkGroup(file.topGroup_);

    return true;
  }

  return topGroup_->append(*file.topGroup_);
}

void
CBookmarkFile::
sort()
{
  if (topGroup_)
    topGroup_->sort();
}

void
CBookmarkFile::
printHtml(std::ostream &os) const
{
  if (topGroup_)
    topGroup_->printHtml(os);
}

void
CBookmarkFile::
printMarkdown(std::ostream &os) const
{
  if (topGroup_)
    topGroup_->printMarkdown(os);
}

void
CBookmarkFile::
dump(std::ostream &os) const
{
  if (topGroup_)
    topGroup_->dump(os);
}

time_t
CBookmarkFile::
lastModified() const
{
  time_t lastModified = lastModified_;

  if (topGroup_)
    lastModified = std::max(lastModified, topGroup_->lastModified());

  return lastModified;
}

//----------------------------

CBookmarkGroup::
CBookmarkGroup(CBookmarkFile *parentFile) :
 parentFile_(parentFile)
{
}

CBookmarkGroup::
CBookmarkGroup(CBookmarkGroup *parentGroup, const std::string &name) :
 parentGroup_(parentGroup), name_(name)
{
}

CBookmarkFile *
CBookmarkGroup::
parentFile() const
{
  if (! parentFile_)
    return parentGroup_->parentFile();

  return parentFile_;
}

CBookmarkGroup *
CBookmarkGroup::
getGroup(const std::string &name) const
{
  for (const auto &group : groups_) {
    if (group->name_ == name)
      return group;
  }

  return nullptr;
}

CBookmarkGroup *
CBookmarkGroup::
addGroup(const std::string &name)
{
  CBookmarkGroup *group = new CBookmarkGroup(this, name);

  groups_.push_back(group);

  return group;
}

CBookmarkGroup *
CBookmarkGroup::
addGroup(const CBookmarkGroup &group)
{
  CBookmarkGroup *group1 = new CBookmarkGroup(this);

  group1->append(group);

  groups_.push_back(group1);

  return group1;
}

CBookmark *
CBookmarkGroup::
addBookmark(const std::string &name, const std::string &url)
{
  CBookmark *bookmark = new CBookmark(name, url);

  bookmarks_.push_back(bookmark);

  bookmark->setGroup(this);

  return bookmark;
}

CBookmark *
CBookmarkGroup::
addBookmark(const CBookmark &bookmark)
{
  CBookmark *bookmark1 = new CBookmark(bookmark);

  bookmarks_.push_back(bookmark1);

  bookmark1->setGroup(this);

  return bookmark1;
}

CBookmark *
CBookmarkGroup::
findUrl(const std::string &url) const
{
  for (const auto &group : groups_) {
    CBookmark *bookmark = group->findUrl(url);

    if (bookmark)
      return bookmark;
  }

  for (const auto &bookmark : bookmarks_) {
    if (url == bookmark->getUrl())
      return bookmark;
  }

  return nullptr;
}

std::string
CBookmarkGroup::
getPath() const
{
  if (! parentGroup())
    return name_;

  return parentGroup()->getPath() + "/" + name_;
}

bool
CBookmarkGroup::
append(const CBookmarkGroup &group)
{
  for (const auto &ggroup : group.groups_) {
    CBookmarkGroup *group1 = getGroup(ggroup->getName());

    if (! group1)
      addGroup(*ggroup);
  }

  for (const auto &bookmark : group.bookmarks_) {
    CBookmark *bookmark1 = findUrl(bookmark->getUrl());

    if (! bookmark1)
      addBookmark(*bookmark);
  }

  return true;
}

void
CBookmarkGroup::
sort()
{
  groups_.sort(CBookmarkGroupCmp());

  for (const auto &group : groups_)
    group->sort();

  bookmarks_.sort(CBookmarkCmp());
}

void
CBookmarkGroup::
printHtml(std::ostream &os) const
{
  CBookmarkFile *parentFile = this->parentFile();

  uint depth = getDepth();

  if (depth > 0) {
    std::cout << "<h" << depth + 1 << ">" << name_ << "</h" << depth + 1 << ">\n";
    std::cout << "<ul>\n";
  }

  for (const auto &group : groups_)
    group->printHtml(os);

  std::string url;
  std::string last_url;

  for (const auto &bookmark : bookmarks_) {
    url = bookmark->getUrl();

    if (url != last_url)
      bookmark->printHtml(os);
    else {
      if (! parentFile->isIgnoreDuplicates())
        std::cerr << "Duplicate url " << last_url << "\n";
    }

    last_url = url;
  }

  if (depth > 0) {
    std::cout << "</ul>\n";
  }
}

void
CBookmarkGroup::
printMarkdown(std::ostream &os) const
{
  CBookmarkFile *parentFile = this->parentFile();

  uint depth = getDepth();

  if (depth > 0) {
    std::string hashStr = "#";

    for (uint i = 0; i < depth; ++i)
      hashStr += "#";

    std::cout << hashStr << " " << name_ << " " << hashStr << "\n";
  }

  for (const auto &group : groups_)
    group->printMarkdown(os);

  std::string url;
  std::string last_url;

  for (const auto &bookmark : bookmarks_) {
    url = bookmark->getUrl();

    if (url != last_url)
      bookmark->printMarkdown(os);
    else {
      if (! parentFile->isIgnoreDuplicates())
        std::cerr << "Duplicate url " << last_url << "\n";
    }

    last_url = url;
  }
}

void
CBookmarkGroup::
dump(std::ostream &os) const
{
  for (const auto &group : groups_)
    group->dump(os);

  for (const auto &bookmark : bookmarks_)
    bookmark->dump(os);
}

uint
CBookmarkGroup::
getDepth() const
{
  if (parentGroup())
    return parentGroup()->getDepth() + 1;

  return 0;
}

time_t
CBookmarkGroup::
lastModified() const
{
  time_t t = 0;

  for (const auto &group : groups_)
    t = std::max(t, group->lastModified());

  for (const auto &bookmark : bookmarks_)
    t = std::max(t, bookmark->lastModified());

  return t;
}

//------------------

void
CBookmark::
printHtml(std::ostream &os) const
{
  os << "<li><a href=\"" << url_ << "\">" << name_ << "</a></li>\n";
}

void
CBookmark::
printMarkdown(std::ostream &os) const
{
  os << " + [" << name_ << "](" << url_ << ")\n";
}

void
CBookmark::
dump(std::ostream &os) const
{
  std::string url = CUrl::replaceSpecialChars(url_);

  while (url.size() > 0 && url[url.size() -1] == '/')
    url = url.substr(0, url.size() - 1);

  std::string path = group_->getPath();

  os << "\"" << url << "\"";

  if (path != "")
    os << " \"" << path << "\"";

  if (name_ != "")
    os << " \"" << name_ << "\"";

  os << "\n";
}

//------------------

bool
CBookmarkGroupCmp::
operator()(const CBookmarkGroup *group1, const CBookmarkGroup *group2)
{
  return (group1->getName() < group2->getName());
}

bool
CBookmarkCmp::
operator()(const CBookmark *bookmark1, const CBookmark *bookmark2)
{
  return (bookmark1->getName() < bookmark2->getName());
}
