#include "gtest/gtest.h"
#include "gmock/gmock.h" 

#include <stdexcept>

#include "vector.h"
#include "widget_layout.h"

using namespace cgutils;
using ::testing::AtLeast; 

class WidgetTest : public ::testing::Test
{
protected:

	WidgetTest()
	{
	}

	virtual ~WidgetTest()
	{
	}

	virtual void SetUp()
	{
		fltk.init();
	}

	virtual void TearDown()
	{
	}


	FLTKWidgetLayout fltk;
};

class MockCallbackReceiver {
 public:
  MOCK_METHOD0(PenUp, void());
  MOCK_METHOD0(PenDown, void());
};


TEST_F(WidgetTest, objectcallback) 
{ 
	MockCallbackReceiver receiver;                            
	EXPECT_CALL(receiver, PenUp())             
	.Times(AtLeast(1));

	CallBack &test = *(new CallBackImpl<MockCallbackReceiver, &MockCallbackReceiver::PenDown>(receiver));
	test.callback();
}
