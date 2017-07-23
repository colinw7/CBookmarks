#ifndef CQBookmarks_H
#define CQBookmarks_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

class QPaintEvent;
class QMouseEvent;
class QWheelEvent;
class QSplitter;
class QLineEdit;
class QLabel;
class QListWidget;
class QTimer;

class CBookmarkGroup;
class CBookmark;

class CQBookmarksTree;
class CQBookmarksInfo;
class CQBookmarksGroupItem;
class CQBookmarksBookmarkItem;

//---

class CQBookmarks : public QWidget {
  Q_OBJECT

 public:
  CQBookmarks();
 ~CQBookmarks();

  void load(const QString &filename);
  void loadGroup(CBookmarkGroup *group, CQBookmarksGroupItem *parent);

  void setNameEdit(const QString &str);
  void setUrlEdit (const QString &str);

 private slots:
  void treeItemSelected(QTreeWidgetItem *item, int);

 private:
  CQBookmarksTree *tree_ { nullptr };
  CQBookmarksInfo *info_ { nullptr };
};

//---

class CQBookmarksTree : public QTreeWidget {
  Q_OBJECT

 public:
  CQBookmarksTree(QWidget *parent = nullptr);
 ~CQBookmarksTree() { }
};

//---

class CQBookmarksInfo : public QWidget {
  Q_OBJECT

 public:
  CQBookmarksInfo(QWidget *parent = nullptr);
 ~CQBookmarksInfo() { }

  void setNameEdit(const QString &str);
  void setUrlEdit (const QString &str);

 private:
  QLabel    *name_label_ { nullptr };
  QLineEdit *name_edit_  { nullptr };
  QLabel    *url_label_  { nullptr };
  QLineEdit *url_edit_   { nullptr };
};

//---

class CQBookmarksGroupItem : public QTreeWidgetItem {
 public:
  CQBookmarksGroupItem(CBookmarkGroup *group);

  CBookmarkGroup *getGroup() const { return group_; }

 private:
  CBookmarkGroup *group_ { nullptr };
};

//---

class CQBookmarksBookmarkItem : public QTreeWidgetItem {
 public:
  CQBookmarksBookmarkItem(CBookmark *bookmark);

  CBookmark *getBookmark() const { return bookmark_; }

 private:
  CBookmark *bookmark_ { nullptr };
};

#endif
