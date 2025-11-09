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


//variables para animación de pizza
float abrircaja = 0.0f;
float elevacionRebanada = 0.0f;
float elevacionOffset;
float abrirPizzaOffset = 0.0f;

//Animación perry
float abrirGuarida = 0.0f;
float movPerry = 0.0f;
float correrOffset = 0.0f;
float elevarPuerta = 0.0f;
float elevarPuerta2 = 0.0f;
float rotaPerry = 0.0f;
bool Corre = true;
bool puertaAbierta = false;

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

//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

// Variables para ciclo día/noche
float tiempoDia = 0.0f;       // contador del tiempo del día
float velocidadCiclo = 0.0009f;    // velocidad de transición (ajústala)
bool esNoche = true;
float velocidad;

//Para el ovni
glm::vec3 centroPiramide = glm::vec3(-80.0f, -1.5f, -25.0f);
float alturaBaseOvni = 50.0f;

//Auxiliaresa
float radioOrbita = 30.0f;
float velocidadOrbita = 0.5f;
float amplitudVertical = 10.0f; //Pa subir y bajar el ovni
float velocidadVertical = 1.0f;

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
Texture OnviTexture;
Texture VidrioOvniTexture;

//Lamparas
Texture lampTexture;
Texture lampBJoshuaTexture;
Texture lampNJoshuaTexture;

// Texturas de los backyardigans - PUERTA JOSHUA
Texture TipografiaBackyardigans;

//Se añade una textura de un camino
Texture CaminoTexture;
Texture CaminoLodoTexture;

//Letrero PUERTA ENRIQUE
//Puerta
Texture PuertaTexture;
Texture LetreroTexture;

//Letrero para interacciones
Texture LetreroInteracciones;

// ----------------- NPCS ----------------- //
Model Baljeet;
Model PerryTorso;
Model PerryMI;	//mano izq
Model PerryMD;	//mano der
Model PerryPI;	//pie izq
Model PerryPD;	//pie der
Model PerryS;	//sombrero
Model PerryC;	//Cola

Model BuffordTorso; 
Model BuffordMI;	//Mano izq
Model BuffordMD;	//Mano der
Model BuffordPI;	//Pie izq
Model BuffordPD;	//Pie der
Model BuffordCabeza;
Model BuffordChef;	//Sombrero de chef

Model TyroneTorso;
Model TyroneCabeza;
Model TyroneMI;
Model TyroneMD;
Model TyronePD;
Model TyronePI;

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

// Modelos bano portatil
Model CuerpoBano;
Model TapaBano;
Model PuertaBano;

// Fuente
Model CuerpoFuente;
Model Fuente;

// Valla
Model Valla;

//Lampara
Model Lampara;
Model LamparaJoshua;

//Silla coca cola
Model SillaCC;

//Arbol con abertura
Model ArbolS;
Model CopaArbolS;
Model EntradaArbolS;

//Carro HotDogs
Model CarroHotDogs;
Model Mostaza;
Model Ketchup;
Model TapaHotDogs;
Model HotDog;
Model SalsaMostaza;

//Model PuestoPiza
Model PuestoPizza;
Model MaderaPuesto;
Model CajaPizza;
Model Pizza;
Model RebanadaPizza;
Model TapaCajaPizza;

//Plato
Model Plato;

// Banco
Model BancoMadera;
Model BancoPatas;

//Arbusto
Model Arbusto;

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

//Ovni
Model Ovni_M;
Model VidrioOvni_M;


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

//función para teclado de keyframes 
void inputKeyframes(bool* keys);

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

///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;

//NEW// Keyframes
float posXHotDog = -168.5, posYHotDog = 0.2, posZHotDog = -85.3;
float	movHotDog_x = 0.0f, movHotDog_y = 0.0f, movHotDog_z = 0.0;
float giroHotDog = 0;

float posXMostaza = -169.0, posYMostaza = -1.6, posZMostaza = -85.0;
float	movMostaza_x = 0.0f, movMostaza_y = 0.0f, movMostaza_z = 0.0;
float giroMostaza = 0;

