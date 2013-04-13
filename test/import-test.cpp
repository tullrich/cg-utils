#include <stdexcept>

#include "gtest/gtest.h"
#include "import.h"

using namespace cgutils;

class ImportTest : public ::testing::Test
{
protected:

	ImportTest() 
	{
		aap.ImportFromFile("assets/test.obj");
	}
	virtual ~ImportTest(){}

	virtual void SetUp(){}
	virtual void TearDown(){}

	AssimpAssetImporter aap;
};


TEST_F(ImportTest, invalid_filepath) 
{ 
	AssimpAssetImporter temp;

	ASSERT_FALSE(temp.ImportFromFile("bad_file_path"));
}

TEST_F(ImportTest, no_open_scene)
{
	AssimpAssetImporter temp;

	ASSERT_THROW(temp.NumMaterials(), std::logic_error);
	ASSERT_THROW(temp.NumMeshes(), std::logic_error);
}

TEST_F(ImportTest, valid_filepath) 
{ 
	AssimpAssetImporter temp;

	ASSERT_TRUE(temp.ImportFromFile("assets/test.obj"));
}

TEST_F(ImportTest, num_materials) 
{ 
	ASSERT_EQ(1, aap.NumMaterials());
}

TEST_F(ImportTest, num_meshes) 
{ 
	ASSERT_EQ(4, aap.NumMeshes());
}

