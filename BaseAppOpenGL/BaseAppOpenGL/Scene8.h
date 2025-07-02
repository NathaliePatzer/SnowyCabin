#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "CModel_3DS.h"
#include "CModel_ASSIMP.h"
#include "CParticles.h"


class CScene8 : public CSceneBaseClass
{
public:
	CScene8();
	~CScene8(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	void CreateSkyBox(float x, float y, float z,
		float width, float height, float length,
		CTexture* pTextures);

private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia câmera OpenGL
	float fDeltaY;				// Rotação da câmera OpenGL no eixo Y
	float fDeltaX;				// Rotação da câmera OpenGL no eixo X

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


	CModel_3DS* pCasa;
	CModel_3DS* pTerreno;
	CModel_3DS* pLago;
	CModel_3DS* pGrama;

	CModel_ASSIMP* pModelAssimp;	// Modelo 3D cabana
	CModel_ASSIMP* pModelAssimpchao; // Modelo 3D montanha
	CModel_ASSIMP* pModelAssimpPinheiro; // Modelo 3D pinheiro
	CModel_ASSIMP* pModelAssimpDeadTree; // Modelo 3D pinheiro seco
	CModel_ASSIMP* pModelAssimpDeadTree2; // Modelo 3D pinheiro seco 2
	CModel_ASSIMP* pModelAssimpFence; // Modelo 3D cerca
	CModel_ASSIMP* pModelAssimpSnowPine; // Modelo 3D pinheiro com neve
	CModel_ASSIMP* pModelAssimpBigSnowPine; // Modelo 3D pinheiro grande com neve
	CModel_ASSIMP* pModelAssimpTree; // Modelo 3D árvore
	CModel_ASSIMP* pModelAssimpBranche; // Modelo 3D galho
	CModel_ASSIMP* pModelAssimpLamp; // Modelo 3D lampada
	CModel_ASSIMP* pModelAssimpFlower; // Modelo 3D flor
	CModel_ASSIMP* pModelAssimpFlowerDaisy; // Modelo 3D flor margarida
	CModel_ASSIMP* pModelAssimpRiverSide; // Modelo 3D margem do rio
	CModel_ASSIMP* pModelAssimpRiverSideBig; // Modelo 3D margem do rio grande
	CModel_ASSIMP* pModelAssimpRiverBranche; // Modelo 3D galho do rio
	CModel_ASSIMP* pModelAssimpCampfire; // Modelo 3D fogueira
	CModel_ASSIMP* pModelAssimpSnowMan; // Modelo 3D boneco de neve
	CModel_ASSIMP* pModelAssimpRocks; // Modelo 3D rochas
	CModel_ASSIMP* pModelAssimpLogs; // Modelo 3D troncos
	CModel_ASSIMP* pModelAssimpLogsFire; // Modelo 3D troncos da fogueira
	CModel_ASSIMP* pModelAssimpRocksRiver; // Modelo 3D troncos da fogueira

	CParticleSystem* pParticleSystemSnow;

	// Definindo as propriedades da fonte de luz
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightSpecular[4];
	GLfloat LightPosition[4];
	GLfloat LightDirection[4];

	GLfloat Light2Diffuse[4];
	GLfloat Light2Specular[4];
	GLfloat Light2Position[4];

	GLfloat Light3Ambient[4];
	GLfloat Light3Diffuse[4];
	GLfloat Light3Specular[4];
	GLfloat Light3Position[4];
	GLfloat Light3Direction[4];

	GLfloat Light4Diffuse[4];
	GLfloat Light4Specular[4];
	GLfloat Light4Position[4];

	GLfloat Light5Diffuse[4];
	GLfloat Light5Specular[4];
	GLfloat Light5Position[4];
	GLfloat Light5Direction[4];
	GLfloat Light5Ambient[4];

	GLfloat Light6Diffuse[4];
	GLfloat Light6Specular[4];
	GLfloat Light6Position[4];
	GLfloat Light6Ambient[4];
	GLfloat Light6Direction[4];

	GLfloat Light7Ambient[4];
	GLfloat Light7Diffuse[4];
	GLfloat Light7Specular[4];
	GLfloat Light7Position[4];
	GLfloat Light7Direction[4];
	float flickerIntensity; // Intensidade do efeito de cintilação da luz da fogueira

	GLfloat Light8Ambient[4];
	GLfloat Light8Diffuse[4];
	GLfloat Light8Specular[4];
	GLfloat Light8Position[4];
	GLfloat Light8Direction[4];

	float fFogColor[4]; // Cor da neblina

	float fLightSpeed;
	float angleX;
	float angleY;

	LPSTR texturesCubeMap[6];
};

