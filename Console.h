/******************************************************************************************************************************************************************************************
File Name:  Console.h
Author(s):  Joel Johnson
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"

namespace GAM200
{
  class Console{
  private:
    bool showing;
    Sprite *panel;
    Font *font;
    int currentLine;
    std::vector<std::string> textlines;
    std::vector<std::string>::iterator iter;
  public:
    Console();
    virtual ~Console();
    bool init();
    void draw();
    void clear();
    void print(std::string text, int line = -1);
    bool isShowing() { return this->showing; }
    void show() { this->showing = true; }
    void hide() { this->showing = false; }
    void setShowing(bool value) { this->showing = value; }
  };
};