#define MAX_FRAMES 100 //Número de cuadros máximos
int i_max_steps = 100; //Número de pasos entre cuadros para interpolación, a mayor número , más lento será el movimiento
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movHotDog_x;		//Variable para PosicionX
	float movHotDog_y;		//Variable para PosicionY
	float movHotDog_z;		//Variable para PosicionZ
	float movHotDog_xInc;		//Variable para IncrementoX
	float movHotDog_yInc;		//Variable para IncrementoY
	float movHotDog_zInc;		//Variable para IncrementoZ
	float giroHotDog;		//Variable para giroHotDog
	float giroHotDogInc;		//Variable para IncrementogiroHotDog

	float movMostaza_x;		//Variable para PosicionX
	float movMostaza_y;		//Variable para PosicionY
	float movMostaza_z;		//Variable para PosicionZ
	float movMostaza_xInc;		//Variable para IncrementoX
	float movMostaza_yInc;		//Variable para IncrementoY
	float movMostaza_zInc;		//Variable para IncrementoZ
	float giroMostaza;		//Variable para giroMostaza
	float giroMostazaInc;		//Variable para IncrementogiroMostaza
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//El número de cuadros guardados actualmente desde 0 para no sobreescribir
bool play = false;
int playIndex = 0;

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movHotDog_x = movHotDog_x;
	KeyFrame[FrameIndex].movHotDog_y = movHotDog_y;
	KeyFrame[FrameIndex].movHotDog_z = movHotDog_z;
	KeyFrame[FrameIndex].giroHotDog = giroHotDog;

	KeyFrame[FrameIndex].movMostaza_x = movMostaza_x;
	KeyFrame[FrameIndex].movMostaza_y = movMostaza_y;
	KeyFrame[FrameIndex].movMostaza_z = movMostaza_z;
	KeyFrame[FrameIndex].giroMostaza = giroMostaza;
	//Se agregan nuevas líneas para guardar más variables si es necesario

	// Crea el archivo si no existe
	/*ofstream archivo(nombreArchivo, ios::app); // modo append

	if (!archivo) {
		cerr << "Error al crear el archivo.\n";
	}
	else {
		archivo << "KeyFrame: [" << FrameIndex << "] Movimiento del Helicoptero en x: " << movHotDog_x << "\n";
		archivo << "KeyFrame: [" << FrameIndex << "] Movimiento del Helicoptero en y: " << movHotDog_y << "\n";
		archivo << "KeyFrame: [" << FrameIndex << "] Giro del Helicoptero: " << giroHotDog << "\n";

		archivo.close();
		cout << "Datos añadidos correctamente.\n";
	}



	//no volatil,se requiere agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;*/
}

void resetElements(void) //Tecla 0
{

	movHotDog_x = KeyFrame[0].movHotDog_x;
	movHotDog_y = KeyFrame[0].movHotDog_y;
	movHotDog_z = KeyFrame[0].movHotDog_z;
	giroHotDog = KeyFrame[0].giroHotDog;

	movMostaza_x = KeyFrame[0].movMostaza_x;
	movMostaza_y = KeyFrame[0].movMostaza_y;
	movMostaza_z = KeyFrame[0].movMostaza_z;
	giroMostaza = KeyFrame[0].giroMostaza;
}

