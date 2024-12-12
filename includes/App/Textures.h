#ifndef TEXTURES_H
#define TEXTURES_H

#include "App.h"
#include "TextureManager.h"

class Textures : public App
{
public:
    map<string, TextureManager> textures;
    
    Textures()
    {
        textures[container] = TextureManager("../resources/textures/pattern.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        textures[containerSpec] = TextureManager("../resources/textures/container2_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

        textures[window] = TextureManager("../resources/textures/window.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        textures[windowSpec] = TextureManager("../resources/textures/white.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    };
    
};

#endif
