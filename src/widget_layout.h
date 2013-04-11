#ifndef _WIDGET_LAYOUT_H
#define _WIDGET_LAYOUT_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>

#include "cgutils.hpp"

namespace cgutils
{


class IWidgetLayout
{
public:
	virtual void init() = 0;
	virtual void start() = 0;
};


class FLTKWidgetLayout : public IWidgetLayout
{
public:
	virtual void init();
	virtual void start();

	/**
	* Adds a component to the layout with a provided callback
	* 
	* @param filename GIF File name to be loaded
	*/
	virtual void addComponent(CallBack* cb);

	virtual void addSlider(CallBack* cb);

	static void widgetCallback(Fl_Widget *w, void *data);

protected:
	Fl_Window *window;

};


template <typename T>
void callback(Fl_Widget *w, void *data)
{

}

} /* namespace cgutils*/
#endif /*_WIDGET_LAYOUT_H */