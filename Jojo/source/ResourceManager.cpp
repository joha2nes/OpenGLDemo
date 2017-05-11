#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Font.hpp"
#include "stb_image.h"
#include "SceneObject.hpp"
#include "Skybox.hpp"
#include "Sprite.hpp"
#include "glm\glm.hpp"
#include "SailingBoat.hpp"
#include "GUIElement.hpp"
#include "GUIButton.hpp"
#include "GUIImage.hpp"
#include "GUIText.hpp"

ResourceManager::ResourceManager()
	: m_shaders({})
	, m_textures({})
	, m_planeMesh(nullptr)
	, m_cubeMesh(nullptr)
	, m_sphereMesh(nullptr)
	, m_triangleMesh(nullptr)
	, m_terrainMeshes({})
{}
ResourceManager::~ResourceManager()
{
	unloadEverything();
}

Shader* ResourceManager::loadShader(std::string vsFilename, std::string fsFilename)
{
	auto itr = m_shaders.find(vsFilename + fsFilename);
	if (itr != m_shaders.end())
		return itr->second;
	else {
		Shader* shader = new Shader(vsFilename, fsFilename);
		m_shaders.insert(std::pair<std::string, Shader*>(vsFilename + fsFilename, shader));
		return shader;
	}
}
Texture* ResourceManager::loadTexture(std::string textureFilename)
{
	auto itr = m_textures.find(textureFilename);
	if (itr != m_textures.end())
		return itr->second;
	else {
		Texture* texture = new Texture(textureFilename);
		m_textures.insert(std::pair<std::string, Texture*>(textureFilename, texture));
		return texture;
	}
}
Font* ResourceManager::loadFont(std::string fontFilename)
{
	auto itr = m_fonts.find(fontFilename);
	if (itr != m_fonts.end())
		return itr->second;
	else {
		Font* font = new Font(fontFilename);
		m_fonts.insert(std::pair<std::string, Font*>(fontFilename, font));
		return font;
	}
}
Mesh* ResourceManager::loadTriangleMesh()
{
	if (m_triangleMesh != nullptr)
		return m_triangleMesh;
	else {
		std::vector<Vertex> vertices =
		{
			Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.0f)),
			Vertex(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
		};
		m_triangleMesh = new Mesh(vertices);
		return m_triangleMesh;
	}
}
Mesh* ResourceManager::loadCubeMesh()
{
	return 0;

}
Mesh* ResourceManager::loadTerrainMesh(std::string textureFilename, glm::vec3 scale, float textureScale)
{
	// load heightmap file
	int width, height, numComponents;
	stbi_uc* heightmap = stbi_load(textureFilename.c_str(), &width, &height, &numComponents, 1);
	assert(heightmap != nullptr && "couldnt find or open heightmap");

	// create vertex data (terrain) from heightmap pixels
	const int numVertices = width * height;

	std::vector<Vertex> vertices = std::vector<Vertex>(numVertices);

	for (int i = 0, z = 0; z < height; z++) {
		for (int x = 0; x < width; x++)
		{
			const float px = ((float)x - (float)width / 2.0f) * scale.x;
			const float py = ((float)heightmap[i] / 255.0f) * scale.y;
			const float pz = ((float)z - (float)height / 2.0f) * scale.z;

			vertices.at(i).position = glm::vec3(px, py, pz);
			vertices.at(i).normal = glm::vec3(0.0f, 1.0f, 0.0f);
			vertices.at(i).texCoord = glm::vec2((float)x / textureScale, (float)z / textureScale);

			i += 1;
		}
	}

	// create index data for terrain
	int numIndices = (width - 1) * (height - 1) * 6;

	std::vector<GLuint> indices = std::vector<GLuint>(numIndices);

	for (int i = 0, y = 0; y < height - 1; y++) {
		for (int x = 0; x < width - 1; x++)
		{
			indices.at(i++) = (GLuint)(y * width + x + 1);
			indices.at(i++) = (GLuint)(y * width + x);
			indices.at(i++) = (GLuint)((y + 1) * width + x + 1);
			indices.at(i++) = (GLuint)((y + 1) * width + x);
			indices.at(i++) = (GLuint)((y + 1) * width + x + 1);
			indices.at(i++) = (GLuint)(y * width + x);
		}
	}

	stbi_image_free(heightmap);

	Mesh* mesh = new Mesh(vertices, indices, true);
	m_terrainMeshes.push_back(mesh);
	return mesh;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, float x, float y, float z)
{
	SceneObject* obj = new SceneObject(m, x, y, z);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, Texture* t, float x, float y, float z)
{
	SceneObject* obj = new SceneObject(m, t, x, y, z);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, const Transform& tr)
{
	SceneObject* obj = new SceneObject(m, tr);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, Texture* t, const Transform& tr)
{
	SceneObject* obj = new SceneObject(m, t, tr);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, const Transform& tr, std::vector<SceneObject*> objs)
{
	SceneObject* obj = new SceneObject(m, tr, objs);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, Texture* t, const Transform& tr, std::vector<SceneObject*> objs)
{
	SceneObject* obj = new SceneObject(m, t, tr, objs);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSceneObject(Mesh* m, float x, float y, float z, std::vector<SceneObject*> objs)
{
	SceneObject* obj = new SceneObject(m, x, y, z, objs);
	m_sceneObjects.push_back(obj);
	return obj;
}
SceneObject* ResourceManager::loadSailingBoat(Mesh* m, Texture* t, Transform tr, float startTime, std::vector<SceneObject*> objs)
{
	SceneObject* obj = new SailingBoat(m, t, tr, startTime, objs);
	m_sceneObjects.push_back(obj);
	return obj;
}
Skybox* ResourceManager::loadSkybox(std::string textureFilename)
{
	auto itr = m_skyboxes.find(textureFilename);
	if (itr != m_skyboxes.end())
		return itr->second;
	else {
		Skybox* skybox = new Skybox(textureFilename);
		m_skyboxes.insert(std::pair<std::string, Skybox*>(textureFilename, skybox));
		return skybox;
	}
}
Sprite* ResourceManager::loadSprite(Texture* t)
{
	Sprite* s = new Sprite(t);
	m_sprites.push_back(s);
	return s;
}
Sprite* ResourceManager::loadSprite(Texture* t, GLuint x, GLuint y, GLuint w, GLuint h)
{
	Sprite* s = new Sprite(t, x, y, w, h);
	m_sprites.push_back(s);
	return s;
}
GUIImage* ResourceManager::loadGUIImage(Rect r, Sprite* s)
{
	GUIImage* img = new GUIImage(r, s);
	m_guiElements.push_back(img);
	return img;
}
GUIText* ResourceManager::loadGUIText(const Rect& r, Font* f, std::string s, float scale, glm::vec4 color)
{
	GUIText* txt = new GUIText(r, f, s, scale, color);
	m_guiElements.push_back(txt);
	return txt;
}

void ResourceManager::unloadEverything()
{
#define del(a) { if (a != nullptr) { delete a; a = nullptr; } }
	for (auto p = m_shaders.begin(); p != m_shaders.end(); p++) del((*p).second);
	for (auto p = m_textures.begin(); p != m_textures.end(); p++) del((*p).second);
	for (auto p = m_fonts.begin(); p != m_fonts.end(); p++) del((*p).second);
	del(m_planeMesh);
	del(m_cubeMesh);
	del(m_sphereMesh);
	del(m_triangleMesh);
	for (auto t : m_terrainMeshes) del(t);
	for (auto obj : m_sceneObjects) del(obj);
	for (auto p = m_skyboxes.begin(); p != m_skyboxes.end(); p++) del((*p).second);
	for (auto s : m_sprites) del(s);
	for (auto a : m_guiElements) del(a);
	m_shaders.clear();
	m_textures.clear();
	m_fonts.clear();
	m_terrainMeshes.clear();
	m_sceneObjects.clear();
	m_skyboxes.clear();
	m_sprites.clear();
	m_guiElements.clear();
}
