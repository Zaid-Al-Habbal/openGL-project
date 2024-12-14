#include "App/Renderer.h"
#include "Light.h"

Renderer::Renderer()
{
    ResourceManager resourceManager;
    //texture:
    textures = resourceManager.textures;
    //shaders:
    shaders = resourceManager.shaders;
    //light
    light = Light(shaders[MAIN], true, 0, false);

}

void Renderer::draw(string objectName, int numOfVertices)
{
    shaders[MAIN].setMat4("model", models[objectName]);
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElements(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)0);  

}

void Renderer::render(Controller& controller)
{
    Camera camera = controller.getCamera();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    
    //MAIN
    shaders[MAIN].use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shaders[MAIN].setMat4("projection", projection);
    shaders[MAIN].setMat4("view", view);
    shaders[MAIN].setFloat("shininess", 32.0f);
    shaders[MAIN].setFloat("alpha", 1.0f);
    

    //Light:
    light.update(camera.Position, camera.Front);
    
    
    // draw skybox as last
    skybox.setEnvironment(!controller.isNight);
    skybox.draw(shaders[SKYBOX], view, projection);
    
    //Wall:

    TextureManager::enable(shaders[MAIN], textures[TRANS_WINDOW], textures[TRANS_WINDOW_SPEC], 10.0f);
    shaders[MAIN].setFloat("alpha", 0.5f);
    //first wall:
    draw(WALL, cubes[WALL].getIndexCount());
    //second wall:
    draw(WALL2, cubes[WALL2].getIndexCount());


    
}