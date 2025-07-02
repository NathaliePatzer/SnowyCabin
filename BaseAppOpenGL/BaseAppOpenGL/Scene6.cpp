#include "Scene6.h"

CScene6::CScene6()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	pTerreno = NULL;
	pParticleSystem = NULL;
	pCena1 = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impress�o de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 5.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();	
	pTextures->CreateTextureMipMap(0, "../Scene1/grass.bmp");
	pTextures->CreateTextureMipMap(1, "../Scene1/decal2.bmp");
	pTextures->CreateTextureMipMap(2, "../Scene1/water.bmp");
	pTextures->CreateTextureMipMap(3, "../Scene5/T.jpg");


	//// Cria um terreno
	//pTerreno = new CTerreno();
	//pTerreno->LoadRawFile("../Scene5/T.raw");

	//pParticleSystem = new CParticleSystem();
	//pParticleSystem->Init(1000, 10);

	// Cria a cena 
	pCena1 = new CModel_3DS();
	pCena1->Load("../Scene5/Cena1.3ds");

}


CScene6::~CScene6(void)
{

	if (pCena1)
	{
		delete pCena1;
		pCena1 = NULL;
	}

	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTerreno)
	{
		delete pTerreno;
		pTerreno = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	
}




int CScene6::DrawGLScene(void)	// Fun��o que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	if (pCamera->Position[1] > 0.0f)
		glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	else
		glClearColor(0.07f, 0.55f, 0.9f, 0.5f);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posi��es da c�mera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espa�o)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (IN�CIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//// Faz o update nas part�culas
	//pParticleSystem->Update(1);
	//// Desenha as part�culas
	//pParticleSystem->Render();


	glEnable(GL_FOG);	// Habilita o efeito de neblina


	if (pCamera->Position[1] > 0.0f)
	{
		fFogColor[0] = 0.5f; fFogColor[1] = 0.5f; fFogColor[2] = 0.5f; fFogColor[3] = 1.0f;
		glFogfv(GL_FOG_COLOR, fFogColor);	// Cor da neblina
		glFogf(GL_FOG_DENSITY, 0.005f);	// Densidade da neblina
		glFogf(GL_FOG_START, 0.1f);	// Dist�ncia inicial da neblina
		glFogf(GL_FOG_END, 500.0f);	// Dist�ncia final da neblina
		glFogi(GL_FOG_MODE, GL_EXP);	// Modo de neblina
	}
	else
	{
		fFogColor[0] = 0.07f; fFogColor[1] = 0.55f; fFogColor[2] = 0.9f; fFogColor[3] = 1.0f;
		glFogfv(GL_FOG_COLOR, fFogColor);	// Cor da neblina
		glFogf(GL_FOG_START, 0.1f);	// Dist�ncia inicial da neblina
		glFogf(GL_FOG_END, 200.0f);	// Dist�ncia final da neblina
		glFogi(GL_FOG_MODE, GL_LINEAR);	// Modo de neblina
	}


	




	glActiveTexture(GL_TEXTURE0);	// Ativa a textura 0
	glEnable(GL_TEXTURE_2D);	// Habilita o uso de texturas
	pTextures->ApplyTexture(2);	// Seta o mapa de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);	// Modo de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE); // Substiti a cor do pol�gono pela textura base

	glActiveTexture(GL_TEXTURE1);	// Ativa a textura 1
	glEnable(GL_TEXTURE_2D);	// Habilita o uso de texturas
	pTextures->ApplyTexture(2);	// Seta o mapa de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);	// Modo de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE); // Multiplica a cor dessa camada de textura com a camada inferior

	// Desenha o Rio
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	glMultiTexCoord2f(GL_TEXTURE0, 0.0f + fTimerPosY / 2, 0.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fTimerPosY, 0.0f);
	glVertex3f(-500.0f, 0.0f,  250.0f);
	
	glMultiTexCoord2f(GL_TEXTURE0, 1.0f + fTimerPosY / 2, 0.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0f + fTimerPosY, 0.0f);
	glVertex3f( 500.0f, 0.0f,  250.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 1.0f + fTimerPosY / 2, 1.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0f + fTimerPosY, 1.0f);
	glVertex3f( 500.0f, 0.0f, -250.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 0.0f + fTimerPosY / 2, 1.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fTimerPosY, 1.0f);
	glVertex3f(-500.0f, 0.0f, -250.0f);
	glEnd();
	glPopMatrix();

	glActiveTexture(GL_TEXTURE1);	// Desativa a textura 0
	glDisable(GL_TEXTURE_2D);	// Desabilita o uso de texturas
	glActiveTexture(GL_TEXTURE0);	// Desativa a textura 0
	glDisable(GL_TEXTURE_2D);	// Desabilita o uso de texturas


	//// Desenha o terreno
	//glEnable(GL_TEXTURE_2D);
	//glPushMatrix();
	//glTranslatef(-500.0f, -150.0f, -500.0f);
	//pTextures->ApplyTexture(3);
	//pTerreno->RenderHeightMapVA();
	//glPopMatrix();	
	//glDisable(GL_TEXTURE_2D);


	// Desenha o terreno
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f, -100.0f, 0.0f);
	pCena1->Draw();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);



	glDisable(GL_FOG); // Desabilita o efeito de neblina


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = (pTimer->GetTime() / 1000.0f) / 10;
	fRenderPosY += 0.005f;

	// Impress�o de texto na tela...
	// Muda para modo de proje��o ortogonal 2D
	// OBS: Desabilite Texturas e Ilumina��o antes de entrar nesse modo de proje��o
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posi��o do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplica��o e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de proje��o perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene6::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os c�lculos de rota��o da vis�o do Player (atrav�s das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a c�mera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene6::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Sen�o, interrompe movimento do Player
	else
	{
	}



}

void CScene6::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene6::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene6::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


