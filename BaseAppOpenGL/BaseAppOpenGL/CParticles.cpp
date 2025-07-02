#include "CParticles.h"

CParticles::CParticles(float x, float y, float z, float speedX, float speedY, float speedZ,
	unsigned char r, unsigned char g, unsigned char b, unsigned char a,
	float size, float life, float angle, float angleDir)
{
	this->pos = glm::vec3(x, y, z);
	this->speed = glm::vec3(speedX, speedY, speedZ);
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->size = size;
	this->life = life;
	this->angle = angle;
	this->angleDir = angleDir;
}


CParticles::~CParticles()
{

}


CParticleSystem::CParticleSystem(CCamera* pCamera)
{
	iMaxParticles = 0;
	this->pCamera = pCamera;

}

CParticleSystem::~CParticleSystem()
{
	KillAllParticles();
}

void CParticleSystem::Init(ParticleType particleType, int maxParticles, char* texturePath)
{
	iMaxParticles = maxParticles;
	ParticlesContainer.reserve(iMaxParticles);

	// Initialize the texture
	texture.LoadTGA(texturePath);

	for (int i = 0; i < iMaxParticles; i++)
	{
		switch (particleType)
		{
		case SNOW:
			CreateRandomParticleSnow();
			break;

		case SMOKE:
		{
			fTime = 0;
		}
		break;

		}
	}
}


void CParticleSystem::KillAllParticles()
{
	for (int i = 0; i < ParticlesContainer.size(); i++)
	{
		delete ParticlesContainer[i];
	}
	ParticlesContainer.clear();
}

void CParticleSystem::KillParticle(int index)
{
	if (index >= 0 && index < ParticlesContainer.size())
	{
		delete ParticlesContainer[index];
		ParticlesContainer.erase(ParticlesContainer.begin() + index);
	}
}

void CParticleSystem::AddParticle(float x, float y, float z, float speedX, float speedY, float speedZ,
	unsigned char r, unsigned char g, unsigned char b, unsigned char a,
	float size, float life, float angle, float angleDir)
{
	if (ParticlesContainer.size() < iMaxParticles)
	{
		CParticles* newParticle = new CParticles(x, y, z, speedX, speedY, speedZ, r, g, b, a, size, life, angle, angleDir);
		ParticlesContainer.push_back(newParticle);
	}
}

int CParticleSystem::GetParticlesCount()
{
	return ParticlesContainer.size();
}

void CParticleSystem::CreateRandomParticleSnow()
{
	// Initialize particles with random values
	float x = static_cast<float>(rand() % 200) - 100.0f;
	float y = static_cast<float>(rand() % 100) + 100.0f;
	float z = static_cast<float>(rand() % 200) - 100.0f;
	float speedX = static_cast<float>(rand() % 100) / 100.0f;
	speedX *= (rand() % 2 == 0) ? -1.0f : 1.0f; // Randomize direction
	float speedY = static_cast<float>(-1.0f);
	float speedZ = static_cast<float>(rand() % 100) / 100.0f;
	speedZ *= (rand() % 2 == 0) ? -1.0f : 1.0f; // Randomize direction
	unsigned char r = static_cast<unsigned char>(rand() % 256);
	unsigned char g = static_cast<unsigned char>(rand() % 256);
	unsigned char b = static_cast<unsigned char>(rand() % 256);
	unsigned char a = static_cast<unsigned char>(rand() % 256);
	float size = static_cast<float>(rand() % 1) + 2;
	float life = static_cast<float>(rand() % 10) + 1;
	float angle = static_cast<float>(rand() % 360);
	float angleDir = static_cast<float>(rand() % 2 == 0) ? -1.0f : 1.0f;

	AddParticle(x, y, z, speedX, speedY, speedZ, r, g, b, a, size, life, angle, angleDir);
}



void CParticleSystem::UpdateSnow(float deltaTime)
{
	for (int i = 0; i < ParticlesContainer.size(); i++)
	{
		CParticles* particle = ParticlesContainer[i];
		particle->pos += particle->speed * 0.5f;
		particle->life -= 0.01f;
		if (particle->life <= 0.0f)
		{
			delete particle;
			ParticlesContainer.erase(ParticlesContainer.begin() + i);
			i--;
			CreateRandomParticleSnow();
		}
	}
}

