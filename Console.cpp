/******************************************************************************************************************************************************************************************
File Name:  Console.cpp
Author(s):  Joel Johnson 
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"

namespace GAM200
{
  Console::Console()
  {
    showing = false;
    currentLine = 0;
    clear();
  }
  
  Console::~Console()
  {
    delete font;
    delete panel;
  }
  
  bool Console::init()
  {
    //load the panel image
    panel = new Sprite();
    if(!panel->loadImage("panel.tga"))return false;
    double scale = g_engine->getScreenWidth() / 640.0f;
    panel->setScale(scale);
    panel->setColor(0x99FFFFFF);
    
    //load the font
    font = new Font();
    if(!font->loadImage("system12.tga")) return false;
    font->setColumns(16);
    font->setCharSize(14, 16);
    if(!font->loadWidthData("system12.dat")) return false;
    return true;
  }
  
  void Console::draw()
  {
    int x = 5, y = 0;
    if(!showing) return;
    //draw panel background
    panel->draw();
    //draw text lines
    for(unsigned int n = 0; n < textlines.size(); n++)
    {
      font->Print(x, y*14, textlines[n], 0xFF000000);
      y+= 1;
      if(y > 26) {
        if(x > 10) break;
        x = g_engine->getScreenWidth()/2 + 5;
        y = 0;
      }
    }
  }
  
  void Console::print(std::string text, int line)
  {
    if(line > -1) currentLine = line;
    textlines[currentLine] = text;
    if(currentLine++ > 52) currentLine = 0;
  }
  
  void Console::clear()
  {
    for(int n = 0; n < 55; n++)
      textlines.push_back("");
  }
};