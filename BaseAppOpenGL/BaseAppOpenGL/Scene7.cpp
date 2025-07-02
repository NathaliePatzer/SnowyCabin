#include "Scene7.h"

CScene7::CScene7()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impress�o de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();
	pTextures->CreateTextureMipMap(0, "../Scene1/grass.bmp");
	pTextures->CreateTextureMipMap(1, "../Scene1/earthTexture.bmp");
	pTextures->CreateTextureMipMap(2, "../Scene1/grafite.bmp");
	pTextures->CreateTextureTGA(3, "../Scene1/cerca.tga");
	pTextures->CreateTextureTGA(4, "../Scene1/tree2.tga");
	


	// Definindo as propriedades da fonte de luz
	LightAmbient[0] = 1.0f; LightAmbient[1] = 1.0f; LightAmbient[2] = 1.0f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f; LightDiffuse[1] = 1.0f; LightDiffuse[2] = 1.0f; LightDiffuse[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 1.0f; LightSpecular[2] = 1.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = 0.0f; LightPosition[1] = 25.0f; LightPosition[2] = 20.0f; LightPosition[3] = 1.0f;
	
	LightDirection[0] = 0.0f;
	LightDirection[1] = -1.0f;
	LightDirection[2] = 0.0f;
	LightDirection[3] = 1.0f;
	// Velocidade de transla��o da fonte de luz
	fLightSpeed = 0.5f;

	bPointLight = false;	// Define o tipo de luz (Ponto ou Spot)
	fCutOff = 45.0f;	// �ngulo de abertura do cone de luz

	iLightType = NO_LIGHT;	// Define o tipo de luz (Ponto ou Spot)

	LightPositionFlashlight[0] = pCamera->Position[0];
	LightPositionFlashlight[1] = pCamera->Position[1];
	LightPositionFlashlight[2] = pCamera->Position[2];
	LightPositionFlashlight[3] = pCamera->Position[3];

	LightDirectionFlashlight[0] = pCamera->Forward[0];
	LightDirectionFlashlight[1] = pCamera->Forward[1];
	LightDirectionFlashlight[2] = pCamera->Forward[2];
	LightDirectionFlashlight[3] = pCamera->Forward[3];


	// Cria esfera com coordenadas de textura
	this->sphere = gluNewQuadric();
	gluQuadricTexture(this->sphere, TRUE);

	

}


CScene7::~CScene7(void)
{
	gluDeleteQuadric(this->sphere);

	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
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




int CScene7::DrawGLScene(void)	// Fun��o que desenha a cena
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posi��es da c�mera
	pCamera->setView();



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

	// Desenha a fonte de luz
	glPushMatrix();
	glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();


	switch (iLightType)
	{
		case NO_LIGHT:
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);	// Desabilita a luz 0
			glDisable(GL_LIGHT1);	// Desabilita a luz 1
		}
		break;

		case POINT_LIGHT:
		{
			glDisable(GL_LIGHT1); // Desabilita a luz 1 (caso esteja ligada)
			glEnable(GL_LIGHTING);	
			glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
			glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
			glEnable(GL_LIGHT0); // Habilita a luz 0		 	
		}
		break;

		case SPOT_LIGHT:
		{
			glDisable(GL_LIGHT0); // Desabilita a luz 0 (caso esteja ligada)
			glEnable(GL_LIGHTING);	
			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
			glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirection);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, fCutOff);	// �ngulo de abertura do cone de luz
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);	// Atenua��o constante
			glEnable(GL_LIGHT1);	// Habilita a luz 1
		}
		break;

		case FLASHLIGHT:
		{
			LightPositionFlashlight[0] = pCamera->Position[0];
			LightPositionFlashlight[1] = pCamera->Position[1];
			LightPositionFlashlight[2] = pCamera->Position[2];
			LightPositionFlashlight[3] = pCamera->Position[3];

			LightDirectionFlashlight[0] = pCamera->Forward[0];
			LightDirectionFlashlight[1] = pCamera->Forward[1];
			LightDirectionFlashlight[2] = pCamera->Forward[2];
			LightDirectionFlashlight[3] = pCamera->Forward[3];

			glDisable(GL_LIGHT0); // Desabilita a luz 0 (caso esteja ligada)
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
			glLightfv(GL_LIGHT1, GL_POSITION, LightPositionFlashlight);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightDirectionFlashlight);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);	// �ngulo de abertura do cone de luz
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);	// Atenua��o constante
			glEnable(GL_LIGHT1);	// Habilita a luz 1
		}
			break;	
	}



	
	// Configura��o do material do Teapot (reflex�o)
	MatAmbient[0] = 0.1f;	MatAmbient[1] = 0.0f;	MatAmbient[2] = 0.0f;	MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f;	MatDiffuse[1] = 0.0f;	MatDiffuse[2] = 0.0f;	MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 1.0f;	MatSpecular[1] = 1.0f;	MatSpecular[2] = 1.0f;	MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, MatShininess);

	// Desenha uma x�cara de ch�
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 0.0f);
	glutSolidTeapot(2.0f);
	glPopMatrix();



	// Desenha uma pir�mide
	glPushMatrix();
	glTranslatef(10.0f, 0.0f, 0.0f);
	DrawTriangle();
	glPopMatrix();

	
	

	// Configura material de reflex�o do ch�o
	MatAmbient[0] = 0.0f;	MatAmbient[1] = 0.0f;	MatAmbient[2] = 0.0f;	MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 1.0f;	MatDiffuse[1] = 1.0f;	MatDiffuse[2] = 1.0f;	MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 0.0f;	MatSpecular[1] = 0.0f;	MatSpecular[2] = 0.0f;	MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, MatShininess);

	glEnable(GL_TEXTURE_2D);	// Habilita o uso de texturas
	pTextures->ApplyTexture(0);	// Aplica a textura 0 (grass.bmp)
	Draw3DSGrid(50.0f, 50.0f); // Desenha grid 


	// Desenha uma esfera
	glPushMatrix();
	glTranslatef(0.0f, 5.0f, -20.0f);
	glRotatef(fRenderPosY, 0.0f, 1.0f, 0.0f);	// Rotaciona a esfera
	pTextures->ApplyTexture(1);
	gluSphere(this->sphere, 5.0f, 50, 50);	// Desenha esfera
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);	// Desabilita o uso de texturas
	
	
	glDisable(GL_LIGHT0);	// Desabilita a luz 0
	glDisable(GL_LIGHT1);	// Desabilita a luz 1
	glDisable(GL_LIGHTING);
	


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Habilita o modo de mistura de cores (transpar�ncia)
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);	// Define a cor da caixa (branca com transpar�ncia)
	// Desenha uma caixa
	glPushMatrix();
	DrawCube(-10.0f, 2.0f, 0.0f,
		0.0f, 1.0f, 0.0f, fRenderPosY,
		3.0f, 3.0f, 3.0f,
		2);
	glPopMatrix();

	// Desenha uma �rvore
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);	// Define o teste de alfa para valores maiores que 0.5
	
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	// Define a cor da �rvore (branca)
	
	pTextures->ApplyTexture(3);	// Aplica a textura da cerca
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 20.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f,  0.0f, -50.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f( 50.0f,  0.0f, -50.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f( 50.0f, 30.0f, -50.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 30.0f, -50.0f);
	glEnd();	
	glPopMatrix();

	pTextures->ApplyTexture(4);	// Aplica a textura da �rvore
	glPushMatrix();
	glTranslatef(-25.0f, 0.0f, 20.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, 0.0f, -20.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(20.0f, 0.0f, -20.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(20.0f, 30.0f, -20.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0f, 30.0f, -20.0f);
	glEnd();
	glPopMatrix();


	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

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
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));


	glPopMatrix();

	// Muda para modo de proje��o perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene7::MouseMove(void) // Tratamento de movimento do mouse
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

void CScene7::KeyPressed(void) // Tratamento de teclas pressionadas
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


	if (GetKeyState(VK_UP) & 0x80)
	{
		LightPosition[2] -= fLightSpeed;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		LightPosition[2] += fLightSpeed;
	}
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		LightPosition[0] -= fLightSpeed;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		LightPosition[0] += fLightSpeed;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		LightPosition[1] += fLightSpeed;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		LightPosition[1] -= fLightSpeed;
	}

	if (GetKeyState(VK_ADD) & 0x80)
	{
		fCutOff += 0.5f;
	}
	if (GetKeyState(VK_SUBTRACT) & 0x80)
	{
		fCutOff -= 0.5f;
	}


}

