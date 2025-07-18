#include "SceneManager.h"

// Construtor
CSceneManager::CSceneManager(int l, int a)
{
	// Redimensiona e inicial a janela OpenGL
	this->ReSizeGLScene(l, a);

	// Inicializa estados iniciais do OpenGL
	this->InitGL();

	// Inicializa estados iniciais da DEVIL
	this->InitIL();

	// Inicializa ponteiros das cenas	
	// Cria a cena principal
	this->Scene = NULL;
	uiCurrentScene = 9;
	ChangeScene(uiCurrentScene);
}


// Destrutor
CSceneManager::~CSceneManager(void)
{
	if (this->Scene)
	{
		delete this->Scene;
		this->Scene = NULL;
	}

	this->DeInitGL();

	this->DeInitIL();
}

// Renderiza a cena
int CSceneManager::DrawGLScene(void)
{
	Scene->DrawGLScene();

	return 1;
}


void CSceneManager::ChangeScene(unsigned int _uiCurrentScene)
{
	this->uiCurrentScene = _uiCurrentScene;

	if (this->Scene)
	{
		delete this->Scene;
		this->Scene = NULL;
		glPopAttrib();
	}	
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	switch (uiCurrentScene)
	{
	case 1:
		this->Scene = new CScene1();
		break;

	case 2:
		this->Scene = new CScene2();
		break;

	case 3:
		this->Scene = new CScene3();
		break;

	case 4:
		this->Scene = new CScene4();
		break;

	case 5:
		this->Scene = new CScene5();
		break;

	case 6:
		this->Scene = new CScene6();
		break;

	case 7:
		this->Scene = new CScene7();
		break;

	case 8:
		this->Scene = new CScene8();
		break;

	case 9:
		this->Scene = new CScene9();
		break;
	
	}	
}

// Configura��es iniciais OpenGL (pr�-render)
bool CSceneManager::InitGL(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing	

	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	//glCullFace(GL_CCW);
	//glEnable(GL_CULL_FACE);

	SetVSync(true);		// Habilita ou desabilita sincroniza��o vertical (VSYNC)

	// Ativar GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MessageBox(NULL, NULL, "GLEW ERROR", MB_OK | MB_ICONINFORMATION);
		exit(-1);
	}

	return true;
}

// Destr�i todos os gerenciadores alocados em InitGL() 
void CSceneManager::DeInitGL(void)
{

}

// Tratamento de movimento do mouse
void CSceneManager::MouseMove(void)
{
	Scene->MouseMove();
}

// Tratamento de teclas pressionadas
void CSceneManager::KeyPressed(void)
{
	Scene->KeyPressed();
}

// Tratamento de teclas pressionadas
void CSceneManager::KeyDownPressed(WPARAM wParam)
{
	Scene->KeyDownPressed(wParam);

	// Carrega nova cena...
	if (wParam == '1') ChangeScene(1);
	if (wParam == '2') ChangeScene(2);
	if (wParam == '3') ChangeScene(3);
	if (wParam == '4') ChangeScene(4);
	if (wParam == '5') ChangeScene(5);
	if (wParam == '6') ChangeScene(6);
	if (wParam == '7') ChangeScene(7);
	if (wParam == '8') ChangeScene(8);
	if (wParam == '9') ChangeScene(9);

	

}

// Redimensiona e inicial a janela OpenGL
void CSceneManager::ReSizeGLScene(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reinicializa a Current Viewport

	glMatrixMode(GL_PROJECTION);						// Seleciona a Projection Matrix
	glLoadIdentity();									// Reinicializa a Projection Matrix

	// Calcula o Aspect Ratio da janela
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);							// Seleciona a Modelview Matrix
	glLoadIdentity();									// Reinicializa a Modelview Matrix
}

void CSceneManager::InitIL(void)
{
	ilInit();					// Initialize IL
	iluInit();					// Initialize ILU
	ilutRenderer(ILUT_OPENGL);	// Initialize ILUT with OpenGL support.

	ILuint devilError;
	devilError = ilGetError();
	string ilStrError = iluErrorString(devilError);

	if (devilError != IL_NO_ERROR)
		MessageBox(NULL, ilStrError.c_str(), "DEVIL ERROR", MB_OK | MB_ICONINFORMATION);
}

void CSceneManager::DeInitIL()
{

}