#ifndef CBOOKMARKS_LIB_H
#define CBOOKMARKS_LIB_H

#include <CHtmlLib.h>

class CBookmark;
class CBookmarkGroup;

class CBookmarkFile {
 public:
  CBookmarkFile(const std::string &filename);
 ~CBookmarkFile();

  bool isIgnoreDuplicates() const { return ignoreDuplicates_; }
  void setIgnoreDuplicates(bool b) { ignoreDuplicates_ = b; }

  CBookmarkGroup *getGroup() const { return topGroup_; }

  bool read();

  bool append(const CBookmarkFile &file);

  void sort();

  void printHtml(std::ostream &os = std::cout) const;

  void printMarkdown(std::ostream &os = std::cout) const;

  void dump(std::ostream &os = std::cout) const;

  time_t lastModified() const;

 private:
  struct CacheData {
    std::string linkName;
    std::string linkValue;
    time_t      lastModified { 0 };
  };

  std::string     filename_;
  bool            ignoreDuplicates_ { false };
  bool            inHeader_         { false };
  time_t          lastModified_     { 0 };
  bool            inLink_           { false };
  CBookmarkGroup *topGroup_         { nullptr };
  CacheData       cacheData_;
};

//------

class CBookmarkGroup {
 public:
  typedef std::list<CBookmarkGroup *> GroupList;
  typedef GroupList::iterator         group_iterator;
  typedef std::list<CBookmark *>      BookmarkList;
  typedef BookmarkList::iterator      bookmark_iterator;

 public:
  CBookmarkGroup(CBookmarkFile *parentFile=nullptr);

  CBookmarkGroup(CBookmarkGroup *parentGroup=nullptr, const std::string &name="");

  CBookmarkFile *parentFile() const;

  CBookmarkGroup *parentGroup() const { return parentGroup_; }

  const std::string &getName() const { return name_; }

  CBookmarkGroup *getGroup(const std::string &name) const;

  CBookmarkGroup *addGroup(const std::string &name);

  CBookmarkGroup *addGroup(const CBookmarkGroup &group);

  CBookmark *addBookmark(const std::string &name, const std::string &url);

  CBookmark *addBookmark(const CBookmark &bookmark);

  CBookmark *findUrl(const std::string &url) const;

  std::string getPath() const;

  bool append(const CBookmarkGroup &group);

  void printHtml(std::ostream &os = std::cout) const;

  void printMarkdown(std::ostream &os = std::cout) const;

  void dump(std::ostream &os = std::cout) const;

  void sort();

  group_iterator groupsBegin() { return groups_.begin(); }
  group_iterator groupsEnd  () { return groups_.end  (); }

  bookmark_iterator bookmarksBegin() { return bookmarks_.begin(); }
  bookmark_iterator bookmarksEnd  () { return bookmarks_.end  (); }

  friend bool operator<(const CBookmarkGroup &a, const CBookmarkGroup &b) {
    return (a.name_ < b.name_);
  }

  time_t lastModified() const;

 private:
  uint getDepth() const;

 private:
  CBookmarkGroup(const CBookmarkGroup &group);
  CBookmarkGroup &operator=(const CBookmarkGroup &group);

 private:
  CBookmarkFile  *parentFile_  { nullptr };
  CBookmarkGroup *parentGroup_ { nullptr };
  std::string     name_;
  GroupList       groups_;
  BookmarkList    bookmarks_;
};

//------

class CBookmark {
 public:
  CBookmark(const std::string &name, const std::string &url) :
   name_(name), url_(url) {
  }

  CBookmark(const CBookmark &bookmark) :
    group_(bookmark.group_), name_(bookmark.name_), url_(bookmark.url_) {
  }

  CBookmarkGroup *getGroup() const { return group_; }
  void setGroup(CBookmarkGroup *group) { group_ = group; }

  const std::string &getName() const { return name_; }

  const std::string &getUrl() const { return url_; }

  time_t lastModified() const { return lastModified_; }
  void setLastModified(time_t v) { lastModified_ = v; }

  void sort();

  void printHtml(std::ostream &os = std::cout) const;

  void printMarkdown(std::ostream &os = std::cout) const;

  void dump(std::ostream &os = std::cout) const;

  friend bool operator<(const CBookmark &a, const CBookmark &b) {
    return (a.name_ < b.name_);
  }

 private:
  CBookmarkGroup *group_        { nullptr };
  std::string     name_;
  std::string     url_;
  time_t          lastModified_ { 0 };
};

#endif