void CParticleSystem::RenderSnow()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.95f);

	glPushMatrix();
	glTranslatef(pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);
	for (int i = 0; i < ParticlesContainer.size(); i++)
	{
		CParticles* particle = ParticlesContainer[i];

		glColor3ub(255, 255, 255);
		texture.Use();
		glPushMatrix();
		float matrixBillboard[16] =
		{
			pCamera->Right[0],		pCamera->Right[1],		pCamera->Right[2],		0.0f,
			pCamera->Up[0],			pCamera->Up[1],			pCamera->Up[2],			0.0f,
			pCamera->Forward[0],	pCamera->Forward[1],	pCamera->Forward[2],	0.0f,
			particle->pos.x,		particle->pos.y,		particle->pos.z,		1.0f
		};
		glMultMatrixf(matrixBillboard);

		glBegin(GL_QUADS);
		//glColor3ub(particle->r, particle->g, particle->b);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-particle->size, -particle->size, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(particle->size, -particle->size, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(particle->size, particle->size, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-particle->size, particle->size, 0.0f);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}



void CParticleSystem::CreateRandomParticleSmoke(int sizeMIN, int sizeMAX)
{
	//// Initialize a random number generator
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<> distrib(sizeMIN, sizeMAX);
	//int randomValue = distrib(gen);

	// Initialize particles with random values
	float x = 0.0f;;
	float y = 0.0f;
	float z = 0.0f;;
	float speedX = static_cast<float>(rand() % 100) / 100.0f;
	speedX *= (rand() % 2 == 0) ? -1.0f : 1.0f; // Randomize direction
	float speedY = static_cast<float>(1.0f);
	float speedZ = static_cast<float>(rand() % 100) / 100.0f;
	speedZ *= (rand() % 2 == 0) ? -1.0f : 1.0f; // Randomize direction
	unsigned char r = static_cast<unsigned char>(rand() % 256);
	unsigned char g = static_cast<unsigned char>(rand() % 256);
	unsigned char b = static_cast<unsigned char>(rand() % 256);
	unsigned char a = static_cast<unsigned char>(rand() % 256);
	float size = static_cast<float>(1.0f);
	float life = static_cast<float>(rand() % 2) + 1;
	float angle = static_cast<float>(rand() % 360);
	float angleDir = static_cast<float>(rand() % 2 == 0) ? -1.0f : 1.0f;

	AddParticle(x, y, z, speedX, speedY, speedZ, r, g, b, a, size, life, angle, angleDir);
}



void CParticleSystem::UpdateSmoke(float deltaTime)
{
	fTime += 0.1;

	if (fTime > 1.0f)
	{
		CreateRandomParticleSmoke(2, 20);
		fTime = 0.0f;
	}

	for (int i = 0; i < ParticlesContainer.size(); i++)
	{
		CParticles* particle = ParticlesContainer[i];
		particle->pos += particle->speed * 0.5f;
		particle->size += 0.5f; // Increase size over time

		particle->angle += particle->angleDir; // Rotate the particle
		if ((particle->angle > 360.0f) || (particle->angle < -360.0f))
			particle->angle = 0.0f;

		particle->life -= 0.01f;
		if (particle->life <= 0.0f)
		{
			delete particle;
			ParticlesContainer.erase(ParticlesContainer.begin() + i);
			i--;
			//CreateRandomParticleSmoke(2, 20);
		}
	}
}

void CParticleSystem::RenderSmoke(float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.3f);

	glPushMatrix();
	glTranslatef(x, y, z);
	for (int i = 0; i < ParticlesContainer.size(); i++)
	{
		CParticles* particle = ParticlesContainer[i];

		glColor4ub(255, 255, 255, particle->life * 255);
		texture.Use();
		glPushMatrix();
		float matrixBillboard[16] =
		{
			pCamera->Right[0],		pCamera->Right[1],		pCamera->Right[2],		0.0f,
			pCamera->Up[0],			pCamera->Up[1],			pCamera->Up[2],			0.0f,
			pCamera->Forward[0],	pCamera->Forward[1],	pCamera->Forward[2],	0.0f,
			particle->pos.x,		particle->pos.y,		particle->pos.z,		1.0f
		};
		glMultMatrixf(matrixBillboard);

		glRotatef(particle->angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

		glBegin(GL_QUADS);
		//glColor3ub(particle->r, particle->g, particle->b);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-particle->size, -particle->size, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(particle->size, -particle->size, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(particle->size, particle->size, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-particle->size, particle->size, 0.0f);
		glEnd();

		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}