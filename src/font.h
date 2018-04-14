#pragma once

#include "ofMain.h"
#include "render.h"

class Font : public ofTrueTypeFont {
 public:
  //inherit constructors of parent class
  using ofTrueTypeFont::ofTrueTypeFont;

  void DrawTopLeftAlign(std::string text, float x, float y, ofColor color);
  void DrawTopLeftAlign(std::string text, ofRectangle rect, ofColor color, int border = 0);
  void DrawCenterAlign(std::string text, float x, float y, ofColor color);
  void DrawCenterAlign(std::string text, ofRectangle rect, ofColor color);
  void DrawCenterAlignX(std::string text, ofRectangle bound, float y_ratio, ofColor color);
  void DrawBottomLeftAlign(std::string text, float x, float y, ofColor color);
};
