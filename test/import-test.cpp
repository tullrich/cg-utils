#include <stdexcept>

#include "gtest/gtest.h"
#include "import.h"

using namespace cgutils;

class ImportTest : public ::testing::Test
{
protected:

	ImportTest() 
	{
		aap.Open("assets/test.obj");
	}
	virtual ~ImportTest(){}

	virtual void SetUp(){}
	virtual void TearDown(){}

	AssimpAssetImporter aap;
};

typedef ImportTest ImportDeathTest;

TEST_F(ImportTest, invalid_filepath) 
{ 
	AssimpAssetImporter temp;

	ASSERT_FALSE(temp.Open("bad_file_path"));
}

TEST_F(ImportTest, valid_filepath) 
{ 
	AssimpAssetImporter temp;

	ASSERT_TRUE(temp.Open("assets/test.obj"));
}

TEST_F(ImportTest, num_materials) 
{ 
	ASSERT_EQ(1, aap.NumMaterials());
}

TEST_F(ImportTest, num_meshes) 
{ 
	ASSERT_EQ(4, aap.NumMeshes());
}