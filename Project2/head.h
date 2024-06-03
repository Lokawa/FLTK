//
// Created by DELL on 2023/12/25.
//

#ifndef PROJECT2_HEAD_H
#define PROJECT2_HEAD_H
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_File_Chooser.H>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>
struct Point
{
    int x,y,direction;
    Point(int x,int y,int direction):x(x),y(y),direction(direction){}
    Point(){}
};
#endif //PROJECT2_HEAD_H
