#include <iostream>

#include "widget_layout.h"

using namespace cgutils;

void testfunction()
{
	printf("this is a test\n");
}

int main()
{
	FLTKWidgetLayout fltk;

	fltk.init();

	fltk.addSlider(new StaticCallBackImpl<&testfunction>());
	fltk.addSlider(new StaticCallBackImpl<&testfunction>());
	fltk.start();

}
