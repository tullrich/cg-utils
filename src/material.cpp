#include "material.h"

namespace raytracer {

	RGB Material::BRDF(const TexCoord *uv) const
	{
		return mDiffuse;
	}

	RGB Material::Le(const TexCoord *uv) const
	{
		return mEmissive;
	}

	void Material::ensureLoaded()
	{
		if(!mLoaded)
		{
			//TODO Fix this!
			if(mDiffuseMap && !mDiffuseMap->load())
			{
				mDiffuseMap = NULL;
			}

			if(mSpecularMap && !mSpecularMap->load())
			{
				mSpecularMap = NULL;
			}

			if(mEmissiveMap && !mEmissiveMap->load())
			{
				mEmissiveMap = NULL;
			}

			if(mNormalMap && !mNormalMap->load())
			{
				mNormalMap = NULL;
			}

			mLoaded = true;
		}
	}

	MaterialManager::MaterialManager()
	{
		mDefaultMaterial = new Material();
		mDefaultMaterial->setDiffuse(Vector3(1.0f, 0.0, 0.0));
	}

	Material* MaterialManager::getDefaultObject()
	{
		return mDefaultMaterial;
	}

	std::ostream& operator<<(std::ostream& o, const Material& b) 
	{
		return o << "Material '" << b.name << "' {\n" << \
			"\tspecular: <" << b.mSpecular << "\n" << \
			"\tdiffuse : <" << b.mDiffuse << "\n" << \
			"\tambient : <" << b.mAmbient << "\n" << \
			"\temissive : <" << b.mEmissive << "\n" << \
			"\tdiffuse : <" << b.mDiffuse << "\n" << \
			"\tshininess : <" << b.mShininess << "\n" << \
			"}";
	}

}; /* namespace raytracer */
