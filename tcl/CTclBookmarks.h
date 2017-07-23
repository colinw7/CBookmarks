class CTclBookmarksFile;

class CTclBookmarks : public CTclApp {
 public:
  CTclBookmarks(int argc, char **argv);
 ~CTclBookmarks();

  void addItems(const std::string &path, CBookmarkGroup *group);
  void addItem(const std::string &path, CBookmark *bookmark);

 protected:
  void addCommands();

  std::string getTclStr();
};
