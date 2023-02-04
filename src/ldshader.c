#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <GL/glew.h>

GLuint
LoadShader(const char * const ShaderCode, GLuint ProgramID, int type)
{
	GLuint ShaderID = glCreateShader(type);
	char const *SourcePointer = ShaderCode;

	glShaderSource(ShaderID, 1, &SourcePointer, NULL);
	glCompileShader(ShaderID);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength > 0){
		char log[1000];
		glGetShaderInfoLog(ShaderID, InfoLogLength > 999 ? 999 : InfoLogLength, NULL, log);
		log[999] = 0;
		printf("%s\n", log);
	}


	glAttachShader(ProgramID, ShaderID);

	return ShaderID;
}

GLuint
MakeProgram(const char *const VertexCode, const char *const FragmentCode)
{
	GLuint ProgramID = glCreateProgram();

	GLuint VertexShaderID = LoadShader(VertexCode, ProgramID, GL_VERTEX_SHADER);
	GLuint FragmentShaderID = LoadShader(FragmentCode, ProgramID, GL_FRAGMENT_SHADER);

	glLinkProgram(ProgramID);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
