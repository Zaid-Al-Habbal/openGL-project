#include "Scene.h"
#include "Light.h"

Scene::Scene()
{
    //texture:
    textures = texturesBuilder.textures;
    //shaders:
    shaders = shadersBuilder.shaders;
    //buffer management
    vaos = objectsBuilder.vaos;
    ebos = objectsBuilder.ebos;
    //objects
    cubes = objectsBuilder.cubes;
    spheres = objectsBuilder.spheres;
    icos = objectsBuilder.icos;
    cones = objectsBuilder.cones;
    cylinders = objectsBuilder.cylinders;
    toruses = objectsBuilder.toruses;
    //glm::models
    models = modelsBuilder.models;
    //3D models
    threeDModels = threeDModelsBuilder.threeDModels;
    //light
    light = Light(shaders["main"], true, 0, false);

}

void Scene::draw(string objectName, int numOfVertices, int startFrom)
{
    shaders["main"].setMat4("model", models[objectName]);
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)(startFrom*sizeof(float)));  

}

void Scene::render(Controller& controller)
{
    Camera camera = controller.getCamera();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    
    shaders["main"].use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shaders["main"].setMat4("projection", projection);
    shaders["main"].setMat4("view", view);
    shaders["main"].setFloat("shininess", 32.0f);
    shaders["main"].setFloat("alpha", 1.0f);

    //Light:
    light.update(camera.Position, camera.Front);
    
    
    //cube:
    TextureManager::enable(shaders["main"], textures[container], textures[containerSpec]);
    draw(cube, cubes[cube].getIndexCount(), 0);
    

    // draw skybox as last
    skybox.setEnvironment(!controller.isNight);
    skybox.draw(shaders["skybox"], view, projection);

    //Window:
    //..material:
    TextureManager::enable(shaders["main"], textures[window], textures[windowSpec]);
    shaders["main"].setFloat("alpha", 0.5f);

    //..draw:
    draw(window, cubes[window].getIndexCount(),0);

    
}