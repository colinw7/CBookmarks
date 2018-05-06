#include <CQBookmarks.h>
#include <QMainWindow>
#include <CFile.h>
#include <iostream>

#ifdef CQ_APP_H
#include <CQApp.h>
#else
#include <QApplication>
#endif

int
main(int argc, char **argv)
{
#ifdef CQ_APP_H
  CQApp app(argc, argv);
#else
  QApplication app(argc, argv);
#endif

  QMainWindow *mw = new QMainWindow;

  CQBookmarks *bookmarks = new CQBookmarks;

  std::string filename = "bookmarks.html";

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      std::cerr << "Invalid arg '" << argv[i] << "'" << std::endl;
    }
    else {
      filename = argv[i];
    }
  }

  if (! CFile::isRegular(filename)) {
    std::cerr << "Invalid file '" << filename << "'" << std::endl;
    exit(1);
  }

  bookmarks->load(filename.c_str());

  mw->setCentralWidget(bookmarks);

  mw->show();

  app.exec();

  return 0;
}
