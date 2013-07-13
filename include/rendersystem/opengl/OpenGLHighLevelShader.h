#ifndef _HIGH_LEVEL_SHADER_H_
#define _HIGH_LEVEL_SHADER_H_ 

namespace raytracer {

	class OpenGLHighLevelShader
	{
	public:
		OpenGLHighLevelShader() {};
		virtual ~OpenGLHighLevelShader() {};

		void compile();
	};

} /* raytracer */

#endif /* _HIGH_LEVEL_SHADER_H_ */
