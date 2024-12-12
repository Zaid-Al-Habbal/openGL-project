#ifndef SCENE_H
#define SCENE_H

#include "App/App.h"
#include "App/Textures.h"
#include "App/Shaders.h"
#include "App/Models.h"
#include "App/Objects.h"
#include "App/3DModels.h"

#include "Skybox.h"
#include "Controller.h"

class Scene : public App
{
private:
    Skybox skybox;     // skybox.setEnvironment(false); // evening
    map<string, TextureManager> textures;
    map<string, Shader> shaders;
    map<string, VAO> vaos;
    map<string, EBO> ebos;
    map<string, Sphere> spheres;
    map<string, Icosphere> icos;
    map<string, Cubesphere> cubes;
    map<string, Cylinder> cylinders;
    map<string, Cone> cones;
    map<string, Torus> toruses;
    map<string, glm::mat4> models;
    map<string, Model> threeDModels;

    Textures texturesBuilder;
    Shaders shadersBuilder;
    Objects objectsBuilder;
    Models modelsBuilder;
    ThreeDModels threeDModelsBuilder;
    

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;


public:
    Scene();
    void render(Controller& controller);
    void draw(string ObjectName, int numOfVertices);
};
#endif
