#include "App/Scene.h"

using namespace glm;

Scene::Scene()
{
    const glm::mat4 MODEL(1.0f);
    const glm::vec3 X(1.0f, 0.0f, 0.0f), Y(0.0f, 1.0f, 0.0f), Z(0.0f, 0.0f, 1.0f);

    //wall:
    cubes[WALL] = Cubesphere(30.0f, 1, false); 
    mat4 model = translate(MODEL, glm::vec3(0.0f, 0.0f, -8.0f));
    model = rotate(model, radians(90.0f), Y);
    model = scale(model, vec3(0.01f, 1.0f, 1.0f));
    models[WALL].push_back(model);
    for(int i=0; i<10; i++){
        model = translate(model, vec3(300.0f, 0.0f, 0.0f));
        models[WALL].push_back(model);
    } 
    cubeBuffers(WALL);
}

void Scene::cubeBuffers(string name)
{
    //..vbo:
    VBO vbo(cubes[name].getInterleavedVertices(), cubes[name].getInterleavedVertexSize());
    //..instanceVBO:
    VBO instanceVBO(models[name], (int)models[name].size());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo, instanceVBO);
    //..ebo:
    ebos[name] = EBO(cubes[name].getIndices(), cubes[name].getIndexSize());
} 