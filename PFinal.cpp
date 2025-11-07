/*
Animación:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada)
Compleja: Por medio de funciones y algoritmos.
Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
//variables para puerta
float rotacion = 0.0f;
float deslizamiento = 0.0f;

float movOffset;
float rotdeslizamientoOffset;
bool avanza = true;
bool abrePuerta = true;
bool cambioTextura = true;
float rotaDragon = 0.0f;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
float dragonavance = 0.0f;

// Variables para ciclo día/noche
float tiempoDia = 0.0f;       // contador del tiempo del día
float velocidadCiclo = 0.0009f;    // velocidad de transición (ajústala)
bool esNoche = true;
float velocidad;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture PiramideTexture;
Texture SerpTexture;

// Texturas de los backyardigans - PUERTA JOSHUA
Texture TipografiaBackyardigans;

//Se añade una textura de un camino
Texture CaminoTexture;
Texture CaminoLodoTexture;

//Letrero PUERTA ENRIQUE
//Puerta
Texture PuertaTexture;
Texture LetreroTexture;

// ----------------- NPCS ----------------- //
Model Baljeet;

// ---------------- ENTORNO ----------------- //
// Modelos de la puerta Joshua
Model Arco;
Model PuertaIzq;
Model PuertaDer;
Model CartelPuerta;

// Modelos de puerta Enrique
Model Cartel_M;
Model PuertaIzq_M;
Model PuertaDer_M;
Model Arco_M;

// Modelo cabeza olmeca
Model CabezaOlmeca;

// Modelos RING de boxeo
Model Ring_R;
Model Escaleras_R;
Model Lona_R;

// Modelos de columpios
Model Estructura_C;
Model ColumpioDer_C;
Model ColumpioIzq_C;

// Modelo mesa de picnic
Model MesaPicnic;

// Modelos baño portatil
Model CuerpoBano; 
Model TapaBano; 
Model PuertaBano;

// Fuente
Model CuerpoFuente;
Model Fuente;

//Prueba para seguimiento de camara
Model Cubo_M;

//Se añaden los modelos separados del dragón (cuerpo, ala izquierda y ala derecha).
Model DragonCuerpo_M;
Model DragonAlaIzq_M;
Model DragonAlaDer_M;
Model Tiamat_M;

//Se añaden modelos de Piramide
Model BasePiradime_M; 
Model CupulaPiramide_M;
Model Serpientes_M;

//Skyboxes
Skybox skybox; 
Skybox skyboxDia; 
Skybox skyboxNoche;
Skybox skyboxAMAT;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,			0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,			0.0f, -1.0f, 0.0f,
	};

	GLfloat backyardigansVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,			0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,			0.0f, -1.0f, 0.0f,
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6); // todos los números

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7); // solo un número

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(backyardigansVertices, numeroIndices, 32, 6);
	meshList.push_back(obj8); // solo un número
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	//Posición del cubo para que se calcule cada frame
	glm::vec3 cubePosition = glm::vec3(0.0f, 5.0f, 0.0f);

	// Cámara
	camera = Camera(glm::vec3(-150.0f, 0.0f, -150.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/pasto.jpg");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/PastoJoshua.jpg");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	TipografiaBackyardigans = Texture("Textures/ProyectoCGEIHC.png");
	TipografiaBackyardigans.LoadTextureA();

	// Texturas de Pirámide
	PiramideTexture = Texture("Textures/TexturePiramide.jpg");
	PiramideTexture.LoadTextureA();
	SerpTexture = Texture("Textures/TextureSerp.jpg");
	SerpTexture.LoadTextureA();

	//letrero ENRIQUE
	//Puerta
	PuertaTexture = Texture("Textures/DoorTexture_Color_3.png");
	PuertaTexture.LoadTextureA();

	LetreroTexture = Texture("Textures/Letrero.png");
	LetreroTexture.LoadTextureA();

	// Cargando el modelo del camino
	CaminoTexture = Texture("Textures/CaminoGrava.jpg");
	CaminoTexture.LoadTextureA();
	CaminoLodoTexture = Texture("Textures/camino.jpg");
	CaminoLodoTexture.LoadTextureA();

	// ----------------- NPCS -----------------

	Baljeet = Model();
	Baljeet.LoadModel("Models/Baljeet.obj");

	// ----------------- ENTORNO ------------------ 

	// Cabeza Olmeca
	CabezaOlmeca = Model();
	CabezaOlmeca.LoadModel("Models/CabezaOlmeca.obj");

	// RING 
	Ring_R = Model();
	Ring_R.LoadModel("Models/RingBoxeo/Ring.obj");
	Escaleras_R = Model();
	Escaleras_R.LoadModel("Models/RingBoxeo/Escaleras.obj");
	Lona_R = Model();
	Lona_R.LoadModel("Models/RingBoxeo/Lona.obj");

	// Columpios
	Estructura_C = Model();
	Estructura_C.LoadModel("Models/Columpios/EstructuraColumpios.obj");
	ColumpioIzq_C = Model();
	ColumpioIzq_C.LoadModel("Models/Columpios/ColumpioIzquierda.obj");
	ColumpioDer_C = Model();
	ColumpioDer_C.LoadModel("Models/Columpios/ColumpioDerecha.obj");

	// Mesa Picnic
	MesaPicnic = Model();
	MesaPicnic.LoadModel("Models/mesaPicnic.obj");

	// Baño portatil
	CuerpoBano = Model();
	CuerpoBano.LoadModel("Models/Bano/CuerpoBano.obj");
	PuertaBano = Model();
	PuertaBano.LoadModel("Models/Bano/PuertaBano.obj");
	TapaBano = Model();
	TapaBano.LoadModel("Models/Bano/TapaBano.obj");

	// Fuente
	CuerpoFuente = Model();
	CuerpoFuente.LoadModel("Models/Decoracion/CuerpoFuente.obj");
	Fuente = Model();
	Fuente.LoadModel("Models/Decoracion/Fuente.obj");

	// Puerta JOSHUA
	PuertaIzq = Model();
	PuertaIzq.LoadModel("Models/puertaIzqJoshua.obj");
	PuertaDer = Model();
	PuertaDer.LoadModel("Models/puertaDerJoshua.obj");
	Arco = Model();
	Arco.LoadModel("Models/arcoJoshua.dae");
	CartelPuerta = Model();
	CartelPuerta.LoadModel("Models/letreroJoshua.dae");

	// Puerta Enrique
	//Modelo de puerta
	Cartel_M = Model();
	Cartel_M.LoadModel("Models/CartelEnrique.dae");
	Arco_M = Model();
	Arco_M.LoadModel("Models/ArcoEnrique.dae");
	PuertaDer_M = Model();
	PuertaDer_M.LoadModel("Models/PuertaDerEnrique.dae");
	PuertaIzq_M = Model();
	PuertaIzq_M.LoadModel("Models/PuertaIzqEnrique.dae");

	// Modelos de Pirámide y Cubo
	//Piramide
	BasePiradime_M = Model();
	BasePiradime_M.LoadModel("Models/BasePiramide.obj");
	CupulaPiramide_M = Model();
	CupulaPiramide_M.LoadModel("Models/CupulaPiramide.dae");

	//Seguimiento de camara prueba Quique
	Cubo_M = Model();
	Cubo_M.LoadModel("Models/Cubo.dae");

	//SKYBOX DÍA
	std::vector<std::string> skyboxFacesDia;
	skyboxFacesDia.push_back("Textures/Skybox/Dia/nx.jpg");
	skyboxFacesDia.push_back("Textures/Skybox/Dia/px.jpg");
	skyboxFacesDia.push_back("Textures/Skybox/Dia/ny.jpg");
	skyboxFacesDia.push_back("Textures/Skybox/Dia/py.jpg");
	skyboxFacesDia.push_back("Textures/Skybox/Dia/nz.jpg");
	skyboxFacesDia.push_back("Textures/Skybox/Dia/pz.jpg");
	skyboxDia = Skybox(skyboxFacesDia);

	//SKYBOX NOCHE
	std::vector<std::string> skyboxFacesNoche;
	skyboxFacesNoche.push_back("Textures/Skybox/Noche/nx.jpg");
	skyboxFacesNoche.push_back("Textures/Skybox/Noche/px.jpg");
	skyboxFacesNoche.push_back("Textures/Skybox/Noche/ny.jpg");
	skyboxFacesNoche.push_back("Textures/Skybox/Noche/py.jpg");
	skyboxFacesNoche.push_back("Textures/Skybox/Noche/nz.jpg");
	skyboxFacesNoche.push_back("Textures/Skybox/Noche/pz.jpg");
	skyboxNoche = Skybox(skyboxFacesNoche);

	//SKYBOX TARDE O AMANECER
	std::vector<std::string> skyboxFacesAMAT;
	skyboxFacesAMAT.push_back("Textures/Skybox/Trancision/nx.jpg");
	skyboxFacesAMAT.push_back("Textures/Skybox/Trancision/px.jpg");
	skyboxFacesAMAT.push_back("Textures/Skybox/Trancision/ny.jpg");
	skyboxFacesAMAT.push_back("Textures/Skybox/Trancision/py.jpg");
	skyboxFacesAMAT.push_back("Textures/Skybox/Trancision/nz.jpg");
	skyboxFacesAMAT.push_back("Textures/Skybox/Trancision/pz.jpg");
	skyboxAMAT = Skybox(skyboxFacesAMAT);

	// Skybox original
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/nx.jpg");
	skyboxFaces.push_back("Textures/Skybox/px.jpg");
	skyboxFaces.push_back("Textures/Skybox/ny.jpg");
	skyboxFaces.push_back("Textures/Skybox/py.jpg");
	skyboxFaces.push_back("Textures/Skybox/nz.jpg");
	skyboxFaces.push_back("Textures/Skybox/pz.jpg");
	skybox = Skybox(skyboxFaces);


	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	// Luz para ciclo día/noche
	mainLight = DirectionalLight(
		0.8, 0.8, 0.4,
		0.3, 0.4,
		0.3, -1.0, 0.5
	);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	//Movimientos base para cada transformación de las puertas
	movOffset = 6.0f;
	rotdeslizamientoOffset = 0.12f;

	glm::vec3 lowerLight(0.0f, 0.0f, 0.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

	//Para el seguimiento de la camara
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosForShader;
	glm::vec3 cameraDirForShader;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//< >
		angulovaria += 5.0f * deltaTime;

		//dragonavance
		dragonavance -= 0.1f * deltaTime;
		/* Animación en Loop Se ejecuta de forma continua mientras la aplicación está activa
		Si la animación no es el loop, y se puede iniciar varias veces, el estado final y el estado inicial
		deben de ser el mismo, o agregar elementos para que no se vea que los modelos desaparecen
		o aparecen de la nada.
		*/

		// Animación que se activa al presionar la tecla F, permite abrir o cerrar las puertas.
		if (mainWindow.getAbrirCerrarPuerta())
		{
			if (rotacion > 0.0f)
			{
				rotacion -= movOffset * deltaTime;
				deslizamiento -= rotdeslizamientoOffset * deltaTime;
			}
		}

		else
		{
			if (rotacion < 90.0f)
			{
				rotacion += movOffset * deltaTime;
				deslizamiento += rotdeslizamientoOffset * deltaTime;
			}
		}

		// Lógica de control de cámara con seguimiento
		//Recibir eventos del usuario
		glfwPollEvents();
		if (!mainWindow.getCamStatus())
		{
			camera.keyControl(mainWindow.getsKeys(), deltaTime);
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		}

		if (mainWindow.getCamStatus())
		{
			// Mover el cubo en un círculo
			float radius = 10.0f;
			float speed = 0.5f;
			cubePosition.x = sin(now * speed) * radius;
			cubePosition.z = cos(now * speed) * radius;
		}

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Lógica de Skybox
		skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);

		/*float tiempo = glfwGetTime();
		float ciclo = (sin(tiempo * 0.08f) + 1.0f) / 2.0f; // oscila entre 0 y 1

		glm::vec3 colorDia(1.0f, 0.95f, 0.8f);
		glm::vec3 colorNoche(0.2f, 0.3f, 0.6f);

		glm::vec3 colorActual = glm::mix(colorNoche, colorDia, ciclo);

		float intensidadAmb = glm::mix(0.05f, 0.4f, ciclo);
		float intensidadDif = glm::mix(0.1f, 0.8f, ciclo);

		glm::vec3 direccionLuz = glm::normalize(glm::vec3(
			sin(tiempo * 0.01f),
			-cos(tiempo * 0.01f),
			-0.3f
		));

		if (ciclo >= 0.6)
		{
			skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (ciclo <= 0.4f)
		{
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else {
			skyboxAMAT.DrawSkybox(camera.calculateViewMatrix(), projection);
		}*/

		/*mainLight = DirectionalLight(
			colorActual.r, colorActual.g, colorActual.b,
			intensidadAmb, intensidadDif,
			direccionLuz.x, direccionLuz.y, direccionLuz.z
		);*/


		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation(); // para la textura con movimiento

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();


		// Lógica de Matriz de Vista con seguimiento
		// --- Lógica de Cámara de Seguimiento --------------------------------
		if (mainWindow.getCamStatus())
		{
			//se define el offset de la camara
			glm::vec3 cameraOffset = glm::vec3(0.0f, 5.0f, 15.0f); //Se modifica la distancia de la camara
			cameraPosForShader = cubePosition + cameraOffset;
			cameraDirForShader = glm::normalize(cubePosition - cameraPosForShader);

			//Se usa lookAt para la matriz de la camara
			viewMatrix = glm::lookAt(cameraPosForShader, cubePosition, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else
		{
			// En caso de acabar la animación seguir con el movimeinto normal de la camara
			viewMatrix = camera.calculateViewMatrix();
			cameraPosForShader = camera.getCameraPosition();
			cameraDirForShader = camera.getCameraDirection();
		}

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniform3f(uniformEyePosition, cameraPosForShader.x, cameraPosForShader.y, cameraPosForShader.z);
		// luz ligada a la cámara de tipo flash
		lowerLight = cameraPosForShader;
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, cameraDirForShader);
		//------------------------------------------------------


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		//Reinicializando variables cada ciclo de reloj
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		// ---------------------- CAMINO ---------------------

		// CAMINO EN EL SPAWN
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.95f, -150.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		CaminoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();*/

		// Instancia del camino spawn - zona de comida
		for (int i = 0; i < 2; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-150.0f, -1.95f, -120.0f + (i * 20)));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			CaminoTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[2]->RenderMesh();
		}

		for (int i = 0; i < 2; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-150.0f, -1.95f, -75.0f + (i * 30)));
			model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.5f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			CaminoLodoTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[2]->RenderMesh();
		}

		// --- INICIO DE OBJETOS ---
		//Piramide con jeraruquía -------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiramideTexture.UseTexture();
		BasePiradime_M.RenderModel();

		//Cupula de piramide
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 2.688f, 0.406f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiramideTexture.UseTexture();
		CupulaPiramide_M.RenderModel();

		//Prueba del cubo
		model = glm::mat4(1.0);
		model = glm::translate(model, cubePosition);
		modelaux = model;
		//									x	  y		z							
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cubo_M.RenderModel();
		// --- FIN DE OBJETOS ---


		// ----------------- NPCS -----------------

		//  Baljeet
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Baljeet.RenderModel();

		// ----------------- ENTORNO -----------------------

		//MESA PICNIC 1, derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 0.6f, -80.0f));
		modelaux = model;
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaPicnic.RenderModel();

		//MESA PICNIC 2, derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-165.0f, 0.6f, -65.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaPicnic.RenderModel();

		//MESA PICNIC 3, derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 0.6f, -50.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaPicnic.RenderModel();

		//MESA PICNIC 4. izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 0.6f, -80.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaPicnic.RenderModel();

		//MESA PICNIC 5, izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-135.0f, 0.6f, -65.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaPicnic.RenderModel();

		//MESA PICNIC 6, izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 0.6f, -50.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaPicnic.RenderModel();

		// CuerpoFuente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.75f, -65.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoFuente.RenderModel();

		// Fuente
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fuente.RenderModel();

		//BAÑO
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-170.0f, -1.6f, -120.0f + (i * 7.5f)));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CuerpoBano.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			TapaBano.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PuertaBano.RenderModel();
		}

		//----------------- RING DE BOXEO -----------------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ring_R.RenderModel();

		model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, 40.0f, 40.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lona_R.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Escaleras_R.RenderModel();

		// ------------------ Estructura columpios ----------------------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Estructura_C.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ColumpioIzq_C.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ColumpioDer_C.RenderModel();

		//---------------- Cabeza olmeca ----------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.8f, -130.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CabezaOlmeca.RenderModel();

		//----------------- Puerta JOSHUA --------------------

		//Definición del arco de la puerta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, -1.8f, -140.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(10.0f, 3.84f, 0.58f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arco.RenderModel();

		//Definición del cartel de la puerta
		model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, -1.8f, -15.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 3.84f, 0.58f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CartelPuerta.RenderModel();

		//Definición de la puerta izquierda, ABRE
		//Jerarquía
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.214f, -0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotacion * toRadians, glm::vec3(0.0f, 0.0f, 1.0f)); // ABRE Y CIERRA CON F
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaIzq.RenderModel();

		//Definición de la puerta derecha, DESLIZA
		//Jerarquía
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.5f, 0.082f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f + deslizamiento, 0.0f, 0.0f)); // ABRE Y CIERRA CON F
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaDer.RenderModel();

		/*color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));*/
		//Agave ¿qué sucede si lo renderizan antes del coche y de la pista?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		//----------------- Puerta ENRIQUE --------------------

		//Modelo de puerta
		//Arco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, -2.0f, -140.0f));
		modelaux = model;
		// 								//x    y      z							
		model = glm::scale(model, glm::vec3(2.0f, 6.5, 0.8f));

		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaTexture.UseTexture();
		Arco_M.RenderModel();

		//Puerta izquierda
		model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0f));
		//Abrir por rotación 
		//model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 6.5, 0.8f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 10.0f, 5.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 10.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaIzq_M.RenderModel();

		//Puerta Derecha
		model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.5f));
		//model = glm::scale(model, glm::vec3(1.0f, 10.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//Abrir por desplazamiento
		model = glm::translate(model, glm::vec3(-2.0f + mainWindow.getmuevex(), 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 6.5, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaDer_M.RenderModel();

		//Cartel
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -3.0f));//20.5f));
		model = glm::scale(model, glm::vec3(2.0f, 6.8f, 0.2f));
		//model = glm::scale(model, glm::vec3(0.5f, 10.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cartel_M.RenderModel();

		//Desplazamiento cartel.

		toffsetnumerocambiau += 0.0005; // Solo se baja el número de offset de cada número 
		if (toffsetnumerocambiau > 1.0)
			toffsetnumerocambiau = 0.0;
		toffsetnumerov = 0.0;
		toffset = glm::vec2(toffsetnumerocambiau, toffsetnumerov);
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.6f, 16.0f, -2.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 6.5, 0.8f));
		model = glm::scale(model, glm::vec3(10.0f, 0.6f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		LetreroTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();


		//textura con movimiento
		//Importantes porque la variable uniform no podemos modificarla directamente
		/*toffsetflechau += 0.001;
		toffsetflechav = 0.00;
		//para que no se desborde la variable
		if (toffsetflechau > 1.0)
			toffsetflechau = 0.0;
		//if (toffsetv > 1.0)
		//	toffsetv = 0;
		//printf("\ntfosset %f \n", toffsetu);
		//pasar a la variable uniform el valor actualizado
		toffset = glm::vec2(toffsetflechau, toffsetflechav);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		FlechaTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();*/


		//Movimiento sobre la textura del texto PROYECTO CGEIHC 
		/*
		¿Cómo hacer para que sea a una velocidad visible?
		*/
		toffsetnumerocambiau += 0.0005;
		if (toffsetnumerocambiau > 1.0)
			toffsetnumerocambiau = 0.0;
		toffsetnumerov = 0.0;

		toffset = glm::vec2(toffsetnumerocambiau, toffsetnumerov);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 14.08f, -142.87f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(5.7f, 1.428f, 1.428f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TipografiaBackyardigans.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[7]->RenderMesh();

		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}