#include <iostream>

#include "widget_layout.h"

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

}
