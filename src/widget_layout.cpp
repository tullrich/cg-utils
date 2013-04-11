#include "widget_layout.h"

namespace cgutils
{

void FLTKWidgetLayout::init()
{
	window = new Fl_Window(25, 50, 800,600, "OpenGL Depth-Fail Test");
	window->end();
	window->show();
}

void FLTKWidgetLayout::start()
{
	Fl::run();
}

void FLTKWidgetLayout::addComponent(CallBack* cb)
{
	cb->callback();
}

void FLTKWidgetLayout::widgetCallback(Fl_Widget *w, void *data)
{
	CallBack* cb = (CallBack*)data;
	cb->callback();
}

void FLTKWidgetLayout::addSlider(CallBack* cb)
{
	Fl_Hor_Value_Slider &temp = *new Fl_Hor_Value_Slider(5, 5, 190, 25, "");
	temp.user_data(cb);
  	temp.callback(&FLTKWidgetLayout::widgetCallback);
	window->add(temp);
}

} /* namespace cgutils*/
