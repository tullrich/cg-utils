#include <iostream>

#include "widget_layout.h"
#include "pantheios/pantheios.hpp"

using namespace cgutils;

class TestClass
{
public:
	int blah;
};


TestClass tt;

void testfunction()
{
	printf("this is a test %i\n", tt.blah);
}



int main()
{
	FLTKWidgetLayout fltk;

	fltk.init();

	fltk.addSlider(new StaticCallBackImpl<&testfunction>());
	fltk.addScalar("test", &tt.blah, 0, 20);
	fltk.start();
	
	pantheios::log_DEBUG("debug");
	pantheios::log_INFORMATIONAL("informational");
	pantheios::log_NOTICE("notice");
	pantheios::log_WARNING("warning");
	pantheios::log_ERROR("error");
	pantheios::log_CRITICAL("critical");
	pantheios::log_ALERT("alert");
	pantheios::log_EMERGENCY("emergency");
}
