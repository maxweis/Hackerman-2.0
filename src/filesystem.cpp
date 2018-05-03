#include "filesystem.h"
#include "ofApp.h"
#include "render.h"

void Hackerman::OpenFilesystemInterface() {
  main_panel.state = FILESYSTEM;
  current_dir = File(fs_root);
}

//initialize images used in the filesystem
void Hackerman::InitFileImages() {
  filesystem_images = std::vector<ofImage>(EXECUTABLE + 1, ofImage());
  filesystem_images[FOLDER].load(kFolderImagePath);
  filesystem_images[DOCUMENT].load(kDocumentImagePath);
  filesystem_images[EXECUTABLE].load(kExecutableImagePath);

}

void Hackerman::ResizeFileImages(int columns) {
  float image_size;
  if (columns  < 3) {
    image_size = main_panel.height / 6;
  } else {
    image_size = main_panel.height / (columns * 2);
  }
  filesystem_images[FOLDER].resize(image_size, image_size);
  filesystem_images[DOCUMENT].resize(image_size, image_size);
  filesystem_images[EXECUTABLE].resize(image_size, image_size);
}

//initialize filesystem structure inspired by Unix fs structure
void Hackerman::InitFilesystem() {
  fs_root = File("/", std::vector<File>());
  std::vector<File> bin_contents;
  bin_contents.push_back(File("connect", CONNECT));
  bin_contents.push_back(File("decrypt", DECRYPT));
  bin_contents.push_back(File("disconnect", DISCONNECT));
  bin_contents.push_back(File("encrypt", ENCRYPT));
  bin_contents.push_back(File("firewall_attack", FIREWALL_ATTACK));
  bin_contents.push_back(File("firewall_up", FIREWALL_UP));
  bin_contents.push_back(File("store", STORE));

  std::vector<File> etc_contents;
  etc_contents.push_back(File("bitcoin_wallet"));

  std::vector<File> home_contents;
  home_contents.push_back(File("max", std::vector<File>()));

  File bin = File("/bin", bin_contents);
  File etc = File("/etc", etc_contents);
  File home = File("/home", home_contents);

  fs_root.files.push_back(bin);
  fs_root.files.push_back(etc);
  fs_root.files.push_back(home);

  current_dir = File(fs_root);
}

void Hackerman::DrawFilesystemInterface() {
  DrawDirectory();
}

//draw entire current_dir onto main_panel
void Hackerman::DrawDirectory() {
  ResizeFileImages(current_dir.files.size());
  ofRectangle file_bound;
  for (unsigned int i = 0; i < current_dir.files.size(); i++) {
    file_bound = DrawFile(current_dir.files[i], (float) (i + 1) / (float) (current_dir.files.size() + 1));
    current_dir.files[i].bound = file_bound;
  }
}

ofRectangle Hackerman::DrawFile(File file, float y_ratio) {
  std::string file_name = file.name;
  FileType file_type = file.file_type;
  ofRectangle icon_box;
  ofRectangle text_box;

  icon_box = DrawCenterAlignX(filesystem_images[file_type], (ofRectangle) main_panel, y_ratio);

  int text_offset = filesystem_images[file_type].getHeight() / 2 + kBorderWidth * 2;
  text_box = icon_box;
  text_box.y += text_offset;
  text_box = font_inconsolata14.DrawCenterAlign(file_name, text_box, kMainColor);

  //return bound of icon and text
  return ofRectangle(icon_box.x, icon_box.y, icon_box.width,
      text_box.height + icon_box.height + kBorderWidth);
}
