#include "font.h"

ofRectangle Font::DrawTopLeftAlign(std::string text, float x, float y, ofColor color) {
  ofRectangle text_box = getStringBoundingBox(text, x, y);
  text_box.y += text_box.height;

  ofSetColor(color);
  drawString(text, x, y + text_box.height);

  return text_box;
}

//default border = 0
//draw text at top left of bound with optional border spacing
ofRectangle Font::DrawTopLeftAlign(std::string text, ofRectangle bound, ofColor color, int border) {
  return DrawTopLeftAlign(text, bound.x + border, bound.y + border, color);
}

ofRectangle Font::DrawCenterAlign(std::string text, float x, float y, ofColor color) {
  ofRectangle text_box = getStringBoundingBox(text, x, y);

  ofSetColor(color);
  drawString(text, x - (text_box.width / 2), y + (text_box.height / 2));
  text_box.x -= (text_box.width / 2);
  text_box.y += (text_box.height / 2);

  return text_box;
}

//draw text in center of bound
ofRectangle Font::DrawCenterAlign(std::string text, ofRectangle bound, ofColor color) {
  float bound_center_x = bound.x + (bound.width / 2);
  float bound_center_y = bound.y + (bound.height / 2);

  return DrawCenterAlign(text, bound_center_x, bound_center_y, color);
}

//draw text centered horizontally
//y_ratio determines y from ratio of height
ofRectangle Font::DrawCenterAlignX(std::string text, ofRectangle bound, float y_ratio, ofColor color) {
  float bound_center_x = bound.x + (bound.width / 2);
  float bound_y = bound.y + (y_ratio * bound.height);

  return DrawCenterAlign(text, bound_center_x, bound_y, color);
}

ofRectangle Font::DrawBottomLeftAlign(std::string text, float x, float y, ofColor color) {
  ofRectangle text_box = getStringBoundingBox(text, x, y);

  ofSetColor(color);
  drawString(text, x, y);

  return text_box;
}
