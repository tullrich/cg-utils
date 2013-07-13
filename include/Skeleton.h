#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "common.h"
#include <list>
#include <vector>

namespace raytracer {

	class Skeleton; // forward declaration

	class Bone
	{
	public:
		Bone(const std::string &name, const Vector3 &translation = Vector3(), const Vector3 &scale = Vector3()
			, const Quaternion &orientation = Quaternion()) : mName(name), mTranslation(translation)
			, mScale(scale), mOrientation(orientation), mParent(NULL), mOwner(NULL) {};

		void attachChild(Bone *bone);
		void setParent(Bone *bone);
		void setOwner(Skeleton *sk);

		void debugPrintTree();

	protected:
		void debugPrintDFS(int count);

	private:
		std::string mName;
		Vector3 mTranslation, mScale;
		Quaternion mOrientation;

		typedef std::list<Bone*> BoneList;
		BoneList mChildren;

		Bone *mParent;
		Skeleton *mOwner;
	};
	
	class Skeleton
	{
	public:
		Skeleton(Bone *root);
		void notifyAttached(Bone *b);

		Bone* getRoot() { return mRootBone; }
	private:
		typedef std::vector<Bone*> BoneVector; // by index
		BoneVector mAllBones;

		Bone *mRootBone;
	};

} /* namespace raytracer */

#endif