#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//http://www.swiftless.com/tutorials/opengl/keyboard.html
#include <GL/glut.h>
#include <math.h>

#include "src/ldshader.h"

GLFWwindow *window;
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint ProgramID;

#define STR(...) #__VA_ARGS__

static const char VertexShader[] = 
"#version 300 es\n"
#include "src/VertShader.glsl"

;

static const char FragmentShader[] = 
"#version 300 es\n"
#include "src/FragShader.glsl"
;

void
init(void)
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0,
		0.0, 0.5, 0.0
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	ProgramID = MakeProgram(VertexShader, FragmentShader);
}

int
draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);
	glfwPollEvents();

	float time = glfwGetTime();
	GLuint uniformTime = glGetUniformLocation(ProgramID, "time");
	glUseProgram(ProgramID);
	glUniform1f(uniformTime, time);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		NULL
	);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ? EM_TRUE : EM_FALSE;
}

EM_BOOL
drawLoop_em(double t, void *ui)
{
	if(draw())
		return EM_TRUE;
	printf("exited draw loop.\n");
	return EM_FALSE;
}

void
drawLoop(void)
{
	emscripten_request_animation_frame_loop(drawLoop_em, 0);
}

int
main(int argc, char **argv)
{
	if(glfwInit()){
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(1000, 750, "mfw.png", NULL, NULL);

		if(window){
			glfwMakeContextCurrent(window);
			glewExperimental=GL_TRUE;
			if(glewInit() == GLEW_OK){
				init();
				drawLoop();
				return 0;
			}else
				printf("failed to initialize GLEW.\n");
		}else
			printf("failed to open GLFW window.\n");
	}else		
		printf("failed to initialize GLFW.\n");	

	return 1;
	
}
