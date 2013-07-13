#include "Skeleton.h"

namespace raytracer {


	void Bone::attachChild(Bone *bone)
	{
		CGUTILS_ASSERT(mOwner != NULL)

		mChildren.push_back(bone);
		bone->setParent(this);
		mOwner->notifyAttached(bone);
	}
	
	void Bone::setParent(Bone *bone)
	{
		CGUTILS_ASSERT(mParent == NULL)
		mParent = bone;
	}
	
	void Bone::setOwner(Skeleton *sk)
	{
		CGUTILS_ASSERT(mOwner == NULL)
		mOwner = sk;
	}

	void Bone::debugPrintTree()
	{
		debugPrintDFS(0);
	}

	void Bone::debugPrintDFS(int count)
	{
		for(int i = 0; i < count; i++)
			std::cout << "\t";

		std::cout << mName << std::endl; 

		BoneList::iterator i = mChildren.begin();
		for(; i != mChildren.end(); i++)
		{
			(*i)->debugPrintDFS(count + 1);
		}
	}

	Skeleton::Skeleton(Bone *root) : mRootBone(root), mAllBones(1)
	{
		mRootBone->setOwner(this);
		mAllBones[0] = mRootBone;
	}

	void Skeleton::notifyAttached(Bone *b)
	{
		mAllBones.resize(mAllBones.size() + 1); 
		mAllBones[mAllBones.size() - 1] = b; 
		b->setOwner(this);
		std::cout << "Notify bone count " << mAllBones.size() << std::endl; 
	}

} /* namespace raytracer */
