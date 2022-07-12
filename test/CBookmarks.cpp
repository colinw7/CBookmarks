#include <CBookmarksLib.h>
#include <cstring>

int
main(int argc, char **argv)
{
  bool merge         = false;
  bool html          = false;
  bool markdown      = false;
  bool dump          = false;
  bool duplicates    = false;
  bool last_modified = false;

  std::list<std::string> filenames;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if      (strcmp(&argv[i][1], "merge") == 0) {
        merge = true;
      }
      else if (strcmp(&argv[i][1], "dump") == 0) {
        dump  = true;
      }
      else if (strcmp(&argv[i][1], "duplicates") == 0) {
        duplicates = true;
      }
      else if (strcmp(&argv[i][1], "html") == 0) {
        html = true;
      }
      else if (strcmp(&argv[i][1], "markdown") == 0) {
        markdown = true;
      }
      else if (strcmp(&argv[i][1], "last_modified") == 0) {
        last_modified = true;
      }
      else if (strcmp(&argv[i][1], "help") == 0) {
        std::cerr << "CBookmarks [-dump|-merge] [-html|-markdown] [-last_modified] <files>" <<
                     std::endl;
        exit(1);
      }
      else
        std::cerr << "Invalid Argument " << argv[i] << std::endl;
    }
    else {
      filenames.push_back(argv[i]);
    }
  }

  if (! html && ! markdown && ! dump)
    html = true;

  if (filenames.empty()) {
    std::cerr << "No Files specified" << std::endl;
    exit(1);
  }

  //----

  std::vector<CBookmarkFile *> files;

  for (const auto &filename : filenames) {
    if (! CFile::isRegular(filename)) {
      std::cerr << "Invalid filename '" << filename << "'" << std::endl;
      continue;
    }

    auto *file = new CBookmarkFile(filename);

    file->setIgnoreDuplicates(! duplicates);

    file->read();

    files.push_back(file);
  }

  //----

  if (last_modified) {
    char str[256];

    for (const auto &file : files) {
      auto t = file->lastModified();

      auto *tm = localtime(&t);

      strftime(str, 256, "%c", tm);

      std::cerr << str << " (" << t << ")" << std::endl;
    }

    exit(0);
  }

  //----

  auto processFile = [&](CBookmarkFile *file) -> void {
    if      (html)
      file->printHtml();
    else if (markdown)
      file->printMarkdown();
    else
      file->dump();
  };

  if (merge) {
    if (files.size() >= 1) {
      if (html) {
        std::cout << "<html>"                   << std::endl;
        std::cout << "<head>"                   << std::endl;
        std::cout << "<title>Bookmarks</title>" << std::endl;
        std::cout << "</head>"                  << std::endl;
        std::cout << "<body>"                   << std::endl;
        std::cout << "<h1>Bookmarks</h1>"       << std::endl;
      }
      else {
        std::cout << "# Bookmarks #" << std::endl;
      }

      CBookmarkFile *file = files[0];

      for (std::size_t i = 1; i < files.size(); ++i) {
        file->append(*files[i]);
      }

      file->sort();

      processFile(file);

      if (html) {
        std::cout << "</body>" << std::endl;
        std::cout << "</html>" << std::endl;
      }
    }
    else {
      for (const auto &file : files) {
        processFile(file);
      }
    }
  }
  else {
    for (const auto &file : files) {
      processFile(file);
    }
  }

  return 0;
}