void CScene7::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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
	{
		iLightType++;
		if (iLightType > FLASHLIGHT)
			iLightType = NO_LIGHT;
	}
	break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene7::Draw3DSGrid(float width, float length)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glColor3f(0.0f, 0.3f, 0.0f);
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



void CScene7::DrawAxis()
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


void CScene7::DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glm::vec3 n = CalculateTriangleNormalVector(
		glm::vec3(-1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 2.0f, 0.0f));
	glNormal3f(n.x, n.y, n.z);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);


	n = CalculateTriangleNormalVector(
		glm::vec3(1.0f, 0.0f, -1.0f),
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 2.0f, 0.0f));
	glNormal3f(n.x, n.y, n.z);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	n = CalculateTriangleNormalVector(
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 2.0f, 0.0f));
	glNormal3f(n.x, n.y, n.z);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	n = CalculateTriangleNormalVector(
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(-1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 2.0f, 0.0f));
	glNormal3f(n.x, n.y, n.z);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();
}


void CScene7::DrawCube(float pX, float pY, float pZ,
	float rX, float rY, float rZ, float angle,
	float sX, float sY, float sZ,
	int texID)
{

	// Seta a textura ativa
	if (texID >= 0)
		pTextures->ApplyTexture(texID);

	glPushMatrix();
	glTranslatef(pX, pY, pZ);
	glRotatef(angle, rX, rY, rZ);
	glScalef(sX, sY, sZ);

	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// face tr�s
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();

	glPopMatrix();
}


// Calcula o vetor normal de um tri�ngulo
glm::vec3 CScene7::CalculateTriangleNormalVector(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	/*
			   v3
			   /\
			  /  \
			 /    \
			/      \
			+------+
		   v1      v2
	*/

	glm::vec3 A, B;
	A.x = v2.x - v1.x;
	A.y = v2.y - v1.y;
	A.z = v2.z - v1.z;

	B.x = v3.x - v1.x;
	B.y = v3.y - v1.y;
	B.z = v3.z - v1.z;

	// Calcula o Cross Product
	glm::vec3 normal;
	normal.x = A.y * B.z - A.z * B.y;
	normal.y = A.z * B.x - A.x * B.z;
	normal.z = A.x * B.y - A.y * B.x;

	// Calcula a magnitude do vetor normal
	double magnitude = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	// Normaliza o vetor normal
	glm::vec3 normalizedVector;
	normalizedVector.x = (normal.x / magnitude);
	normalizedVector.y = (normal.y / magnitude);
	normalizedVector.z = (normal.z / magnitude);

	return normalizedVector;
}