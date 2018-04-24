#pragma once

#include "ofMain.h"
#include "render.h"
#include <iostream>

class Font : public ofTrueTypeFont {
 public:
  //inherit constructors of parent class
  using ofTrueTypeFont::ofTrueTypeFont;

  ofRectangle DrawTopLeftAlign(std::string text, float x, float y, ofColor color);
  ofRectangle DrawTopLeftAlign(std::string text, ofRectangle rect, ofColor color, int border = 0);
  ofRectangle DrawCenterAlign(std::string text, float x, float y, ofColor color);
  ofRectangle DrawCenterAlign(std::string text, ofRectangle rect, ofColor color);
  ofRectangle DrawCenterAlignX(std::string text, ofRectangle bound, float y_ratio, ofColor color);
  ofRectangle DrawBottomLeftAlign(std::string text, float x, float y, ofColor color);
};
