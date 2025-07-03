#include "Scene8.h"

CScene8::CScene8()
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

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 1.5f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	angleX = 0.0f;
	angleY = 0.0f;

	flickerIntensity = 0.0f;


	// Carrega todas as texturas
	pTextures = new CTexture();
	pTextures->CreateTextureClamp(0, "../Scene1/negz.jpg"); // BACK map 
	pTextures->CreateTextureClamp(1, "../Scene1/posz.jpg"); // FRONT map
	pTextures->CreateTextureClamp(2, "../Scene1/negy.jpg"); // DOWN map
	pTextures->CreateTextureClamp(3, "../Scene1/posy.jpg"); // UP map
	pTextures->CreateTextureClamp(4, "../Scene1/posx.jpg"); // LEFT map
	pTextures->CreateTextureClamp(5, "../Scene1/negx.jpg"); // RIGHT map 

	pTextures->CreateTextureMipMap(6, "../Scene1/water.bmp");


	pModelAssimp = NULL;
	pModelAssimp = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/cabana/cabin.obj");

	pModelAssimpchao = NULL;
	pModelAssimpchao = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/montanhaBigLake.3ds");

	pModelAssimpPinheiro = NULL;
	pModelAssimpPinheiro = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/pine.3ds");

	pModelAssimpDeadTree = NULL;
	pModelAssimpDeadTree = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/deadTree.3ds");

	pModelAssimpFence = NULL;
	pModelAssimpFence = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/allFences/allFences.obj");

	pModelAssimpSnowPine = NULL;
	pModelAssimpSnowPine = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/snowPine/snowPine.obj");

	pModelAssimpBigSnowPine = NULL;
	pModelAssimpBigSnowPine = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/snowPineBig/snowPineBig.obj");

	pModelAssimpTree = NULL;
	pModelAssimpTree = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/snowTree/snowTree.obj");

	pModelAssimpBranche = NULL;
	pModelAssimpBranche = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/snowTree/branche.obj");

	pModelAssimpLamp = NULL;
	pModelAssimpLamp = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/objects/lamp.obj");

	pModelAssimpFlower = NULL;
	pModelAssimpFlower = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/flowers/garden.obj");

	pModelAssimpFlowerDaisy = NULL;
	pModelAssimpFlowerDaisy = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/flowers/white.obj");

	pModelAssimpRiverSide = NULL;
	pModelAssimpRiverSide = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/flowers/riverSide.obj");

	pModelAssimpRiverSideBig = NULL;
	pModelAssimpRiverSideBig = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/flowers/riverSideBig.obj");

	pModelAssimpRiverBranche = NULL;
	pModelAssimpRiverBranche = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/flowers/riverBranche.obj");

	pModelAssimpCampfire = NULL;
	pModelAssimpCampfire = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/objects/campfire.obj");

	pModelAssimpSnowMan = NULL;
	pModelAssimpSnowMan = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/snowman/snowman.obj");

	pModelAssimpRocks = NULL;
	pModelAssimpRocks = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/objects/rocks.obj");

	pModelAssimpLogs = NULL;
	pModelAssimpLogs = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/objects/logs.obj");

	pModelAssimpLogsFire = NULL;
	pModelAssimpLogsFire = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/objects/logsFire.obj");

	pModelAssimpRocksRiver = NULL;
	pModelAssimpRocksRiver = new CModel_ASSIMP(CModel_ASSIMP::DISPLAYLIST, "../Scene9/objects/rocksRiver.obj");

	pParticleSystemSnow = NULL;
	pParticleSystemSnow = new CParticleSystem(pCamera);
	pParticleSystemSnow->Init(CParticleSystem::SNOW, 1000, "../Scene9/snowflake.tga");

	// Luz da lareira (Spotlight - GL_LIGHT0)
	LightAmbient[0] = 0.15f; LightAmbient[1] = 0.05f; LightAmbient[2] = 0.0f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f;  LightDiffuse[1] = 0.3f; LightDiffuse[2] = 0.0f; LightDiffuse[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 0.25f; LightSpecular[2] = 0.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = -80.0f; LightPosition[1] = 200.0f; LightPosition[2] = 45.0f; LightPosition[3] = 1.0f;
	LightDirection[0] = 0.0f; LightDirection[1] = -1.0f; LightDirection[2] = 0.0f;

	// Luz amarelada suave (Point Light - GL_LIGHT1)
	Light2Diffuse[0] = 0.65f; Light2Diffuse[1] = 0.6f; Light2Diffuse[2] = 0.42f; Light2Diffuse[3] = 1.0f;
	Light2Specular[0] = 0.5f; Light2Specular[1] = 0.45f; Light2Specular[2] = 0.3f; Light2Specular[3] = 1.0f;
	Light2Position[0] = 300.0f; Light2Position[1] = 400.0f; Light2Position[2] = 400.0f; Light2Position[3] = 1.0f;

	// Luz frontal suave da cabana (Spotlight - GL_LIGHT2)
	Light3Ambient[0] = 0.2f;  Light3Ambient[1] = 0.13f; Light3Ambient[2] = 0.05f; Light3Ambient[3] = 1.0f;
	Light3Diffuse[0] = 1.5f;  Light3Diffuse[1] = 1.1f;  Light3Diffuse[2] = 0.42f; Light3Diffuse[3] = 1.0f;
	Light3Specular[0] = 1.1f; Light3Specular[1] = 0.8f; Light3Specular[2] = 0.32f; Light3Specular[3] = 1.0f;
	Light3Position[0] = -80.0f; Light3Position[1] = 50.0f; Light3Position[2] = 50.0f; Light3Position[3] = 1.0f;
	Light3Direction[0] = 0.5f; Light3Direction[1] = -0.4f; Light3Direction[2] = -0.2f;

	// Luz alaranjada suave 2 (Point Light - GL_LIGHT3)
	Light4Diffuse[0] = 0.42f; Light4Diffuse[1] = 0.28f; Light4Diffuse[2] = 0.12f; Light4Diffuse[3] = 1.0f;
	Light4Specular[0] = 0.25f; Light4Specular[1] = 0.18f; Light4Specular[2] = 0.08f; Light4Specular[3] = 1.0f;
	Light4Position[0] = 300.0f; Light4Position[1] = 500.0f; Light4Position[2] = -500.0f; Light4Position[3] = 1.0f;

	// Luz do poste (Spotlight - GL_LIGHT4)
	Light5Ambient[0] = 0.08f; Light5Ambient[1] = 0.05f; Light5Ambient[2] = 0.02f; Light5Ambient[3] = 1.0f;
	Light5Diffuse[0] = 0.85f; Light5Diffuse[1] = 0.45f; Light5Diffuse[2] = 0.15f; Light5Diffuse[3] = 1.0f;
	Light5Specular[0] = 0.5f;  Light5Specular[1] = 0.3f;  Light5Specular[2] = 0.1f;  Light5Specular[3] = 1.0f;
	Light5Position[0] = -265.0f; Light5Position[1] = 150.0f; Light5Position[2] = 240.0f; Light5Position[3] = 1.0f;
	Light5Direction[0] = 0.0f; Light5Direction[1] = -1.0f; Light5Direction[2] = 0.0f;

	// Luz da lâmpada acesa (Spotlight - GL_LIGHT5) - alaranjada
	Light6Ambient[0] = 0.25f; Light6Ambient[1] = 0.12f; Light6Ambient[2] = 0.05f; Light6Ambient[3] = 1.0f;
	Light6Diffuse[0] = 1.0f;  Light6Diffuse[1] = 0.5f;  Light6Diffuse[2] = 0.2f;  Light6Diffuse[3] = 1.0f;
	Light6Specular[0] = 1.0f;  Light6Specular[1] = 0.6f;  Light6Specular[2] = 0.3f;  Light6Specular[3] = 1.0f;
	Light6Position[0] = -285.0f; Light6Position[1] = 80.0f; Light6Position[2] = 200.0f; Light6Position[3] = 1.0f;
	Light6Direction[0] = 0.5f;  Light6Direction[1] = 0.0f;  Light6Direction[2] = 1.0f;

	// Luz da plaquinha (Spotlight - GL_LIGHT7)
	Light8Ambient[0] = 0.25f; Light8Ambient[1] = 0.12f; Light8Ambient[2] = 0.05f; Light8Ambient[3] = 1.0f;
	Light8Diffuse[0] = 1.0f;  Light8Diffuse[1] = 0.5f;  Light8Diffuse[2] = 0.2f;  Light8Diffuse[3] = 1.0f;
	Light8Specular[0] = 1.0f;  Light8Specular[1] = 0.6f;  Light8Specular[2] = 0.3f;  Light8Specular[3] = 1.0f;
	Light8Position[0] = -170.0f; Light8Position[1] = 30.0f; Light8Position[2] = 70.0f; Light8Position[3] = 1.0f;
	Light8Direction[0] = 0.8f;  Light8Direction[1] = -0.4f;  Light8Direction[2] = 1.0f;


	// Velocidade de translação da fonte de luz
	fLightSpeed = 0.5f;
}


