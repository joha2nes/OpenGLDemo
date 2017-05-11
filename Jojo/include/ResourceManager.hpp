#pragma once
#include <string>
#include <vector>
#include <map>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "GUIButton.hpp"

struct Vertex;
struct Transform;
class Shader;
class Texture;
class Mesh;
class Font;
struct Text;
class SceneObject;
class SailingBoat;
class Skybox;
class Sprite;
class GUIButton;
class GUIImage;
class GUIText;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Shader* loadShader(std::string vsFilename, std::string fsFilename);
	Texture* loadTexture(std::string textureFilename);
	Font* loadFont(std::string fontFilename);
	Mesh* loadTriangleMesh();
	Mesh* loadCubeMesh();
	Mesh* loadTerrainMesh(std::string textureFilename, glm::vec3 scale, float textureScale);
	SceneObject* loadSceneObject(Mesh*, float x, float y, float z);
	SceneObject* loadSceneObject(Mesh*, Texture*, float x, float y, float z);
	SceneObject* loadSceneObject(Mesh*, const Transform&);
	SceneObject* loadSceneObject(Mesh*, Texture*, const Transform&);
	SceneObject* loadSceneObject(Mesh*, const Transform&, std::vector<SceneObject*>);
	SceneObject* loadSceneObject(Mesh*, Texture*, const Transform&, std::vector<SceneObject*>);
	SceneObject* loadSceneObject(Mesh*, float x, float y, float z, std::vector<SceneObject*>);
	SceneObject* loadSailingBoat(Mesh*, Texture*, Transform, float startTime, std::vector<SceneObject*>);
	Skybox* loadSkybox(std::string textureFilename);
	Sprite* loadSprite(Texture*);
	Sprite* loadSprite(Texture*, GLuint x, GLuint y, GLuint w, GLuint h);
	template <class T>
	GUIButton* loadGUIButton(T* object, void(T::*method)(GUIButtonEvent event), Rect rect, Sprite* defaultSprite, Sprite* hoverSprite, Sprite* pressSprite, Text text)
	{
		GUIButton* butt = new GUIButton(object, method, rect, defaultSprite, hoverSprite, pressSprite, text);
		m_guiElements.push_back(butt);
		return butt;
	};
	GUIImage* loadGUIImage(Rect, Sprite*);
	GUIText* loadGUIText(const Rect&, Font*, std::string, float scale, glm::vec4 color);

	void unloadEverything();

private:
	std::map<std::string, Shader*> m_shaders;
	std::map<std::string, Texture*> m_textures;
	std::map<std::string, Font*> m_fonts;
	Mesh* m_planeMesh;
	Mesh* m_cubeMesh;
	Mesh* m_sphereMesh;
	Mesh* m_triangleMesh;
	std::vector<Mesh*> m_terrainMeshes;
	std::vector<SceneObject*> m_sceneObjects;
	std::map<std::string, Skybox*> m_skyboxes;
	std::vector<Sprite*> m_sprites;
	std::vector<GUIElement*> m_guiElements;
};