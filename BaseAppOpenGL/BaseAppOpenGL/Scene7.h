#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include <glm/glm.hpp>


class CScene7 : public CSceneBaseClass
{
public:
	CScene7();
	~CScene7(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Fun��o que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();
	void DrawTriangle();
	

	void DrawCube(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f,
		float rX = 0.0f, float rY = 0.0f, float rZ = 0.0f, float angle = 0.0f,
		float sX = 1.0f, float sY = 1.0f, float sZ = 1.0f,
		int texID = -1);

	glm::vec3 CalculateTriangleNormalVector(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

	
private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia c�mera OpenGL
	float fDeltaY;				// Rota��o da c�mera OpenGL no eixo Y
	float fDeltaX;				// Rota��o da c�mera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;


	// Definindo as propriedades da fonte de luz
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightSpecular[4];
	GLfloat LightPosition[4];

	GLfloat LightDirection[4];

	GLfloat LightPositionFlashlight[4];
	GLfloat LightDirectionFlashlight[4];


	// Definindo as propriedades do material
	GLfloat MatAmbient[4];
	GLfloat MatDiffuse[4];
	GLfloat MatSpecular[4];
	GLfloat MatShininess;

	float fLightSpeed;

	bool bPointLight;
	float fCutOff;

	enum 
	{
		NO_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,
		FLASHLIGHT
	} eLightType;

	int iLightType;	// Tipo de luz (0 = sem luz, 1 = luz pontual, 2 = luz spot, 3 = lanterna)



	GLUquadric* sphere;



};

