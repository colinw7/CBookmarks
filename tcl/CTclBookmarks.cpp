#include <CTclApp.h>
#include <CTclAppCommand.h>

#undef INLINE

#include <CBookmarksLib.h>
#include <CTclBookmarks.h>

#include <CTclBookmarks.k>

#define CTclBookmarksAppCommand(N) \
class N : public CTclAppCommand { \
 private: \
  CTclBookmarks *bookmarks_; \
\
 public: \
  N(CTclBookmarks *bookmarks) : \
    CTclAppCommand(bookmarks, #N), bookmarks_(bookmarks) { \
  } \
\
 protected: \
  bool proc(int argc, const char **argv) override; \
};

CTclBookmarksAppCommand(CTclBookmarksAddItems)

int
main(int argc, char **argv)
{
  CTclBookmarks app(argc, argv);
}

CTclBookmarks::
CTclBookmarks(int argc, char **argv) :
 CTclApp(argc, argv)
{
  init();
}

CTclBookmarks::
~CTclBookmarks()
{
}

void
CTclBookmarks::
addCommands()
{
  new CTclBookmarksAddItems(this);
}

std::string
CTclBookmarks::
getTclStr()
{
  return CTclBookmarks_TK;
}

bool
CTclBookmarksAddItems::
proc(int argc, const char **argv)
{
  if (argc < 1) return false;

  const char *filename = argv[1];

  CBookmarkFile file(filename);

  file.read();

  file.sort();

  CBookmarkGroup *group = file.getGroup();

  bookmarks_->addItems("", group);

  return true;
}

void
CTclBookmarks::
addItems(const std::string &path, CBookmarkGroup *group)
{
  if (path.size() > 0)
    eval("CTclBookmarksAddGroup {%s} {%s}",
         path.c_str(), group->getName().c_str());

  CBookmarkGroup::group_iterator pgroup1 = group->groupsBegin();
  CBookmarkGroup::group_iterator pgroup2 = group->groupsEnd  ();

  for ( ; pgroup1 != pgroup2; ++pgroup1) {
    std::string path1 = path;

    if (path.size() > 0)
      path1 += "@";

    path1 += (*pgroup1)->getName();

    addItems(path1, *pgroup1);
  }

  CBookmarkGroup::bookmark_iterator pbookmark1 = group->bookmarksBegin();
  CBookmarkGroup::bookmark_iterator pbookmark2 = group->bookmarksEnd  ();

  for ( ; pbookmark1 != pbookmark2; ++pbookmark1)
    addItem(path, *pbookmark1);

  if (path.size() > 0)
    eval("CTclBookmarksCloseGroup {%s}",
         path.c_str());
}

void
CTclBookmarks::
addItem(const std::string &path, CBookmark *bookmark)
{
  std::string path1 = path;

  if (path.size() > 0)
    path1 += "@";

  path1 += bookmark->getName();

  eval("CTclBookmarksAddItem {%s} {%s} {%s}",
       path1.c_str(), bookmark->getName().c_str(),
       bookmark->getUrl().c_str());
}