void interpolation(void)
{
	KeyFrame[playIndex].movHotDog_xInc = (KeyFrame[playIndex + 1].movHotDog_x - KeyFrame[playIndex].movHotDog_x) / i_max_steps;
	KeyFrame[playIndex].movHotDog_yInc = (KeyFrame[playIndex + 1].movHotDog_y - KeyFrame[playIndex].movHotDog_y) / i_max_steps;
	KeyFrame[playIndex].movHotDog_zInc = (KeyFrame[playIndex + 1].movHotDog_z - KeyFrame[playIndex].movHotDog_z) / i_max_steps;
	KeyFrame[playIndex].giroHotDogInc = (KeyFrame[playIndex + 1].giroHotDog - KeyFrame[playIndex].giroHotDog) / i_max_steps;

	KeyFrame[playIndex].movMostaza_xInc = (KeyFrame[playIndex + 1].movMostaza_x - KeyFrame[playIndex].movMostaza_x) / i_max_steps;
	KeyFrame[playIndex].movMostaza_yInc = (KeyFrame[playIndex + 1].movMostaza_y - KeyFrame[playIndex].movMostaza_y) / i_max_steps;
	KeyFrame[playIndex].movMostaza_zInc = (KeyFrame[playIndex + 1].movMostaza_z - KeyFrame[playIndex].movMostaza_z) / i_max_steps;
	KeyFrame[playIndex].giroMostazaInc = (KeyFrame[playIndex + 1].giroMostaza - KeyFrame[playIndex].giroMostaza) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animación entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animación con último frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolación del próximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animación
			movHotDog_x += KeyFrame[playIndex].movHotDog_xInc;
			movHotDog_y += KeyFrame[playIndex].movHotDog_yInc;
			movHotDog_z += KeyFrame[playIndex].movHotDog_zInc;
			giroHotDog += KeyFrame[playIndex].giroHotDogInc;

			movMostaza_x += KeyFrame[playIndex].movMostaza_xInc;
			movMostaza_y += KeyFrame[playIndex].movMostaza_yInc;
			movMostaza_z += KeyFrame[playIndex].movMostaza_zInc;
			giroMostaza += KeyFrame[playIndex].giroMostazaInc;
			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	//Posición del cubo para que se calcule cada frame
	glm::vec3 ovniPos = glm::vec3(-80.0f, 50.0f, -25.0f);

	// Cáamara
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

	//Textura de Ovni
	OnviTexture = Texture("Textures/OvniTexture.jpg");
	OnviTexture.LoadTextureA();
	VidrioOvniTexture = Texture("Textures/VidrioOvni.jpg");
	VidrioOvniTexture.LoadTextureA();

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

	//Lampara
	lampTexture = Texture("Textures/Lamp.png");
	lampTexture.LoadTextureA();

	lampBJoshuaTexture = Texture("Textures/imagenBlanca.png");
	lampBJoshuaTexture.LoadTextureA();
	lampNJoshuaTexture = Texture("Textures/imagenNegra.png");
	lampNJoshuaTexture.LoadTextureA();

	// ----------------- NPCS -----------------

	Baljeet = Model();
	Baljeet.LoadModel("Models/Baljeet.obj");

	PerryTorso = Model();
	PerryTorso.LoadModel("Models/NPCS/Perry/PerryTorso.obj");
	PerryMI = Model();
	PerryMI.LoadModel("Models/NPCS/Perry/PerryManoIzq.Obj");
	PerryMD = Model();
	PerryMD.LoadModel("Models/NPCS/Perry/PerryManoDer.obj");
	PerryPI = Model();
	PerryPI.LoadModel("Models/NPCS/Perry/PerryPieIzq.obj");
	PerryPD = Model();
	PerryPD.LoadModel("Models/NPCS/Perry/PerryPieDer.obj");
	PerryS = Model();
	PerryS.LoadModel("Models/NPCS/Perry/PerrySombrero.obj");
	PerryC = Model();
	PerryC.LoadModel("Models/NPCS/Perry/PerryCola.obj");

	BuffordTorso = Model();
	BuffordTorso.LoadModel("Models/NPCS/Bufford/TorsoBufford.obj");
	BuffordMI = Model();
	BuffordMI.LoadModel("Models/NPCS/Bufford/BrazoIzqBufford.obj");
	BuffordMD = Model();
	BuffordMD.LoadModel("Models/NPCS/Bufford/BrazoDerBufford.obj");
	BuffordPI = Model();
	BuffordPI.LoadModel("Models/NPCS/Bufford/PieIzqBufford.obj");
	BuffordPD = Model();
	BuffordPD.LoadModel("Models/NPCS/Bufford/PieDerBufford.obj");
	BuffordCabeza = Model();
	BuffordCabeza.LoadModel("Models/NPCS/Bufford/CabezaBufford.obj");
	BuffordChef = Model();
	BuffordChef.LoadModel("Models/NPCS/Bufford/SombreroBufford.obj");


	// Tyrone
	TyroneTorso = Model();
	TyroneTorso.LoadModel("Models/NPCS/Tyrone/TyroneTorso.obj");
	TyroneCabeza = Model();
	TyroneCabeza.LoadModel("Models/NPCS/Tyrone/TyroneCabeza.obj");
	TyroneMI = Model();
	TyroneMI.LoadModel("Models/NPCS/Tyrone/TyroneMI.obj");
	TyroneMD = Model();
	TyroneMD.LoadModel("Models/NPCS/Tyrone/TyroneMD.obj");
	TyronePD = Model();
	TyronePD.LoadModel("Models/NPCS/Tyrone/TyronePD.obj");
	TyronePI = Model();
	TyronePI.LoadModel("Models/NPCS/Tyrone/TyronePI.obj");
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

	//Arbol Con apertura
	ArbolS = Model();
	ArbolS.LoadModel("Models/Decoracion/ArbolSecreto.obj");
	CopaArbolS = Model();
	CopaArbolS.LoadModel("Models/Decoracion/CopaArbolS.obj");
	EntradaArbolS = Model();
	EntradaArbolS.LoadModel("Models/Decoracion/EntradaArbolS.obj");


	// Carro de hotdogs
	CarroHotDogs = Model();
	CarroHotDogs.LoadModel("Models/ZonaComida/CarroHotDog.obj");
	TapaHotDogs = Model();
	TapaHotDogs.LoadModel("Models/ZonaComida/TapaGrandeHD.obj");
	Mostaza = Model();
	Mostaza.LoadModel("Models/ZonaComida/Mostaza.obj");
	Ketchup = Model();
	Ketchup.LoadModel("Models/ZonaComida/Ketchup.obj");
	HotDog = Model();
	HotDog.LoadModel("Models/ZonaComida/HotDog.obj");
	SalsaMostaza = Model();
	SalsaMostaza.LoadModel("Models/ZonaComida/SalsaMostaza.obj");

	//Puesto de Pizza
	PuestoPizza = Model();
	PuestoPizza.LoadModel("Models/ZonaComida/PuestoRojo.obj");
	MaderaPuesto = Model();
	MaderaPuesto.LoadModel("Models/ZonaComida/MesaPuestoRojo.obj");

	//Pizza
	CajaPizza = Model();
	CajaPizza.LoadModel("Models/ZonaComida/Caja.obj");
	Pizza = Model();
	Pizza.LoadModel("Models/ZonaComida/Pizza.obj");
	RebanadaPizza = Model();
	RebanadaPizza.LoadModel("Models/ZonaComida/RebanadaPizza.obj");
	TapaCajaPizza = Model();
	TapaCajaPizza.LoadModel("Models/ZonaComida/CajaPizza.obj");

	//Plato 
	Plato = Model();
	Plato.LoadModel("Models/ZonaComida/Plato.obj");

	//Banco
	BancoMadera = Model();
	BancoMadera.LoadModel("Models/Decoracion/BancoMadera.obj");
	BancoPatas = Model();
	BancoPatas.LoadModel("Models/Decoracion/BancoPatas.obj");

	//Arbusto
	Arbusto = Model();
	Arbusto.LoadModel("Models/Decoracion/Arbusto.obj");

	//Lampara
	Lampara = Model();
	Lampara.LoadModel("Models/Lampara.dae");

	LamparaJoshua = Model();
	LamparaJoshua.LoadModel("Models/LamparaJoshua.dae");

	// Fuente
	CuerpoFuente = Model();
	CuerpoFuente.LoadModel("Models/Decoracion/CuerpoFuente.obj");
	Fuente = Model();
	Fuente.LoadModel("Models/Decoracion/Fuente.obj");

	// Valla
	Valla = Model();
	Valla.LoadModel("Models/Decoracion/Valla.obj");

	//Ring de boxeo
	SillaCC = Model();
	SillaCC.LoadModel("Models/RingBoxeo/SillaCC.obj");

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
	CupulaPiramide_M.LoadModel("Models/CupulaPiramide.obj");
	Serpientes_M = Model();
	Serpientes_M.LoadModel("Models/SerpientePiramide.obj");

	//UFO
	Ovni_M = Model();
	Ovni_M.LoadModel("Models/BaseUFO.obj");
	VidrioOvni_M = Model();
	VidrioOvni_M.LoadModel("Models/VidrioUFO.obj");

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


	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	// Luz para ciclo día/noche
	mainLight = DirectionalLight(
		1.0, 1.0, 1.0,
		0.3, 0.4,
		0.3, -1.0, 0.5
	);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
		// ---Lampara------

	//Lampara 1
	pointLights[0] = PointLight(1.0f, 0.75f, 0.0f,
		0.05f, 0.01f,
		//		 K_c	k_l	  k_q
		-180.0f, 7.0f, -75.0f,
		//0.3f, 0.2f, 0.1f);
		1.0f, 0.09f, 0.032f);
	pointLightCount++;

	//Lampara 2
	pointLights[1] = PointLight(1.0f, 0.75f, 0.0f,
		0.05f, 0.1f,
		//		 K_c	k_l	  k_q
		-165.0f, -1.5f, -30.0f,
		//0.3f, 0.2f, 0.1f);
		1.0f, 0.09f, 0.032f);
	pointLightCount++;

	//Lampara 3
	pointLights[2] = PointLight(1.0f, 0.75f, 0.0f,
		0.05f, 0.1f,
		//		 K_c	k_l	  k_q
		-140.0f, -1.5f, -100.0f,
		1.0f, 0.09f, 0.032f);
	pointLightCount++;

	//Lampara 4
	pointLights[3] = PointLight(1.0f, 0.75f, 0.0f,
		0.05f, 0.1f,
		//		 K_c	k_l	  k_q
		-135.0f, -1.5f, -30.0f,
		//0.3f, 0.2f, 0.1f);
		1.0f, 0.09f, 0.032f);
	pointLightCount++;

	PointLight activePointLights[MAX_POINT_LIGHTS];

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

	//Para la lampara
	PointLight lamparaON = pointLights[0];

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	movPerry = -163.0f;
	//Movimientos base para cada transformación de las puertas
	movOffset = 6.0f;
	correrOffset = 0.1;
	abrirPizzaOffset = 3.0f;
	rotdeslizamientoOffset = 0.12f;
	elevacionOffset = 0.01;
	glm::vec3 posHotDog = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 posMostaza = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 lowerLight(0.0f, 0.0f, 0.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

	//Para el seguimiento de la camara
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosForShader;
	glm::vec3 cameraDirForShader;

	//---------PARA TENER KEYFRAMES GUARDADOS NO VOLATILES QUE SIEMPRE SE UTILIZARAN SE DECLARAN AQUÍ
	KeyFrame[0].movHotDog_x = 0.0f;
	KeyFrame[0].movHotDog_y = 1.0f;
	KeyFrame[0].movHotDog_z = 0.0f;
	KeyFrame[0].giroHotDog = 0;

	KeyFrame[0].movMostaza_x = 0.43f;	//z
	KeyFrame[0].movMostaza_y = 0.75f;	//y
	KeyFrame[0].movMostaza_z = 0.5f;	//x
	KeyFrame[0].giroMostaza = 0;

	KeyFrame[1].movHotDog_x = 0.0f;
	KeyFrame[1].movHotDog_y = 1.5f;
	KeyFrame[1].movHotDog_z = 1.0f;
	KeyFrame[1].giroHotDog = 0;

	KeyFrame[1].movMostaza_x = 0.86f;	//z
	KeyFrame[1].movMostaza_y = 1.5f;	//y
	KeyFrame[1].movMostaza_z = 1.0f;	//x
	KeyFrame[1].giroMostaza = 18;

	KeyFrame[2].movHotDog_x = 0.0f;
	KeyFrame[2].movHotDog_y = 2.0f;
	KeyFrame[2].movHotDog_z = -1.0f;
	KeyFrame[2].giroHotDog = 0.0f;

	KeyFrame[2].movMostaza_x = 1.29f;	//z
	KeyFrame[2].movMostaza_y = 2.25f;	//y
	KeyFrame[2].movMostaza_z = 1.5f;	//x
	KeyFrame[2].giroMostaza = 36.0f;


	KeyFrame[3].movHotDog_x = 0.0f;
	KeyFrame[3].movHotDog_y = 2.5f;
	KeyFrame[3].movHotDog_z = 0.0f;
	KeyFrame[3].giroHotDog = 0.0f;

	KeyFrame[3].movMostaza_x = 1.72f;	//z
	KeyFrame[3].movMostaza_y = 3.0f;	//y
	KeyFrame[3].movMostaza_z = 2.0f;	//x
	KeyFrame[3].giroMostaza = 54.0f;


	KeyFrame[4].movHotDog_x = 0.0f;
	KeyFrame[4].movHotDog_y = 2.5f;
	KeyFrame[4].movHotDog_z = 0.0f;
	KeyFrame[4].giroHotDog = 0.0f;

	KeyFrame[4].movMostaza_x = 2.15f;	//z
	KeyFrame[4].movMostaza_y = 3.75f;	//y
	KeyFrame[4].movMostaza_z = 2.5f;	//x
	KeyFrame[4].giroMostaza = 72.0f;

	KeyFrame[5].movHotDog_x = 0.0f;
	KeyFrame[5].movHotDog_y = 2.5f;
	KeyFrame[5].movHotDog_z = 0.0f;
	KeyFrame[5].giroHotDog = 0.0f;

	KeyFrame[5].movMostaza_x = 2.6f;	// z
	KeyFrame[5].movMostaza_y = 4.5f;	// y
	KeyFrame[5].movMostaza_z = 3.0f;	// x
	KeyFrame[5].giroMostaza = 90.0f;

	printf("\nTeclas para uso de Keyframes:\n1.-Presionar barra espaciadora para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");

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


		// Animación caja pizza
		if (mainWindow.getPizza()) 
		{
			if (abrircaja > 0.0f) 
			{
				abrircaja -= abrirPizzaOffset * deltaTime;
				elevacionRebanada -= elevacionOffset * deltaTime;
			}
		}
		else
		{
			if (abrircaja < 90.0f)
			{
				abrircaja += abrirPizzaOffset * deltaTime;
				elevacionRebanada += elevacionOffset * deltaTime;
			}
		}

		//Animación Perry
		if (Corre)
		{
			if (movPerry > -163) // -162.0
			{
				movPerry -= correrOffset * deltaTime;
				elevarPuerta += 0.001 * deltaTime;
				elevarPuerta2 -= 0.001 * deltaTime;
			}
			else
			{
				Corre = !Corre;
				rotaPerry += 180.0f;
				elevarPuerta += 0.001 * deltaTime;
				elevarPuerta2 -= 0.001 * deltaTime;
			}
		}

		else
		{
			if (movPerry < -136.0f) // -136.0
			{
				movPerry += correrOffset * deltaTime;
				elevarPuerta -= 0.001 * deltaTime;
				elevarPuerta2 += 0.001 * deltaTime;
			}
			else
			{
				Corre = !Corre;
				rotaPerry -= 180.0f;
				elevarPuerta -= 0.001 * deltaTime;
				elevarPuerta2 += 0.001 * deltaTime;
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
			// Mover el cubo en un circulo
			float radius = 10.0f;
			float speed = 0.5f;
			ovniPos.x = centroPiramide.x + sin(now * velocidadOrbita) * radioOrbita;
			ovniPos.z = centroPiramide.z + cos(now * velocidadOrbita) * radioOrbita;
			ovniPos.y = alturaBaseOvni + sin(now * velocidadVertical) * amplitudVertical;
		}

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

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
			cameraPosForShader = ovniPos + cameraOffset;
			cameraDirForShader = glm::normalize(ovniPos - cameraPosForShader);

			//Se usa lookAt para la matriz de la camara
			viewMatrix = glm::lookAt(cameraPosForShader, ovniPos, glm::vec3(0.0f, 1.0f, 0.0f));
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

		unsigned int activePointLightCount = 0;

		if (mainWindow.getprendida())
		{
			for (unsigned int i = 0; i < pointLightCount; i++)
			{
				activePointLights[activePointLightCount] = pointLights[i];
				activePointLightCount++;
			}

		}

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

		for (int i = 0; i < 8; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-135.0f + (i * 25), -1.95f, -112.0f));
			model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.25f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			CaminoTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[2]->RenderMesh();
		}

		// --- INICIO DE OBJETOS ---

		//Atractivo turistico
		for (int i = 0; i < 8; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(20.0f, -1.95f, -100.0f + (i * 30)));
			model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.5f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			CaminoTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[2]->RenderMesh();
		}

		//Piramide con jeraruquía -------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, -1.5f, -25.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiramideTexture.UseTexture();
		BasePiradime_M.RenderModel();

		//Cupula de piramide
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiramideTexture.UseTexture();
		CupulaPiramide_M.RenderModel();

		//Serpientes
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SerpTexture.UseTexture();
		Serpientes_M.RenderModel();

		//Ovni
		model = glm::mat4(1.0);
		model = glm::translate(model, ovniPos);
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		OnviTexture.UseTexture();
		Ovni_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.0f, 0.0f, -0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		VidrioOvniTexture.UseTexture();
		VidrioOvni_M.RenderModel();

		//Prueba del cubo
		/*model = glm::mat4(1.0);
		model = glm::translate(model, ovniPos);
		modelaux = model;
		//									x	  y		z
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cubo_M.RenderModel();
		Cubo_M.RenderModel();*/
		// --- FIN DE OBJETOS ---


		/*model = glm::mat4(1.0);
		model = glm::translate(model, cubePosition);
		modelaux = model;
		//									x	  y		z							
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cubo_M.RenderModel();*/
		// --- FIN DE OBJETOS ---


		// ----------------- NPCS -----------------

		//  Baljeet
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 2.0f, -145.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, -270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Baljeet.RenderModel();

		// PERRY EL ORNITORRINCO

		//posicion de perry dentro del arbol
		//model = glm::translate(model, glm::vec3(-164.5f, -2.0f, -94.8f));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + movPerry, -2.0f, -94.6f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, -270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotaPerry), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryTorso.RenderModel();

		
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryPI.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryPD.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryMI.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryMD.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryS.RenderModel();

		model = modelaux;
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PerryC.RenderModel();

		// BUFFORD CHEF

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -1.5f, -65.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, -270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotaPerry), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordTorso.RenderModel();


		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordPI.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordPD.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordMI.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordMD.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordCabeza.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BuffordChef.RenderModel();


		// TYRONE BACKYARDIGANS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, -2.0f, -150.0));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, -270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotaPerry), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TyroneTorso.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TyronePI.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TyronePD.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TyroneMI.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TyroneMD.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TyroneCabeza.RenderModel();



		// ----------------- ENTORNO -----------------------

		// ----------------- ZONA DE COMIDA ----------------- //


		//ARBOL

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -2.0f, -106.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -35 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolS.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CopaArbolS.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.6f + elevarPuerta));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EntradaArbolS.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -2.0f, -82.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 145 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolS.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CopaArbolS.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f + elevarPuerta2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EntradaArbolS.RenderModel();

		/*for (int i = 0; i < 2; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-175.0f + (i * 30), -2.0f, -75.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 45 * (i * 2) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CopaArbolS.RenderModel();

			/*model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EntradaArbolS.RenderModel();
		}*/


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

		//Banco 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-125.0f, -0.5f, -95.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoMadera.RenderModel();

		//Patas de banca
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoPatas.RenderModel();

		//Banco 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-115.0f, -0.5f, -95.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoMadera.RenderModel();
		//Patas de banca
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoPatas.RenderModel();

		//Banco 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-105.0f, -0.5f, -95.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoMadera.RenderModel();

		//Patas de banca
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoPatas.RenderModel();

		//Arbusto
		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-130.0f + (i * 10), -0.8f, -95.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Arbusto.RenderModel();
		}

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, -2.0f, -80.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolS.RenderModel();
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CopaArbolS.RenderModel();
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EntradaArbolS.RenderModel();

		//-------------------------------- Termino Conjunto 1 ---------------------------------

		//-------------------------------- Conjunto 2 ---------------------------------
		//ARBOL 2
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-75.0f + (i * 30), -2.0f, -75.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 45 + (i * 2) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CopaArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EntradaArbolS.RenderModel();
		}

		//Arbusto 2
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-60.0f + (i * 10), -0.8f, -95.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Arbusto.RenderModel();
		}

		//Bancos
		for (int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-55.0f + (i * 10), -0.5f, -95.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BancoMadera.RenderModel();
			//Patas de banca
			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BancoPatas.RenderModel();
		}

		//Arbusto 3
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-30.0f + (i * 10), -0.8f, -95.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Arbusto.RenderModel();
		}


		//Bancos 3
		for (int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-25.0f + (i * 10), -0.5f, -95.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BancoMadera.RenderModel();
			//Patas de banca
			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BancoPatas.RenderModel();
		}

		//-------------------------------- Termino Conjunto 2 ---------------------------------
		//-------------------------------- Conjunto 3 ---------------------------------
		//ARBOL 3
		for (int i = 0; i < 8; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-10.0f, -2.0f, -65.0f + (i * 30)));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 45 + (i * 2) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CopaArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EntradaArbolS.RenderModel();
		}

		//Arbusto 3
		for (int i = 0; i < 12; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.8f, -78.0f + (i * 10)));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Arbusto.RenderModel();
		}

		//Bancos
		for (int i = 0; i < 12; i++)
		{
			if ((i % 3) != 2)
			{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(0.0f, -0.5f, -73.0f + (i * 10)));
				model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
				modelaux = model;
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BancoMadera.RenderModel();
				//Patas de banca
				model = modelaux;
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BancoPatas.RenderModel();
			}

		}

		//Arbusto 4
		for (int i = 0; i < 6; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.8f, 70.0f + (i * 10)));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Arbusto.RenderModel();
		}

		//Bancos 4
		for (int i = 0; i < 5; i++)
		{
			if ((i % 3) != 2)
			{
				model = glm::mat4(1.0);
				model = glm::translate(model, glm::vec3(0.0f, -0.5f, 75.0f + (i * 10)));
				model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
				modelaux = model;
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BancoMadera.RenderModel();
				//Patas de banca
				model = modelaux;
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BancoPatas.RenderModel();
			}

		}

		//-------------------------------- Termino Conjunto 3 ---------------------------------
		//-------------------------------- Conjunto 4 ---------------------------------
		//ARBOL 5
		for (int i = 0; i < 12; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(35.0f, -2.0f, -75.0f + (i * 20)));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 45 + (i * 2) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CopaArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EntradaArbolS.RenderModel();
		}
		
		for (int i = 0; i < 34; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(35.0f, -1.5f, -95.0f + (i * 6.5)));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Valla.RenderModel();
		}
		//-------------------------------- Termino Conjunto 4 ---------------------------------

		//------------------------ Vallas y Arboles --------------------------
		//Vallas
		for (int i = 0; i < 5; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(6.0f + (i * 6.5), -1.5f, 125.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Valla.RenderModel();
		}

		//ARBOL 6
		for (int i = 0; i < 3; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-5.0f + (i * 15), -2.0f, 150.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 45 + (i * 2) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CopaArbolS.RenderModel();

			model = modelaux;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			EntradaArbolS.RenderModel();
		}

		//Vallas abajo
		for (int i = 0; i < 3; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(38.0f + (i * 6.5), -1.5f, -99.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Valla.RenderModel();
		}

		//Vallas abajo columpios
		for (int i = 0; i < 5; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(25.0f + (i * 6.5), -1.5f, -125.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Valla.RenderModel();
		}
		//--------------------------------------------------------------------


		// Carrito de hotdogs //
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-170.0f, -1.6f, -85.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarroHotDogs.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ketchup.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TapaHotDogs.RenderModel();

		model = glm::mat4(1.0);
		posMostaza = glm::vec3(posXMostaza + movMostaza_x, posYMostaza + movMostaza_y, posZMostaza + movMostaza_z);
		model = glm::translate(model, posMostaza);
		//model = glm::translate(model, glm::vec3(-170.0f, 1.2f, -85.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -(giroMostaza * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mostaza.RenderModel();

		


		//HOTDOG
		model = glm::mat4(1.0);
		posHotDog = glm::vec3(posXHotDog + movHotDog_x, posYHotDog + movHotDog_y, posZHotDog + movHotDog_z);
		model = glm::translate(model, posHotDog);
		//model = glm::translate(model, glm::vec3(-170.0f, 1.2f, -85.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, giroHotDog * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HotDog.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SalsaMostaza.RenderModel();

		// Puesto de pizza
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-175.0f, -1.5f, -52.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuestoPizza.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MaderaPuesto.RenderModel();


		// Pizza
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-177.0f, 2.6f, -62.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CajaPizza.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pizza.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f + elevacionRebanada));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RebanadaPizza.RenderModel();

		//Plato
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.8f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plato.RenderModel();

		
		/*model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -0.0f));
		model = glm::rotate(model, -30 - abrircaja * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));*/
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-177.3f, 2.48f, -62.65f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, abrircaja * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TapaCajaPizza.RenderModel();

		
		


		//----------------- RING DE BOXEO -----------------

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, -1.5f, -145.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		model = glm::rotate(model, -270 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//Siento que se puede reducir pero la neta así salio y ya no le quiero mover jajaja
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ring_R.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lona_R.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Escaleras_R.RenderModel();

		//Sillas derecha 
		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-30.0f, 1.1f, -136.5f - (i * 5)));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SillaCC.RenderModel();
		}
		
		//Sillas Izquierda
		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-70.0f, 1.1f, -136.5f - (i * 5)));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SillaCC.RenderModel();
		}

		//Sillas de atras
		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-42.0f - (i * 5), 1.1f, -165.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			SillaCC.RenderModel();
		}

		// ------------------ Estructura columpios ----------------------

		//Columpio 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.5f, -130.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
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

		//Columpio 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.5f, -130.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
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

		//Arboles para los columpios
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -2.0f, -130.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolS.RenderModel();
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CopaArbolS.RenderModel();
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EntradaArbolS.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f, -0.5f, -140.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoMadera.RenderModel();

		//Patas de banca
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoPatas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -0.5f, -140.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoMadera.RenderModel();

		//Patas de banca
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BancoPatas.RenderModel();

		//---------------- Cabeza olmeca ----------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.8f, -135.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CabezaOlmeca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-95.0f, -1.8f, -115.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolS.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CopaArbolS.RenderModel();

		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EntradaArbolS.RenderModel();

		//----------------- Luces / Lamparas -----------------
		//Lampara 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -1.5f, -75.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampTexture.UseTexture();
		Lampara.RenderModel();

		//Lampara 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-165.0f, -1.5f, -30.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampTexture.UseTexture();
		Lampara.RenderModel();

		//Lampara 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, -1.5f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampTexture.UseTexture();
		Lampara.RenderModel();

		//Lampara 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-135.0f, -1.5f, -30.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampTexture.UseTexture();
		Lampara.RenderModel();

		//-------------------- Lampara Joshua -------------------------

		for (int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-90.0f + (i * 20), -2.0f, -95.0f));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			lampBJoshuaTexture.UseTexture();
			lampNJoshuaTexture.UseTexture();
			LamparaJoshua.RenderModel();
		}

		for (int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -2.0f, 40.0f + (i * 22)));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			lampBJoshuaTexture.UseTexture();
			lampNJoshuaTexture.UseTexture();
			LamparaJoshua.RenderModel();
		}

		for (int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(53.0f, -2.0f, -123.0f + (i * 22)));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			lampBJoshuaTexture.UseTexture();
			lampNJoshuaTexture.UseTexture();
			LamparaJoshua.RenderModel();
		}

		for (int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-65.0f + (i * 32), -2.0f, -165.0f));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			lampBJoshuaTexture.UseTexture();
			lampNJoshuaTexture.UseTexture();
			LamparaJoshua.RenderModel();
		}

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
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaTexture.UseTexture();
		Arco_M.RenderModel();

		//Puerta izquierda
		model = modelaux;
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 6.5, 0.8f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaIzq_M.RenderModel();

		//Puerta Derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f + mainWindow.getmuevex(), 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 6.5, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaDer_M.RenderModel();

		//Cartel
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -3.0f));//20.5f));
		model = glm::scale(model, glm::vec3(2.0f, 6.8f, 0.2f));
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
		meshList[4]->RenderMesh();


		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

//KEYFRAMES, INICIAR REINICIAR ANIMACION

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;

		}
	}
}
