#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "CTerreno.h"
#include "CParticles.h"
#include "CModel_3DS.h"


class CScene6 : public CSceneBaseClass
{
public:
	CScene6();
	~CScene6(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Fun��o que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	
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
	CTerreno* pTerreno;	// Objeto que gerencia o terreno
	CParticleSystem* pParticleSystem;	// Objeto que gerencia o sistema de part�culas

	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;

	CModel_3DS* pCena1;	// Objeto que gerencia o modelo 3DS
	float fFogColor[4];
};

