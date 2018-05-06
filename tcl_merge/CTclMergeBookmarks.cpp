#include <CTclApp.h>
#include <CTclAppCommand.h>

#undef INLINE

#include <CBookmarksLib.h>
#include <CTclMergeBookmarks.h>

#include <CTclMergeBookmarks.k>

#define CTclMergeBookmarksAppCommand(N) \
class N : public CTclAppCommand { \
 private: \
  CTclMergeBookmarks *bookmarks_; \
\
 public: \
  N(CTclMergeBookmarks *bookmarks) : \
    CTclAppCommand(bookmarks, #N), bookmarks_(bookmarks) { \
  } \
\
 protected: \
  bool proc(int argc, const char **argv); \
};

CTclMergeBookmarksAppCommand(CTclMergeBookmarksAddItems1)
CTclMergeBookmarksAppCommand(CTclMergeBookmarksAddItems2)
CTclMergeBookmarksAppCommand(CTclMergeBookmarksHighlight)

int
main(int argc, char **argv)
{
  CTclMergeBookmarks app(argc, argv);
}

CTclMergeBookmarks::
CTclMergeBookmarks(int argc, char **argv) :
 CTclApp(argc, argv), file1_(NULL), file2_(NULL)
{
  init();
}

CTclMergeBookmarks::
~CTclMergeBookmarks()
{
}

void
CTclMergeBookmarks::
addCommands()
{
  new CTclMergeBookmarksAddItems1(this);
  new CTclMergeBookmarksAddItems2(this);
  new CTclMergeBookmarksHighlight(this);
}

std::string
CTclMergeBookmarks::
getTclStr()
{
  return CTclMergeBookmarks_TK;
}

void
CTclMergeBookmarks::
addItems(int num, const std::string &path, CBookmarkGroup *group)
{
  if (path.size() > 0) {
    eval("CTclMergeBookmarksAddGroup%d {%s} {%s}",
         num, path.c_str(), group->getName().c_str());

    group_path_[group] = path;
  }

  CBookmarkGroup::group_iterator pgroup1 = group->groupsBegin();
  CBookmarkGroup::group_iterator pgroup2 = group->groupsEnd  ();

  for ( ; pgroup1 != pgroup2; ++pgroup1) {
    std::string path1 = path;

    if (path.size() > 0)
      path1 += "^";

    path1 += (*pgroup1)->getName();

    addItems(num, path1, *pgroup1);
  }

  CBookmarkGroup::bookmark_iterator pbookmark1 = group->bookmarksBegin();
  CBookmarkGroup::bookmark_iterator pbookmark2 = group->bookmarksEnd  ();

  for ( ; pbookmark1 != pbookmark2; ++pbookmark1)
    addItem(num, path, *pbookmark1);

  if (path.size() > 0)
    eval("CTclMergeBookmarksCloseGroup%d {%s}",
         num, path.c_str());
}

void
CTclMergeBookmarks::
addItem(int num, const std::string &path, CBookmark *bookmark)
{
  std::string path1 = path;

  if (path.size() > 0)
    path1 += "^";

  path1 += bookmark->getName();
  path1 += " ";
  path1 += bookmark->getUrl();

  eval("CTclMergeBookmarksAddItem%d {%s} {%s} {%s}",
       num, path1.c_str(), bookmark->getName().c_str(),
       bookmark->getUrl().c_str());

  bookmark_path_[bookmark] = path1;
}

void
CTclMergeBookmarks::
highlight()
{
  CBookmarkGroup *group1 = file1_->getGroup();
  CBookmarkGroup *group2 = file2_->getGroup();

  highlightGroups(group1, group2, "CTclMergeBookmarksSetGroupColor1");
  highlightGroups(group2, group1, "CTclMergeBookmarksSetGroupColor2");

  highlightBookmarks(group1, group2, "CTclMergeBookmarksSetBookmarkColor1");
//highlightBookmarks(group2, group1, "CTclMergeBookmarksSetBookmarkColor2");
}

void
CTclMergeBookmarks::
highlightGroups(CBookmarkGroup *group1, CBookmarkGroup *group2, const char *proc)
{
  CBookmarkGroup::group_iterator pgroup1 = group1->groupsBegin();
  CBookmarkGroup::group_iterator pgroup2 = group1->groupsEnd  ();

  for ( ; pgroup1 != pgroup2; ++pgroup1) {
    CBookmarkGroup *group3 = group2->getGroup((*pgroup1)->getName());

    if (group3 != NULL)
      highlightGroups(*pgroup1, group3, proc);
    else {
      std::string path = group_path_[*pgroup1];

      eval("%s {%s} red", proc, path.c_str());
    }
  }
}

void
CTclMergeBookmarks::
highlightBookmarks(CBookmarkGroup *group1, CBookmarkGroup *group2, const char *proc)
{
  CBookmarkGroup::group_iterator pgroup1 = group1->groupsBegin();
  CBookmarkGroup::group_iterator pgroup2 = group1->groupsEnd  ();

  for ( ; pgroup1 != pgroup2; ++pgroup1)
    highlightBookmarks(*pgroup1, group2, proc);

  CBookmarkGroup::bookmark_iterator pbookmark1 = group1->bookmarksBegin();
  CBookmarkGroup::bookmark_iterator pbookmark2 = group1->bookmarksEnd  ();

  for ( ; pbookmark1 != pbookmark2; ++pbookmark1) {
    CBookmark *bookmark3 = group2->findUrl((*pbookmark1)->getUrl());

    if (bookmark3 == NULL) {
      std::string path = bookmark_path_[*pbookmark1];

      eval("%s {%s} red", proc, path.c_str());
    }
  }
}

bool
CTclMergeBookmarksAddItems1::
proc(int, const char **argv)
{
  const char *filename = argv[1];

  CBookmarkFile *file = new CBookmarkFile(filename);

  file->read();

  file->sort();

  CBookmarkGroup *group = file->getGroup();

  bookmarks_->setFile1(file);

  bookmarks_->addItems(1, "", group);

  return true;
}

bool
CTclMergeBookmarksAddItems2::
proc(int, const char **argv)
{
  const char *filename = argv[1];

  CBookmarkFile *file = new CBookmarkFile(filename);

  file->read();

  file->sort();

  CBookmarkGroup *group = file->getGroup();

  bookmarks_->setFile2(file);

  bookmarks_->addItems(2, "", group);

  return true;
}

bool
CTclMergeBookmarksHighlight::
proc(int, const char **)
{
  bookmarks_->highlight();

  return true;
}
