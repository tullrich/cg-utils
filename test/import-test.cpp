#include "gtest/gtest.h"
#include "import.h"

using namespace cgutils;

class ImportTest : public ::testing::Test
{
protected:

	ImportTest(){}
	virtual ~ImportTest(){}

	virtual void SetUp(){}
	virtual void TearDown(){}

};


TEST_F(ImportTest, invalidfilepath) 
{ 
	AssimpAssetImporter aap;

	ASSERT_FALSE(aap.ImportFromFile("bad_file_path"));
}

TEST_F(ImportTest, validfilepath) 
{ 
	AssimpAssetImporter aap;

	ASSERT_FALSE(aap.ImportFromFile("bad_file_path"));
}