CScene8::~CScene8(void)
{
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

	if (pModelAssimp)
	{
		delete pModelAssimp;
		pModelAssimp = NULL;
	}

	if (pModelAssimpchao)
	{
		delete pModelAssimpchao;
		pModelAssimpchao = NULL;
	}

	if (pModelAssimpPinheiro)
	{
		delete pModelAssimpPinheiro;
		pModelAssimpPinheiro = NULL;
	}

	if (pModelAssimpDeadTree)
	{
		delete pModelAssimpDeadTree;
		pModelAssimpDeadTree = NULL;
	}

	if (pModelAssimpFence)
	{
		delete pModelAssimpFence;
		pModelAssimpFence = NULL;
	}

	if (pModelAssimpSnowPine)
	{
		delete pModelAssimpSnowPine;
		pModelAssimpSnowPine = NULL;
	}

	if (pModelAssimpBigSnowPine)
	{
		delete pModelAssimpBigSnowPine;
		pModelAssimpBigSnowPine = NULL;
	}

	if (pModelAssimpTree)
	{
		delete pModelAssimpTree;
		pModelAssimpTree = NULL;
	}

	if (pModelAssimpBranche)
	{
		delete pModelAssimpBranche;
		pModelAssimpBranche = NULL;
	}

	if (pModelAssimpLamp)
	{
		delete pModelAssimpLamp;
		pModelAssimpLamp = NULL;
	}

	if (pModelAssimpFlower)
	{
		delete pModelAssimpFlower;
		pModelAssimpFlower = NULL;
	}

	if (pModelAssimpFlowerDaisy)
	{
		delete pModelAssimpFlowerDaisy;
		pModelAssimpFlowerDaisy = NULL;
	}

	if (pModelAssimpRiverSide)
	{
		delete pModelAssimpRiverSide;
		pModelAssimpRiverSide = NULL;
	}

	if (pModelAssimpRiverSideBig)
	{
		delete pModelAssimpRiverSideBig;
		pModelAssimpRiverSideBig = NULL;
	}

	if (pModelAssimpRiverBranche)
	{
		delete pModelAssimpRiverBranche;
		pModelAssimpRiverBranche = NULL;
	}

	if (pModelAssimpCampfire)
	{
		delete pModelAssimpCampfire;
		pModelAssimpCampfire = NULL;
	}

	if (pModelAssimpSnowMan)
	{
		delete pModelAssimpSnowMan;
		pModelAssimpSnowMan = NULL;
	}

	if (pModelAssimpRocks)
	{
		delete pModelAssimpRocks;
		pModelAssimpRocks = NULL;
	}

	if (pModelAssimpLogs)
	{
		delete pModelAssimpLogs;
		pModelAssimpLogs = NULL;
	}

	if (pModelAssimpLogsFire)
	{
		delete pModelAssimpLogsFire;
		pModelAssimpLogsFire = NULL;
	}

	if (pModelAssimpRocksRiver)
	{
		delete pModelAssimpRocksRiver;
		pModelAssimpRocksRiver = NULL;
	}

	if (pParticleSystemSnow)
	{
		delete pParticleSystemSnow;
		pParticleSystemSnow = NULL;
	}
}


