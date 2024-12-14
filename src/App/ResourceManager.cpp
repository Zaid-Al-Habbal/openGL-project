#include "App/ResourceManager.h"

ResourceManager::ResourceManager()
{
    setShaders();
    setTextures();
}

void ResourceManager::setShaders()
{
    shaders[MAIN] = Shader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");
    shaders[SKYBOX] = Shader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

}

void ResourceManager::setTextures()
{   
    //blue metal
    textures[BLUE_METAL] = TextureManager("../resources/textures/blue_metal_plate_diff_1k.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[BLUE_METAL_SPEC] = TextureManager("../resources/textures/blue_metal_plate_rough_1k.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
        
}