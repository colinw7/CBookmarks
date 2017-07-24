#include <QApplication>
#include <QMainWindow>
#include "CQTagMarks.h"

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QMainWindow *mw = new QMainWindow;

  CQTagMarks *tag_marks = new CQTagMarks;

  mw->setCentralWidget(tag_marks);

  mw->show();

  app.exec();

  return 0;
}
