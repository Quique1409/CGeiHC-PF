#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	//Movimiento de puertas ENRIQUE
	GLfloat getmuevex() { return muevex; }
	GLfloat getarticulacion1() { return articulacion1; }

	//Movimiento de puertas JOSHUA
	GLfloat getmuevey() { return muevey; }

	//Abrir o cerrar puertas JOSHUA
	GLboolean getAbrirCerrarPuerta() { return abrirCerrarPuerta; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	//Para el status de la piramide
	bool getCamStatus() { return followCamState; }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	// Movimiento de puertas ENRIQUE
	GLfloat muevex;
	GLfloat articulacion1;
	//followCamState
	GLfloat followCamState;

	// Práctica 9.3. Abrir o cerrar puertas
	GLfloat muevey;
	GLboolean abrirCerrarPuerta;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

