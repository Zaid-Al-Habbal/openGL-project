#include "App/Scene.h"

using namespace glm;

Scene::Scene()
{
    const glm::mat4 MODEL(1.0f);

    //wall:
    cubes[WALL] = Cubesphere(30.0f, 0, true);
    cubeBuffers(WALL);
    models[WALL] = scale(MODEL, vec3(1.0f, 1.0f, 0.005f));
    models[WALL] = translate(models[WALL], glm::vec3(0.0f, 0.0f, -8.0f));
}

void Scene::cubeBuffers(string name)
{
    //..vbo:
    VBO vbo(cubes[name].getInterleavedVertices(), cubes[name].getInterleavedVertexSize());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo);
    //..ebo:
    ebos[name] = EBO(cubes[name].getIndices(), cubes[name].getIndexSize());
} 