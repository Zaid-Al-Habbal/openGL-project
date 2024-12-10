#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <bits/stdc++.h>

#include "Controller.h"
#include "model.h"
#include "shader.h"
#include "filesystem.h"
#include "TextureClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Light.h"
#include "Cube.h"
#include "LivingRoom.h"
#include "Room.h"
#include "color.hpp"
#include <Sofa.h>
#include "Sphere.h"
#include "Icosphere.h"
#include "Cubesphere.h"
#include "Cylinder.h"
#include <Cone.h>
#include "Torus.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

//for skybox:
unsigned int loadCubemap(vector<std::string> faces);

int main()
{
    //Controller:
    Controller controller;
    if (!controller.initializeWindow("Learning CG")) return -1;
    
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    // enable blending:
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //enable face culling:
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT); 

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Shaders:
    Shader mainShader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");
    Shader skyboxShader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

    //Models:
    // Model mirror("../resources/objects/mirror/ornate_mirror_01_2k.gltf");

    //textures:
    //..container:
    TextureClass containerTex("../resources/textures/pattern.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    TextureClass containerSpecTex("../resources/textures/container2_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    //..myWindow:
    TextureClass myWindowTex("../resources/textures/window.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass myWindowSpecTex("../resources/textures/white.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    

    //Objects;
    Cubesphere myWindow(1.0f, 0, true);
    glm::mat4 myWindowModel = glm::mat4(1.0f);
    glm::mat4 cubeModel = glm::scale(myWindowModel, glm::vec3(0.1f, 0.1f, 0.1f));
    cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 0.0f, -3.0f));
    myWindowModel = glm::scale(myWindowModel, glm::vec3(1.0f, 1.0f, 0.01f));

    //VBOs:
    VBO myWindowVBO(myWindow.getInterleavedVertices(), myWindow.getInterleavedVertexSize());
    
    //VAOs:
    VAO myWindowVAO; myWindowVAO.init(myWindowVBO);
    
    //EBOs:
    EBO myWindowEBO(myWindow.getIndices(), myWindow.getIndexSize());

    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //skybox faces:
    vector<string> faces = 
    {
        "../resources/objects/skybox/right.jpg",
        "../resources/objects/skybox/left.jpg",
        "../resources/objects/skybox/top.jpg",
        "../resources/objects/skybox/bottom.jpg",
        "../resources/objects/skybox/front.jpg",
        "../resources/objects/skybox/back.jpg"
    };
    unsigned int cubemapTexture = loadCubemap(faces);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);
    
    // render loop:
    while(!controller.shouldClose()){
        controller.updateDeltaTime();
        controller.processInput();
        Camera camera = controller.getCamera();
        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        
        //start mainShader:
        
        mainShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("projection", projection);
        mainShader.setMat4("view", view);
        mainShader.setFloat("shininess", 32.0f);
        mainShader.setFloat("alpha", 1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        //Light:
        Light light(mainShader, true, 1, false, camera.Position, camera.Front);
        light.pointLightPosition[0] = glm::vec3(0.0f, 0.0f, 3.0f);
        light.turnOnTheLights();
        
        //cube:
        TextureClass::enable(mainShader, containerTex, containerSpecTex);
        //..model:
        mainShader.setMat4("model", cubeModel);
        //..draw:
        myWindowVAO.Bind(); myWindowEBO.Bind();
        glDrawElements(GL_TRIANGLES, myWindow.getIndexCount(), GL_UNSIGNED_INT, (void*)0);  




         // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        //myWindow:
        //..material:
        TextureClass::enable(mainShader, myWindowTex, myWindowSpecTex);
        mainShader.setFloat("alpha", 0.5f);
        
        //..model:
        model = glm::translate(myWindowModel, glm::vec3(0.0f, 0.0f, -2.0f));
        mainShader.setMat4("model", model);

        //..draw:
        myWindowVAO.Bind(); myWindowEBO.Bind();
        glDrawElements(GL_TRIANGLES, myWindow.getIndexCount(), GL_UNSIGNED_INT, (void*)0);  

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

	// EBO1.Delete();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}