int CScene8::DrawGLScene(void)	// Função que desenha a cena
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


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	//DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_FOG); //Habilita o efeito de neblina

	if (pCamera->Position[1] > 0.0f) {
		fFogColor[0] = 0.5f;
		fFogColor[1] = 0.5f;
		fFogColor[2] = 0.5f;
		fFogColor[3] = 1.0f;

		glFogfv(GL_FOG_COLOR, fFogColor); //Cor da neblina
		glFogf(GL_FOG_DENSITY, 0.005f); //Densidade da neblina
		glFogf(GL_FOG_START, 0.01f); //Distância inicial da neblina
		glFogf(GL_FOG_END, 500.0f); //Distância final da neblina (quer dizer que depois de 500.0f não será possível ver mais nada)
		glFogi(GL_FOG_MODE, GL_EXP); //Modo da neblina
	}
	else {
		fFogColor[0] = 0.07f;
		fFogColor[1] = 0.55f;
		fFogColor[2] = 0.9f;
		fFogColor[3] = 1.0f;

		glFogfv(GL_FOG_COLOR, fFogColor); //Cor da neblina
		glFogf(GL_FOG_START, 0.01f); //Distância inicial da neblina
		glFogf(GL_FOG_END, 200.0f); //Distância final da neblina (quer dizer que depois de 500.0f não será possível ver mais nada)
		glFogi(GL_FOG_MODE, GL_LINEAR); //Modo da neblina
	}

	// Efeito de luz piscando da lareira
	float time = pTimer->GetTime() / 1000.0f; // Tempo em segundos
	float flicker = 0.9f + 0.3f * sin(time * 4.0f);

	GLfloat flickerDiffuse[] = {
		1.0f * flicker, 0.3f * flicker, 0.0f, 1.0f
	};
	GLfloat flickerSpecular[] = {
		1.0f * flicker, 0.25f * flicker, 0.0f, 1.0f
	};

	// Desenha a fonte de luz
	glPushMatrix();
	glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	glutSolidSphere(0.1f, 10, 10);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D); // Habilita o uso de texturas
	glPushAttrib(GL_TEXTURE_BIT); // Salva o estado atual das texturas

	// Luz da lareira (GL_LIGHT0 - Spotlight)
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, flickerDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, flickerSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
	glEnable(GL_LIGHT0);

	// Luz ambiental (GL_LIGHT1 - Point Light)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light2Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light2Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, Light2Position);
	glEnable(GL_LIGHT1);

	// Luz frontal suave da cabana (GL_LIGHT2 - Spotlight)
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light3Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light3Diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light3Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, Light3Position);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Light3Direction);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0f);    // Ângulo do cone de luz
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 8.0f);  // Concentração do foco
	glEnable(GL_LIGHT2);

	// Luz ambiental (GL_LIGHT3 - Point Light)
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light4Diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Light4Specular);
	glLightfv(GL_LIGHT3, GL_POSITION, Light4Position);
	glEnable(GL_LIGHT3);

	// Luz do poste (GL_LIGHT4 - Spotlight)
	glLightfv(GL_LIGHT4, GL_AMBIENT, Light5Ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light5Diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Light5Specular);
	glLightfv(GL_LIGHT4, GL_POSITION, Light5Position);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, Light5Direction);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 55.0f);    // Ângulo do cone de luz
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 20.0f);  // Concentração do foco
	glEnable(GL_LIGHT4);

	// Luz da lâmpada acesa (GL_LIGHT5 - Spotlight)
	glLightfv(GL_LIGHT5, GL_AMBIENT, Light6Ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Light6Diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Light6Specular);
	glLightfv(GL_LIGHT5, GL_POSITION, Light6Position);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, Light6Direction);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 30.0f);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0f);
	glEnable(GL_LIGHT5);

	// Luz da fogueira (Spotlight - GL_LIGHT6)

	float flickerIntensity = 0.95f + 0.3f * sin(time * 10.0f) + 0.1f * cos(time * 17.0f); // mais variação e intensidade

	// Luz da fogueira (Spotlight - GL_LIGHT6)
	Light7Ambient[0] = 0.12f * flickerIntensity; Light7Ambient[1] = 0.06f * flickerIntensity; Light7Ambient[2] = 0.02f * flickerIntensity; Light7Ambient[3] = 1.0f;
	Light7Diffuse[0] = 1.2f * flickerIntensity; Light7Diffuse[1] = 0.6f * flickerIntensity; Light7Diffuse[2] = 0.15f * flickerIntensity; Light7Diffuse[3] = 1.0f;
	Light7Specular[0] = 0.9f * flickerIntensity; Light7Specular[1] = 0.45f * flickerIntensity; Light7Specular[2] = 0.2f * flickerIntensity; Light7Specular[3] = 1.0f;
	Light7Position[0] = 395.0f; Light7Position[1] = 150.0f; Light7Position[2] = -380.0f; Light7Position[3] = 1.0f;
	Light7Direction[0] = 0.0f; Light7Direction[1] = -1.0f; Light7Direction[2] = 0.0f;

	glLightfv(GL_LIGHT6, GL_AMBIENT, Light7Ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, Light7Diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, Light7Specular);
	glLightfv(GL_LIGHT6, GL_POSITION, Light7Position);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, Light7Direction);

	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 60.0f);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 15.0f); // mais foco no brilho
	glEnable(GL_LIGHT6);

	// Luz da plaquinha (Spotlight - GL_LIGHT7)
	glLightfv(GL_LIGHT7, GL_AMBIENT, Light8Ambient);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, Light8Diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, Light8Specular);
	glLightfv(GL_LIGHT7, GL_POSITION, Light8Position);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, Light8Direction);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 50.0f);
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 20.0f);
	glEnable(GL_LIGHT7);

	// Desenha fonte da lareira
	//glPushMatrix();
	//glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	//glColor3f(1.0f, 0.6f, 0.2f);
	//glutSolidSphere(10.0f, 10, 10);
	//glPopMatrix();

	// Desenha fonte ambiental
	/*glPushMatrix();
	glTranslatef(Light2Position[0], Light2Position[1], Light2Position[2]);
	glColor3f(0.6f, 0.7f, 1.0f);
	glutSolidSphere(80.0f, 10, 10);
	glPopMatrix();*/

	// Desenha fonte ambiental 2
	/*glPushMatrix();
	glTranslatef(Light4Position[0], Light4Position[1], Light4Position[2]);
	glColor3f(0.6f, 0.7f, 1.0f);
	glutSolidSphere(80.0f, 10, 10);
	glPopMatrix();*/

	//Desenha fonte frontal suave da cabana
	//glPushMatrix();
	//glTranslatef(Light3Position[0], Light3Position[1], Light3Position[2]);
	//glColor3f(0.6f, 0.7f, 1.0f);
	//glutSolidSphere(10.0f, 10, 10);
	//glPopMatrix();

	//Desenha fonte luz da lampada acesa
	/*glPushMatrix();
	glTranslatef(Light6Position[0], Light6Position[1], Light6Position[2]);
	glColor3f(0.6f, 0.7f, 1.0f);
	glutSolidSphere(4.0f, 10, 10);
	glPopMatrix();*/

	//Desenha fonte luz da fogueira
	/*glPushMatrix();
	glTranslatef(Light7Position[0], Light7Position[1], Light7Position[2]);
	glColor3f(0.6f, 0.7f, 1.0f);
	glutSolidSphere(4.0f, 10, 10);
	glPopMatrix();*/


	// Desenha o SkyBox
	CreateSkyBox(0.0f, 100.0f, 0.0f,
		1000.0f, 1000.0f, 1000.0f,
		pTextures);

	// Desenha modelo assimp chão montanha nevada
	glPushMatrix();
	glTranslatef(-30.0f, 0.0f, 0.0f);
	pModelAssimpchao->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro
	glPushMatrix();
	glTranslatef(-120.0f, -5.0f, -25.0f);
	pModelAssimpSnowPine->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro 2
	glPushMatrix();
	glTranslatef(-35.0f, -4.5f, 100.0f);
	pModelAssimpSnowPine->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro grande
	glPushMatrix();
	glTranslatef(90.0f, -2.5f, -30.0f);
	pModelAssimpBigSnowPine->Draw();
	glPopMatrix();

	// Desenha arvore nevada direita
	glPushMatrix();
	glTranslatef(170.0f, -2.0f, 420.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a árvore
	pModelAssimpTree->Draw();
	glPopMatrix();

	// Desenha arvore nevada esquerda
	glPushMatrix();
	glTranslatef(428.0f, -2.0f, -271.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a árvore
	pModelAssimpTree->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro direito
	glPushMatrix();
	glTranslatef(285.0f, -5.0f, 429.0f);
	pModelAssimpSnowPine->Draw();
	glPopMatrix();

	// Desenha galho nevado direito
	glPushMatrix();
	glTranslatef(10.0f, -2.0f, 420.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o galho
	pModelAssimpBranche->Draw();
	glPopMatrix();

	// Desenha galho nevado direito
	glPushMatrix();
	glTranslatef(-83.0f, -2.0f, 471.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o galho
	pModelAssimpBranche->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro grande direito
	glPushMatrix();
	glTranslatef(-231.0f, -30.0f, 435.0f);
	pModelAssimpBigSnowPine->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro direito
	glPushMatrix();
	glTranslatef(-379.0f, -5.0f, 392.0f);
	pModelAssimpSnowPine->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro grande direito trás
	glPushMatrix();
	glTranslatef(430.0f, -30.0f, 294.0f);
	pModelAssimpBigSnowPine->Draw();
	glPopMatrix();

	// Desenha galho nevado trás lado pinheiro grande
	glPushMatrix();
	glTranslatef(437.0f, -2.0f, 21.0f);
	glRotatef(-30.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o galho
	pModelAssimpBranche->Draw();
	glPopMatrix();

	// Desenha galho nevado trás
	glPushMatrix();
	glTranslatef(442.0f, -2.0f, -148.0f);
	glRotatef(-180.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o galho
	pModelAssimpBranche->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro trás lado galho
	glPushMatrix();
	glTranslatef(420.0f, -5.0f, 124.0f);
	pModelAssimpSnowPine->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro esquerdo
	glPushMatrix();
	glTranslatef(-262.0f, -30.0f, -449.0f);
	pModelAssimpBigSnowPine->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro grande esquerdo
	glPushMatrix();
	glTranslatef(60.0f, -30.0f, -452.0f);
	pModelAssimpBigSnowPine->Draw();
	glPopMatrix();

	// Desenha galho nevado esquerdo
	glPushMatrix();
	glTranslatef(-73.0f, -2.0f, -430.0f);
	glRotatef(-180.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o galho
	pModelAssimpBranche->Draw();
	glPopMatrix();

	// Desenha modelo pinheiro trás lado galho
	glPushMatrix();
	glTranslatef(-459.0f, -5.0f, -457.0f);
	pModelAssimpSnowPine->Draw();
	glPopMatrix();

	//Desenha poste de luz
	glPushMatrix();
	glTranslatef(-265.0f, 1.0f, 240.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o poste de luz
	pModelAssimpLamp->Draw();
	glPopMatrix();

	// Desenha a cerca
	glPushMatrix();
	glTranslatef(-250.0f, 3.0f, 130.0f);
	glRotatef(20.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a cerca
	pModelAssimpFence->Draw();
	glPopMatrix();

	// Desenha a flor
	glPushMatrix();
	glTranslatef(-300.0f, 1.3f, 80.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a flor
	pModelAssimpFlower->Draw();
	glPopMatrix();

	// Desenha a flor
	glPushMatrix();
	glTranslatef(-426.0f, 1.3f, 52.0f);
	glRotatef(40.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a flor
	pModelAssimpFlower->Draw();
	glPopMatrix();

	// Desenha a flor
	glPushMatrix();
	glTranslatef(-359.0f, 1.3f, 103.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a flor
	pModelAssimpFlower->Draw();
	glPopMatrix();

	// Desenha a flor
	glPushMatrix();
	glTranslatef(-407.0f, 1.3f, 251.0f);
	glRotatef(320.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a flor
	pModelAssimpFlower->Draw();
	glPopMatrix();

	// Desenha a flor
	glPushMatrix();
	glTranslatef(-299.0f, 2.2f, 228.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a flor
	pModelAssimpFlower->Draw();
	glPopMatrix();

	// Desenha a flor
	glPushMatrix();
	glTranslatef(-356.0f, 1.3f, 298.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a flor
	pModelAssimpFlower->Draw();
	glPopMatrix();

	// Desenha jardim 
	for (int i = -250; i > -500; i -= 40) {
		for (int j = -20; j < 380; j += 50) {
			glPushMatrix();
			glTranslatef(i, 1.3f, j);
			pModelAssimpFlower->Draw();
			glPopMatrix();
		}
	}

	// Desenha margarida
	for (int i = -250; i > -500; i -= 45) {
		for (int j = -20; j < 380; j += 55) {
			glPushMatrix();
			glTranslatef(i, 1.0f, j);
			pModelAssimpFlowerDaisy->Draw();
			glPopMatrix();
		}
	}

	// Desenha a margem do rio
	for (int i = -500; i < 350; i += 30) {
		for (int j = -445; j > -500; j -= 20) {
			glPushMatrix();
			glTranslatef(i, 1.0f, j);
			pModelAssimpRiverSide->Draw();
			glPopMatrix();
		}
	}

	// Desenha a margem do rio grande início
	glPushMatrix();
	glTranslatef(-460.0f, -8.0f, -415.0f);
	glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
	pModelAssimpRiverSideBig->Draw();
	glPopMatrix();

	// Desenha a margem do rio grande início
	glPushMatrix();
	glTranslatef(-383.0f, -8.0f, -419.0f);
	glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
	pModelAssimpRiverSideBig->Draw();
	glPopMatrix();

	// Desenha a margem do rio grande meio
	glPushMatrix();
	glTranslatef(-147.0f, -18.0f, -434.0f);
	glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
	pModelAssimpRiverSideBig->Draw();
	glPopMatrix();


	// Desenha a margem do rio grande final
	glPushMatrix();
	glTranslatef(300.0f, -8.0f, -408.0f);
	glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
	pModelAssimpRiverSideBig->Draw();
	glPopMatrix();

	// Desenha a margem do rio grande final
	glPushMatrix();
	glTranslatef(270.0f, -8.0f, -358.0f);
	glRotatef(-125.0f, 0.0f, 1.0f, 0.0f);
	pModelAssimpRiverSideBig->Draw();
	glPopMatrix();

	// Desenha o galho do rio
	glPushMatrix();
	glTranslatef(88.0f, -12.0f, -415.0f);
	glRotatef(15.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o galho
	pModelAssimpRiverBranche->Draw();
	glPopMatrix();

	// Desenha a fogueira
	glPushMatrix();
	glTranslatef(395.0f, 3.5f, -380.0f);
	pModelAssimpCampfire->Draw();
	glPopMatrix();

	// Desenha os troncos em volta da fogueira 
	glPushMatrix();
	glTranslatef(440.0f, 3.5f, -380.0f);
	pModelAssimpLogsFire->Draw();
	glPopMatrix();

	// Desenha o boneco de neve
	glPushMatrix();
	glTranslatef(-260.0f, 3.8f, 220.0f);
	glRotatef(-20.0f, 0.0f, 1.0f, 0.0f); // Rotaciona o boneco de neve
	pModelAssimpSnowMan->Draw();
	glPopMatrix();

	// Desenha rochas
	glPushMatrix();
	glTranslatef(-130.0f, 4.0f, 135.0f);
	glRotatef(-80.0f, 0.0f, 1.0f, 0.0f); // Rotaciona as rochas
	pModelAssimpRocks->Draw();
	glPopMatrix();

	// Desenha troncos 
	glPushMatrix();
	glTranslatef(-430.0f, 4.0f, 420.0f);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f); // Rotaciona os troncos
	pModelAssimpLogs->Draw();
	glPopMatrix();

	// Desenha troncos trás
	glPushMatrix();
	glTranslatef(440.0f, 4.0f, -56.0f);
	pModelAssimpLogs->Draw();
	glPopMatrix();

	// Desenha troncos trás
	glPushMatrix();
	glTranslatef(450.0f, 3.5f, -207.0f);
	glRotatef(-82.0f, 0.0f, 1.0f, 0.0f); // Rotaciona os troncos
	pModelAssimpLogs->Draw();
	glPopMatrix();

	// Desenha rochas no rio
	glPushMatrix();
	glTranslatef(-470.0f, -25.0f, -300.0f);
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotaciona as rochas
	pModelAssimpRocksRiver->Draw();
	glPopMatrix();

	//Rio
	glActiveTexture(GL_TEXTURE0);	// Ativa a textura 0
	pTextures->ApplyTexture(6);	// Seta o mapa de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);	// Modo de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE); // Substiti a cor do polígono pela textura base

	glActiveTexture(GL_TEXTURE1);	// Ativa a textura 1
	glEnable(GL_TEXTURE_2D);	// Habilita o uso de texturas
	pTextures->ApplyTexture(6);	// Seta o mapa de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);	// Modo de textura
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE); // Multiplica a cor dessa camada de textura com a camada inferior

	// Desenha o Rio
	glPushMatrix();
	glTranslatef(-5.0f, -18.0f, -300.0f);

	glBegin(GL_QUADS);
	glMultiTexCoord2f(GL_TEXTURE0, 0.0f + fTimerPosY / 2, 0.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fTimerPosY, 0.0f);
	glVertex3f(-500.0f, 0.0f, 250.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 1.0f + fTimerPosY / 2, 0.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0f + fTimerPosY, 0.0f);
	glVertex3f(500.0f, 0.0f, 250.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 1.0f + fTimerPosY / 2, 1.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 1.0f + fTimerPosY, 1.0f);
	glVertex3f(500.0f, 0.0f, -250.0f);

	glMultiTexCoord2f(GL_TEXTURE0, 0.0f + fTimerPosY / 2, 1.0f);
	glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fTimerPosY, 1.0f);
	glVertex3f(-500.0f, 0.0f, -250.0f);
	glEnd();
	glPopMatrix();

	glActiveTexture(GL_TEXTURE1);	// Desativa a textura 0
	glActiveTexture(GL_TEXTURE0);	// Desativa a textura 0


	glPopAttrib(); // Restaura o estado das texturas
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D); // Habilita o uso de texturas

	// Desenha modelo assimp cabana (para não ser afetado pelas luzes)
	glPushMatrix();
	glTranslatef(-20.0f, 8.0f, 30.0f);
	glScalef(6.0f, 6.0f, 6.0f);
	glRotatef(-75.0f, 0.0f, 1.0f, 0.0f);
	pModelAssimp->Draw();
	glPopMatrix();

	// Desenha a cerca
	/*glPushMatrix();
	glTranslatef(-100.0f, 20.0f, 50.0f);
	glScalef(20.5f, 20.5f, 20.5f);
	pModelAssimpFence->Draw();
	glPopMatrix();*/

	glDisable(GL_TEXTURE_2D); // Desabilita o uso de texturas

	pParticleSystemSnow->UpdateSnow(0);	// Atualiza o sistema de partículas
	pParticleSystemSnow->RenderSnow();	// Renderiza o sistema de partículas

	// Chama da fogueira
	// Ativa o blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glTranslatef(395.0f, 4.0f, -380.0f);

	// Grupos animados de triângulos (rotacionando)
	float groupRotations[3] = { angleX, angleX + 25.0f, angleX - 15.0f };

	for (int i = 0; i < 3; ++i) {
		glPushMatrix();

		// Espalha os grupos em torno do eixo Y
		glRotatef(i * 60.0f, 0.0f, 1.0f, 0.0f);

		// Rotação individual do grupo (eixo Z)
		glRotatef(groupRotations[i], 0.0f, 0.0f, 1.0f);

		// Triângulo laranja animado
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 0.5f, 0.0f, 0.5f);
		glVertex3f(-13.5f, 0.0f, 0.0f);  // -9 * 1.5
		glVertex3f(13.5f, 0.0f, 0.0f);   // 9 * 1.5
		glVertex3f(0.0f, 36.0f, 0.0f);   // 24 * 1.5
		glEnd();

		// Triângulo amarelo animado
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 1.0f, 0.0f, 0.4f);
		glVertex3f(0.0f, 0.0f, -13.5f);
		glVertex3f(0.0f, 0.0f, 13.5f);
		glVertex3f(0.0f, 36.0f, 0.0f);
		glEnd();

		glPopMatrix();
	}

	float pulseY = 3.0f * sin(time * 2.5f); // movimento suave no eixo Y

	float selfRotation = fmod(time * 60.0f, 360.0f); // rotação contínua (60 graus por segundo)

	// Triângulos estáticos adicionais com leve movimentação vertical
	for (int i = 0; i < 3; ++i) {
		glPushMatrix();

		// Aplica rotação para espalhar os triângulos
		glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f);

		// Movimento vertical suave
		glTranslatef(0.0f, pulseY, 0.0f);

		// Rotação em torno do próprio eixo
		glRotatef(selfRotation + i * 30.0f, 0.0f, 1.0f, 0.0f); // cada um gira em fase diferente

		// Triângulo laranja fixo
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 0.3f, 0.0f, 0.3f);
		glVertex3f(-12.0f, 0.0f, 0.0f);
		glVertex3f(12.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 32.0f, 0.0f);
		glEnd();

		// Triângulo amarelo fixo
		glBegin(GL_TRIANGLES);
		glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
		glVertex3f(0.0f, 0.0f, -12.0f);
		glVertex3f(0.0f, 0.0f, 12.0f);
		glVertex3f(0.0f, 32.0f, 0.0f);
		glEnd();

		glPopMatrix();
	}

	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_FOG); // Desabilita o efeito de neblina


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 10000.0f;
	fRenderPosY += 0.2f;

	angleX += 1.5f; // velocidade de rotação no eixo X
	angleY += 1.0f; // velocidade de rotação no eixo Y

	// Mantém os valores dentro de 0 a 360 graus
	if (angleX > 360.0f) angleX -= 360.0f;
	if (angleY > 360.0f) angleY -= 360.0f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
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

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene8::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene8::KeyPressed(void) // Tratamento de teclas pressionadas
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
	// Senão, interrompe movimento do Player
	else
	{
	}

	if (GetKeyState(VK_UP) & 0x80)
	{
		Light6Position[2] -= fLightSpeed;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		Light6Position[2] += fLightSpeed;
	}
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		Light6Position[0] -= fLightSpeed;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		Light6Position[0] += fLightSpeed;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		Light6Position[1] += fLightSpeed;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		Light6Position[1] -= fLightSpeed;
	}


}

void CScene8::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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
void CScene8::Draw3DSGrid(float width, float length)
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



void CScene8::DrawAxis()
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


void CScene8::CreateSkyBox(float x, float y, float z,
	float width, float height, float length,
	CTexture* pTextures)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();

	// Centraliza o Skybox em torno da posição especificada(x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Aplica a textura que representa a parte da frente do skybox (BACK map)
	pTextures->ApplyTexture(0);

	// Desenha face BACK do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (FRONT map)
	pTextures->ApplyTexture(1);

	// Desenha face FRONT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (DOWN map)
	pTextures->ApplyTexture(2);

	// Desenha face BOTTOM do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (UP map)
	pTextures->ApplyTexture(3);

	// Desenha face TOP do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (LEFT map)
	pTextures->ApplyTexture(4);

	// Desenha face LEFT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (RIGHT map)
	pTextures->ApplyTexture(5);

	// Desenha face RIGHT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();
}

