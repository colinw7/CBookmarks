#include <CQBookmarks.h>
#include <CBookmarksLib.h>
#include <CFile.h>
#include <CStrUtil.h>

#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

//--------------

CQBookmarks::
CQBookmarks()
{
  QHBoxLayout *layout = new QHBoxLayout(this);

  //------

  QSplitter *splitter = new QSplitter(Qt::Horizontal);

  layout->addWidget(splitter);

  //------

  tree_ = new CQBookmarksTree;

  connect(tree_, SIGNAL(itemClicked(QTreeWidgetItem *, int)),
          this, SLOT(treeItemSelected(QTreeWidgetItem *, int)));

  splitter->addWidget(tree_);

  //------

  info_ = new CQBookmarksInfo(this);

  splitter->addWidget(info_);
}

CQBookmarks::
~CQBookmarks()
{
}

void
CQBookmarks::
load(const QString &fileName)
{
  CBookmarkFile bookmarks(fileName.toStdString());

  bookmarks.setIgnoreDuplicates(true);

  bookmarks.read();

  tree_->clear();

  CBookmarkGroup *group = bookmarks.getGroup();

  loadGroup(group, nullptr);
}

void
CQBookmarks::
loadGroup(CBookmarkGroup *group, CQBookmarksGroupItem *parent)
{
  CBookmarkGroup::group_iterator pg1 = group->groupsBegin();
  CBookmarkGroup::group_iterator pg2 = group->groupsEnd  ();

  for ( ; pg1 != pg2; ++pg1) {
    CBookmarkGroup *group1 = (*pg1);

    CQBookmarksGroupItem *item = new CQBookmarksGroupItem(group1);

    if (! parent)
      tree_->addTopLevelItem(item);
    else
      parent->addChild(item);

    loadGroup(group1, item);
  }

  CBookmarkGroup::bookmark_iterator pb1 = group->bookmarksBegin();
  CBookmarkGroup::bookmark_iterator pb2 = group->bookmarksEnd  ();

  for ( ; pb1 != pb2; ++pb1) {
    CBookmark *bookmark1 = (*pb1);

    CQBookmarksBookmarkItem *item = new CQBookmarksBookmarkItem(bookmark1);

    if (! parent)
      tree_->addTopLevelItem(item);
    else
      parent->addChild(item);
  }
}

void
CQBookmarks::
setNameEdit(const QString &str)
{
  info_->setNameEdit(str);
}

void
CQBookmarks::
setUrlEdit(const QString &str)
{
  info_->setUrlEdit(str);
}

void
CQBookmarks::
treeItemSelected(QTreeWidgetItem *item, int)
{
  if      (CQBookmarksGroupItem *group_item =
             dynamic_cast<CQBookmarksGroupItem *>(item)) {
    CBookmarkGroup *group = group_item->getGroup();

    setNameEdit(group->getName().c_str());
    setUrlEdit ("");
  }
  else if (CQBookmarksBookmarkItem *bookmark_item =
             dynamic_cast<CQBookmarksBookmarkItem *>(item)) {
    CBookmark *bookmark = bookmark_item->getBookmark();

    setNameEdit(bookmark->getName().c_str());
    setUrlEdit (bookmark->getUrl ().c_str());
  }
}

//--------------

CQBookmarksTree::
CQBookmarksTree(QWidget *parent) :
 QTreeWidget(parent)
{
  setColumnCount(1);

  headerItem()->setHidden(true);

  setSelectionMode(QAbstractItemView::SingleSelection);
}

//--------------

CQBookmarksInfo::
CQBookmarksInfo(QWidget *parent) :
 QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  QGridLayout *grid = new QGridLayout;

  name_label_ = new QLabel   ("Name");
  name_edit_  = new QLineEdit();

  url_label_  = new QLabel   ("Url");
  url_edit_   = new QLineEdit();

  grid->addWidget(name_label_, 0, 0);
  grid->addWidget(name_edit_ , 0, 1);
  grid->addWidget(url_label_ , 1, 0);
  grid->addWidget(url_edit_  , 1, 1);

  layout->addLayout(grid);

  layout->addStretch();
}

void
CQBookmarksInfo::
setNameEdit(const QString &str)
{
  name_edit_->setText(str);
}

void
CQBookmarksInfo::
setUrlEdit(const QString &str)
{
  url_edit_->setText(str);
}

//--------------

CQBookmarksGroupItem::
CQBookmarksGroupItem(CBookmarkGroup *group) :
 QTreeWidgetItem(QStringList() << group->getName().c_str()),
 group_(group)
{
}

CQBookmarksBookmarkItem::
CQBookmarksBookmarkItem(CBookmark *bookmark) :
 QTreeWidgetItem(QStringList() << bookmark->getName().c_str()),
 bookmark_(bookmark)
{
}
