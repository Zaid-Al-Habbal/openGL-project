#include "Scene.h"
#include "Light.h"

Scene::Scene()
{
    textures = texturesBuilder.textures;
    shaders = shadersBuilder.shaders;
    vaos = objectsBuilder.vaos;
    ebos = objectsBuilder.ebos;
    cubes = objectsBuilder.cubes;
    spheres = objectsBuilder.spheres;
    icos = objectsBuilder.icos;
    cones = objectsBuilder.cones;
    cylinders = objectsBuilder.cylinders;
    toruses = objectsBuilder.toruses;
    models = modelsBuilder.models;
    threeDModels = threeDModelsBuilder.threeDModels;
}

void Scene::draw(string objectName, int numOfVertices)
{
    shaders["main"].setMat4("model", models[objectName]);
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)0);  

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
    Light light(shaders["main"], true, 1, false, camera.Position, camera.Front);
    light.pointLightPosition[0] = glm::vec3(0.0f, 0.0f, 3.0f);
    light.turnOnTheLights();
    
    //cube:
    TextureManager::enable(shaders["main"], textures["container"], textures["containerSpec"]);
    draw("cube", cubes["cube"].getIndexCount());
    

    // draw skybox as last
    skybox.draw(shaders["skybox"], view, projection);

    //Window:
    //..material:
    TextureManager::enable(shaders["main"], textures["window"], textures["windowSpec"]);
    shaders["main"].setFloat("alpha", 0.5f);

    //..draw:
    draw("window", cubes["window"].getIndexCount());

    //Window:
    shaders["main"].setMat4("model", models["mirror"]);
    threeDModels["mirror"].Draw(shaders["main"]);
}