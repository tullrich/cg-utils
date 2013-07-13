#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_ 

#include "common.h"
#include "HardwareBuffer.h"
#include "Renderable.h"
#include "windowsubsystem.h"
#include "light.h"
#include "HardwareTexture.h"
#include "material.h"

namespace raytracer {

	enum FixedAttribute
	{
		FA_VERTICES = 0,
		FA_NORMALS = 1,
		FA_DIFFUSE_COLORS = 2,
		FA_SPECULAR_COLORS = 3,
		FA_TEX_COORDS_0 = 4,
		FA_TEX_COORDS_1 = 5,
		FA_TEX_COORDS_2 = 6,
		FA_TEX_COORDS_3 = 7,
		FA_TEX_COORDS_4 = 8,
		FA_TEX_COORDS_5 = 9,
		FA_TEX_COORDS_6 = 10,
	};

	enum FixedTexture
	{
		FT_DIFFUSE = 0,
		FT_NORMAL = 1,
		FT_SPECULAR = 2,
		FT_EMISSIVE = 3,
	};

	enum FixedUniform
	{
		FU_ModelViewProjection = 0,
		FU_ModelView = 1,
		FU_InverseViewProjection = 2,
		FU_DiffuseColor = 3,
		FU_NormalMatrix = 4,
		FU_Shininess = 5,
		FU_FogParameters = 6,
		FU_FogColor = 7,
	};

	struct FogParameters
	{
		RGB mColor;
		float mStart;
		float mEnd;
		float mDensity;

		Vector3 getFormatted()
		{
			return Vector3(mStart, mEnd, mDensity);
		}

		FogParameters() : mStart(0.0f), mEnd(0.0f), mDensity(0.0f) {};
		FogParameters(const RGB &color, float start, float end, float density)
			 : mColor(color), mStart(start), mEnd(end), mDensity(density) 
		 {
		 	density = min(max(density, 0.0f), 1.0f);
		 };
	};
	
	class RenderSystem
	{
		typedef std::list<Light*> LightList;

	public:
		RenderSystem();
		virtual ~RenderSystem() {};
	
		virtual Window* initialise(const string& windowTitle);
		HardwareBufferManager* getHardwareBufferManager() const;
		void pollEvent();
		virtual void render(const RenderOperation &op) = 0;
		virtual void setTexture(int unit, bool enabled, const Texture *t) = 0;
		virtual void renderGUI() = 0;

		void setCurrentMaterial(const Material *m);
		void setProjectionMatrix(const Matrix4 &proj = Matrix4());
		void setViewMatrix(const Matrix4 &view = Matrix4());
		void setWorldMatrix(const Matrix4 &world = Matrix4());
		void useLights(const LightList &lights);
		void setFog(const FogParameters &fog);
		void setClearColor(const RGBA &color) { mClearColor = color; }

		void updateGPUParameters();
		void clear();
		void swapAllWindows();

	protected:
		virtual void uploadModelViewProj() = 0;
		virtual void clearImpl(const RGBA &color) = 0;

		virtual void setParameterVector4(FixedUniform attr, const Vector4 &value) = 0;
		virtual void setParameterVector3(FixedUniform attr, const Vector3 &value) = 0;
		virtual void setParameterFloat(FixedUniform attr, float value) = 0;
		
		virtual void setLight(int unit, bool enabled, const Light *t) = 0;
		virtual HardwareBufferManager *initaliseHWBufManager() = 0;

		void updateMaterialGPUParameters();
		void updateLightsGPUParameters();
		void updateFogGPUParameters();

		Matrix4 mProjectionMatrix, mViewMatrix, mWorldMatrix;
		Matrix4 mProjectionViewMatrix, mModelViewProjectionMatrix, mModelViewMatrix;
	private:
		WindowSubSystem *mWindowSys;
		HardwareBufferManager *mHWBufferManager;
		const Material* mCurrentMaterial;

		typedef std::list<Window*> WindowList;
		WindowList mWindows;

		LightList mCurrentLights;
		int mMaxLights;

		FogParameters mFog;
		RGBA mClearColor;

		bool mProjectionViewDirty, mWorldDirty, mMaterialDirty, mLightsDirty, mFogDirty;
	};



} /* raytracer */

#ifdef OPENGL_ENABLED
#include "rendersystem/opengl/OpenGLRenderSystem.h"
#endif

#endif /* _RENDER_SYSTEM_H_ */
