#ifndef SHADERS_H
#define SHADERS_H

#include <iostream>
#include <map>
#include "shader.h"

using namespace std;

class Shaders {
public:
    map<string, Shader> shaders;
    Shaders()
    {
        shaders["main"] = Shader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");
        shaders["skybox"] = Shader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

    }
};

#endif
