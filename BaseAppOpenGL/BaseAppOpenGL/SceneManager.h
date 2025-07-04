#pragma once
#include "SceneBaseClass.h"		// Classe Base
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include "Scene8.h"
#include "Scene9.h"


class CSceneManager : public CSceneBaseClass
{
public:
	CSceneManager(int l, int a);
	virtual ~CSceneManager(void);

	virtual void MouseMove(void); // Tratamento de movimento do mouse
	virtual void KeyPressed(void); // Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);	// Fun��o que desenha a cena
	void ChangeScene(unsigned int _uiCurrentScene);

	void ReSizeGLScene(int width, int height); // Redimensiona e inicial a janela OpenGL

	void InitIL(void);
	void DeInitIL();

private:
	bool InitGL(void); // Configura��es iniciais OpenGL (pr�-render)
	void DeInitGL(void); // Destr�i todos os gerenciadores alocados em InitGL() 

	// Ponteiro para cenas do jogo
	CSceneBaseClass* Scene;

	// ID da cena
	unsigned int uiCurrentScene;
};

