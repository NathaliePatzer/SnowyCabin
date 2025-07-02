#pragma once

#include <glew.h>
#include "GLTexture.h"
#include <glm/glm.hpp>
#include <vector>
#include "CCamera.h"

#include <iostream>
#include <random>
#include "CTimer.h"

class CParticles
{

public:
	// Constructor
	CParticles(float x, float y, float z, float speedX, float speedY, float speedZ,
		unsigned char r, unsigned char g, unsigned char b, unsigned char a,
		float size, float life, float angle, float angleDir);
	
	// Destructor
	~CParticles();

	glm::vec3 pos, speed;
	unsigned char r, g, b, a; 
	float size, angle, angleDir, life; 
};

class CParticleSystem
{
public:
	enum ParticleType
	{
		RAIN,
		SNOW,
		EXPLOSION,
		SMOKE,
		SPARK
	};

	CParticleSystem(CCamera* pCamera);
	~CParticleSystem();
	void Init(ParticleType particleType, int maxParticles, char* texturePath);	
	void KillAllParticles();
	void KillParticle(int index);
	void AddParticle(float x, float y, float z, float speedX, float speedY, float speedZ,
		unsigned char r, unsigned char g, unsigned char b, unsigned char a,
		float size, float life, float angle, float angleDir);
	int GetParticlesCount();


	void UpdateSnow(float deltaTime);
	void RenderSnow();
	void CreateRandomParticleSnow();

	void UpdateSmoke(float deltaTime);
	void RenderSmoke(float x, float y, float z);
	void CreateRandomParticleSmoke(int sizeMIN, int sizeMAX);

private:
	int iMaxParticles;
	GLTexture texture;
	std::vector<CParticles*> ParticlesContainer;
	CCamera* pCamera;
	float fTime;
};
