#pragma once

#include <GL\glew.h>
#include "../utils/fileutils.h"
#include <vector>
#include <iostream>
#include "../maths/maths.h"

namespace sparky { namespace graphics {

	class Shader{
	private:
		GLuint m_shaderID;
		const char *m_vertPath, *m_fragPath;
	public:
		Shader(const char *vertPath, const char *fragPath);
		Shader(const char *name);
		~Shader();

		void enable() const;
		void disable() const;
	private:
		GLuint load();
		GLint getUniformLocation(const GLchar *name);
	public:
		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
	};
	
}}