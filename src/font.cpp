#include "font.h"

void Font::DrawTopLeftAlign(std::string text, float x, float y, ofColor color) {
  ofRectangle text_box = getStringBoundingBox(text, x, y);

  ofSetColor(color);
  drawString(text, x, y + text_box.height);
}

//default border = 0
//draw text at top left of bound with optional border spacing
void Font::DrawTopLeftAlign(std::string text, ofRectangle bound, ofColor color, int border) {
  DrawTopLeftAlign(text, bound.x + border, bound.y + border, color);
}

void Font::DrawCenterAlign(std::string text, float x, float y, ofColor color) {
  ofRectangle text_box = getStringBoundingBox(text, x, y);

  ofSetColor(color);
  drawString(text, x - (text_box.width / 2), y + (text_box.height / 2));
}

//draw text in center of bound
void Font::DrawCenterAlign(std::string text, ofRectangle bound, ofColor color) {
  float bound_center_x = bound.x + (bound.width / 2);
  float bound_center_y = bound.y + (bound.height / 2);

  DrawCenterAlign(text, bound_center_x, bound_center_y, color);
}

//draw text centered horizontally
//y_ratio determines y from ratio of height
void Font::DrawCenterAlignX(std::string text, ofRectangle bound, float y_ratio, ofColor color) {
  float bound_center_x = bound.x + (bound.width / 2);
  float bound_y = bound.y + (y_ratio * bound.height);

  DrawCenterAlign(text, bound_center_x, bound_y, color);
}

void Font::DrawBottomLeftAlign(std::string text, float x, float y, ofColor color) {
  ofRectangle text_box = getStringBoundingBox(text, x, y);

  ofSetColor(color);
  drawString(text, x, y);
}
