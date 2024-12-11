#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class Skybox {
private:
    unsigned int VAO, VBO;
    unsigned int cubemapTextureMorning, cubemapTextureEvening;
    unsigned int currentTexture;
    unsigned int loadCubemap(const std::vector<std::string>& faces);

public:
    Skybox(Shader shader);
    ~Skybox();
    void draw(Shader shader, const glm::mat4& view, const glm::mat4& projection);
    void setEnvironment(bool isMorning);
};

#endif
