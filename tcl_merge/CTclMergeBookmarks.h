class CTclMergeBookmarksFile;

class CTclMergeBookmarks : public CTclApp {
 public:
  CTclMergeBookmarks(int argc, char **argv);
 ~CTclMergeBookmarks();

  void addItems(int num, const std::string &path, CBookmarkGroup *group);
  void addItem(int num, const std::string &path, CBookmark *bookmark);

  void highlight();
  void highlightGroups(CBookmarkGroup *group1, CBookmarkGroup *group2, const char *proc);
  void highlightBookmarks(CBookmarkGroup *group1, CBookmarkGroup *group2, const char *proc);

  void setFile1(CBookmarkFile *file1) { file1_ = file1; }
  void setFile2(CBookmarkFile *file2) { file2_ = file2; }

 protected:
  void addCommands() override;

  std::string getTclStr() override;

 private:
  typedef std::map<CBookmarkGroup *, std::string> GroupPath;
  typedef std::map<CBookmark *, std::string>      BookmarkPath;

  CBookmarkFile* file1_ { nullptr };
  CBookmarkFile* file2_ { nullptr };
  GroupPath      group_path_;
  BookmarkPath   bookmark_path_;
};
