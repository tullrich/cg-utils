#ifndef _OPENGL_RENDER_SYSTEM_H_
#define _OPENGL_RENDER_SYSTEM_H_ 

#include "rendersystem/rendersystem.h"
#include "GL/glew.h"
#include "GL/glu.h"
#include "OpenGLHardwareBufferManager.h"
#include "OpenGLLowLevelShader.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/OpenGL/GL3Renderer.h"

namespace raytracer {

	class OpenGLTexture; // forward declaration
	class OpenGLShaderProgram; // forward declaration

	class OpenGLRenderSystem : public RenderSystem
	{
	public:
		OpenGLRenderSystem(WindowSubSystem *sys);
		virtual ~OpenGLRenderSystem() {};
		virtual void render(const RenderOperation &op);
		virtual Window* initialise(const string &windowTitle);
		virtual void setTexture(int unit, bool enabled, const Texture *t);
		virtual void renderGUI();

	protected:
		virtual void clearImpl(const RGBA &color);
		virtual HardwareBufferManager *initaliseHWBufManager();
		virtual void uploadModelViewProj();

		virtual void setParameterVector4(FixedUniform attr, const Vector4 &value);
		virtual void setParameterVector3(FixedUniform attr, const Vector3 &value);
		virtual void setParameterFloat(FixedUniform attr, float value);
		virtual void setLight(int unit, bool enabled, const Light *t);

	private:
		void initCEGUI();
		typedef std::map<GLint, GLenum> TextureBindingUnitMap;
		TextureBindingUnitMap mLastTexUnitBindings;

		OpenGLShaderProgram *mDefaultProgram, *mDefaultLineProgram;
		bool mCEGUIInitialized;
	};

	typedef OpenGLRenderSystem CompiledRenderSystem;
	typedef OpenGLTexture CompiledTexture;

} /* raytracer */

#endif /* _OPENGL_RENDER_SYSTEM_H_ */
