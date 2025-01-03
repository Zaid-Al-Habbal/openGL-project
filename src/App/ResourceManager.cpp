#include "App/ResourceManager.h"

ResourceManager::ResourceManager()
{
    setShaders();
    setTextures();
}

void ResourceManager::setShaders()
{
    //MAIN:
    shaders[MAIN] = Shader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");
    //SKYBOX:
    shaders[SKYBOX] = Shader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

}

void ResourceManager::setTextures()
{   
    stbi_set_flip_vertically_on_load(true);

    //blue metal
    textures[BLUE_METAL] = TextureManager("../resources/textures/blue_metal_plate_diff_1k.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[BLUE_METAL_SPEC] = TextureManager("../resources/textures/blue_metal_plate_rough_1k.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //awsome face:
    textures[AWESOME_FACE] = TextureManager("../resources/textures/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[AWESOME_FACE_SPEC] = TextureManager("../resources/textures/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //Transparncy window:
    textures[AWESOME_FACE] = TextureManager("../resources/textures/window.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[AWESOME_FACE_SPEC] = TextureManager("../resources/textures/window.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //ROBOT
    textures[ROBOT] = TextureManager("../resources/textures/diffuse.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[ROBOT_SPEC] = TextureManager("../resources/textures/specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
}