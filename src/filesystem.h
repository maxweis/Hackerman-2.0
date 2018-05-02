#pragma once 

#include <iostream>
#include <vector>
#include "ofMain.h"
#include "panel.h"

enum FileType {
  FOLDER,
  DOCUMENT,
  EXECUTABLE
};

class File {
  public:
  File() {}
  File(const File &other) : name(other.name), file_type(other.file_type), 
    bound(other.bound), program(other.program), files(other.files) {}
  File(std::string name) :
    name(name), file_type(DOCUMENT) {}
  File(std::string name, std::vector<File> files) :
    name(name), file_type(FOLDER), files(files) {}
  File(std::string name, UtilButtonType program) :
    name(name), file_type(EXECUTABLE), program(program) {}

  std::string name;
  FileType file_type;

  ofRectangle bound;
  UtilButtonType program;
  std::vector<File> files;
};

const std::string kFolderImagePath = "icons/folder.png";
const std::string kDocumentImagePath = "icons/document.png";
const std::string kExecutableImagePath = "icons/executable.png";

void InitFileImages();
