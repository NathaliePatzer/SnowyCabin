#pragma once

#include <windows.h>
#include <stdio.h>
#include <glew.h>
#include <gl.h>
#include <glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <fstream>

//to map image filenames to textureIds
#include <string.h>
#include <map>
#include <vector>
#include <glm/glm.hpp>

// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"


/*
Ao definir o modo de renderização VERTEX_BUFFER_OBJECT_MODE para um objeto CModel_ASSIMP, 
não é possível usar objetos da classe CModel_3DS na mesma cena, pois gera incompatibilidades devido ao uso de
Vertex Arrays na CModel_3DS.

Usando qualquer outro modo de renderização (IMMEDIATE, DISPLAYLIST, VERTEX_ARRAY), não há problemas de incompatibilidade.
*/

class CModel_ASSIMP
{
public:
	struct MeshEntry 
	{		
		MeshEntry(aiMesh* mesh, bool isVBO);
		~MeshEntry();

		unsigned int elementCount;
		float* vertices;
		float* texCoords;
		float* normals;
		unsigned int* indices;		

		std::vector<glm::vec3> vVertexData;
		std::vector<glm::vec2> vTexCoordData;
		std::vector<glm::vec3> vNormalData;

		GLuint BufferNameVBO[4];
		
		enum BuffersData
		{
			V_DATA, N_DATA, T_DATA, I_DATA
		};
		
		void render();

		void CreateVBO();		
		void renderVBO();
	};

	std::vector<MeshEntry*> meshEntries;

	enum RENDER_MODE
	{
		IMMEDIATE, DISPLAYLIST, VERTEX_ARRAY, VERTEX_BUFFER_OBJECT_MODE
	};

	CModel_ASSIMP(RENDER_MODE render, std::string modelPathAndName);
	~CModel_ASSIMP();
	
	void Draw();

private:
	void Load();	
	void createAILogger();
	void destroyAILogger();
	void logInfo(std::string logString);
	void logDebug(const char* logString);
	bool Import3DFromFile(const std::string& pFile);
	std::string getBasePath(const std::string& path);
	int LoadGLTextures(const aiScene* scene);
	void Color4f(const aiColor4D *color);
	void set_float4(float f[4], float a, float b, float c, float d);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void apply_material(const aiMaterial *mtl);
	void recursive_render(const struct aiScene *sc, const struct aiNode* nd, float scale);
	void CreateDisplayList();

	


	std::string modelpath;

	// the global Assimp scene object
	const aiScene* scene;
	GLuint scene_list;
	aiVector3D scene_min, scene_max, scene_center;

	// images / texture
	std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
	GLuint*		textureIds;							// pointer to texture Array
													
	Assimp::Importer importer;	// Create an instance of the Importer class

	GLuint displayListId;
	int iRenderMode;

	bool bump;
	
};

