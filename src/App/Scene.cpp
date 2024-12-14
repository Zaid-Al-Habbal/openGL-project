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
    for(int i=0; i<100; i++){
        model = translate(model, vec3(300.0f, 0.0f, 0.0f));
        models[WALL].push_back(model);
    } 
    cubeBuffers(WALL);

    //TRANSFORMER:
    stbi_set_flip_vertically_on_load(true);
    threeDModels[TRANSFORMER] = Model("../resources/objects/transformers-one-orion-pax/source/scene.gltf");
    model = translate(MODEL, glm::vec3(0.0f, 0.0f, -8.0f));
    model = rotate(model, radians(180.0f), Y);
    models[TRANSFORMER].push_back(model);
    for(int i=0; i<100; i++){
        model = translate(model, vec3(3.0f, 0.0f, 0.0f));
        models[TRANSFORMER].push_back(model);
        model = translate(model, vec3(0.0f, 3.0f, 0.0f));
        models[TRANSFORMER].push_back(model);
        
    }
    threeDmodelBuffers(TRANSFORMER);


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

void Scene::threeDmodelBuffers(string name)
{
    //..instanceVBO:
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, models[name].size() * sizeof(glm::mat4), models[name].data(), GL_STATIC_DRAW);
    for (unsigned int i = 0; i < threeDModels[name].meshes.size(); i++)
    {
        unsigned int VAO = threeDModels[name].meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
} 