#include "rendersystem/rendersystem.h"
#include "rendersystem/WindowSubSystem.h"

namespace raytracer {


	RenderSystem::RenderSystem(WindowSubSystem *sys)
		: mWindowSys(sys), mMaterialDirty(true), mCurrentMaterial(NULL)
		, mHWBufferManager(NULL), mMaxLights(8)
		, mFogDirty(true), mLightsDirty(true), mInitilized(false)
	{
	}

	Window* RenderSystem::initialise(const string &windowTitle)
	{
		CGUTILS_ASSERT(mWindowSys && !mInitilized);
		
		mWindowSys->start();

		mHWBufferManager = initaliseHWBufManager();
		Window *win = mWindowSys->createWindow(this, windowTitle);
		mWindows.push_back(win);
		mInitilized = true;
		return win;
	}

	HardwareBufferManager* HardwareBufferManager::gInstance = 0;
	HardwareBufferManager* RenderSystem::getHardwareBufferManager() const
	{
		CGUTILS_ASSERT(mHWBufferManager);

		return mHWBufferManager;
	}

	void RenderSystem::pollEvent()
	{
		mWindowSys->pollEvent();
	}

	void RenderSystem::swapAllWindows()
	{
		WindowList::iterator i = mWindows.begin();
		for(; i != mWindows.end(); i++)
		{
			(*i)->swapBuffers();
		}
	}

	void RenderSystem::clear()
	{
		clearImpl(mClearColor);
	}

	void RenderSystem::setProjectionMatrix(const Matrix4 &proj /*  = Matrix4() */)
	{
		mProjectionMatrix = proj;
		mProjectionViewDirty  = true;
	}

	void RenderSystem::setViewMatrix(const Matrix4 &view /*  = Matrix4()*/)
	{
		mViewMatrix = view;
		mProjectionViewDirty  = true;
	}

	void RenderSystem::setWorldMatrix(const Matrix4 &world /*  = Matrix4() */)
	{
		mWorldMatrix = world;
		mWorldDirty  = true;
	}

	void RenderSystem::updateMaterialGPUParameters()
	{
		if(mCurrentMaterial == NULL)
		{
			setTexture(FT_DIFFUSE, false, NULL);
			setParameterVector4(FU_DiffuseColor, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
			setParameterFloat(FU_Shininess, 1.0f);
			return;
		}


		if(mCurrentMaterial->hasDiffuseTexture())
		{	
			setTexture(FT_DIFFUSE, true, mCurrentMaterial->getDiffuseTexture());
			setParameterVector4(FU_DiffuseColor, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		}
		else
		{
			setTexture(FT_DIFFUSE, false, NULL);
			setParameterVector4(FU_DiffuseColor, Vector4(mCurrentMaterial->getDiffuse(), 1.0f));
		}

		if(mCurrentMaterial->hasNormalTexture())
		{	
			setTexture(FT_NORMAL, true, mCurrentMaterial->getNormalTexture());
		}
		else
		{
			setTexture(FT_NORMAL, false, NULL);
		}

		if(mCurrentMaterial->hasSpecularTexture())
		{	
			setTexture(FT_SPECULAR, true, mCurrentMaterial->getSpecularTexture());
			setParameterFloat(FU_Shininess, mCurrentMaterial->getShininess());
		}
		else
		{
			setTexture(FT_SPECULAR, false, NULL);
			setParameterFloat(FU_Shininess, mCurrentMaterial->getShininess());
		}

		if(mCurrentMaterial->hasEmissiveTexture())
		{
			setTexture(FT_EMISSIVE, true, mCurrentMaterial->getEmissiveTexture());
			//setTexture(FT_NORMAL, true, mCurrentMaterial->getNormalTexture());
		}
		else
		{
			setTexture(FT_EMISSIVE, false, NULL);
		}

		mMaterialDirty= false;
	}

	void RenderSystem::updateLightsGPUParameters()
	{
		int lightCount = (mCurrentLights.size() < mMaxLights) ? mCurrentLights.size() : mMaxLights;
		LightList::iterator iter = mCurrentLights.begin();
		for (int i = 0; i < lightCount; ++i)
		{
			setLight(i, true, (*iter));
			iter++;
		}

		for(int i = lightCount; i < mMaxLights; i++)
		{
			setLight(i, false, NULL);
		}

		mLightsDirty = false;
	}

	void RenderSystem::updateFogGPUParameters()
	{
		setParameterVector3(FU_FogColor, mFog.mColor);
		setParameterVector3(FU_FogParameters, mFog.getFormatted());
		mFogDirty = false;
	}

	void RenderSystem::updateGPUParameters()
	{
		if(mWorldDirty || mProjectionViewDirty)
		{
			if(mProjectionViewDirty)
			{
				mProjectionViewMatrix = mProjectionMatrix * mViewMatrix;
			}
			mModelViewMatrix = mViewMatrix * mWorldMatrix;
			mModelViewProjectionMatrix = mProjectionViewMatrix * mWorldMatrix;
			uploadModelViewProj();

			mProjectionViewDirty = false;
			mWorldDirty = false;
		}

		if(mMaterialDirty)
		{
			updateMaterialGPUParameters();
		}

		if(mLightsDirty)
		{
			updateLightsGPUParameters();
		}

		if(mFogDirty)
		{
			updateFogGPUParameters();
		}
	}

	void RenderSystem::setCurrentMaterial(const Material *m)
	{
		if(mCurrentMaterial != m)
		{
			mCurrentMaterial = m;
			mMaterialDirty = true;
		}
	}

	void RenderSystem::useLights(const LightList &lights)
	{
		mCurrentLights = lights;
		mLightsDirty = true;
	}

	void RenderSystem::setFog(const FogParameters &fog)
	{
		mFog = fog;
		mFogDirty = true;
	}

} /* namespace raytracer  */
