#ifndef _OPENGL_LOW_LEVEL_SHADER_H_
#define _OPENGL_LOW_LEVEL_SHADER_H_ 

#include "common.h"
#include "rendersystem/opengl/OpenGLRenderSystem.h"

namespace raytracer {

	class OpenGLLowLevelShader
	{
	public:

		enum HardwareShaderType
		{
			GPU_VERTEX_SHADER,
			GPU_FRAGMENT_SHADER,
			GPU_GEOMETRY_SHADER,
		};

		OpenGLLowLevelShader(HardwareShaderType type, const std::string &filePath);
		virtual ~OpenGLLowLevelShader();

		bool readSourceFile();
		void loadSource();
		bool isCompiled() { return mIsCompiled; }
		bool isBad() { return mIsBad; }
		HardwareShaderType getShaderType() const { return mType; }
		GLuint getShaderID() const { return mShaderID; }
	protected:
		void logShaderInfo();

	private:
		HardwareShaderType mType;
		GLuint mShaderID;
		string mFilePath;
		string mSource;
		bool mIsCompiled, mIsBad;
	};

} /* raytracer */

#endif /* _OPENGL_LOW_LEVEL_SHADER_H_ */
