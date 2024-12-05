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

int main()
{
    //Controller:
    Controller controller;
    if (!controller.initializeWindow("Learning CG")) return -1;
    
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
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

    //Models:

    //textures:
    //..container:
    TextureClass containerTex("../resources/textures/pattern.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    TextureClass containerSpecTex("../resources/textures/container2_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    //..myWindow:
    TextureClass myWindowTex("../resources/textures/window.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass myWindowSpecTex("../resources/textures/white.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    

    //Objects;
    Cubesphere sphere;

    Cubesphere myWindow(1.0f, 0, true);
    glm::mat4 myWindowModel = glm::mat4(1.0f);
    myWindowModel = glm::scale(myWindowModel, glm::vec3(1.0f, 1.0f, 0.01f));

    //VBOs:
    VBO vbo(sphere.getInterleavedVertices(), sphere.getInterleavedVertexSize());
    VBO myWindowVBO(myWindow.getInterleavedVertices(), myWindow.getInterleavedVertexSize());
    
    //VAOs:
    VAO vao; vao.init(vbo);
    VAO myWindowVAO; myWindowVAO.init(myWindowVBO);
    
    //EBOs:
    EBO ebo(sphere.getIndices(), sphere.getIndexSize());
    EBO myWindowEBO(myWindow.getIndices(), myWindow.getIndexSize());

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
        Light light(mainShader, true, 1, true, camera.Position, camera.Front);
        light.pointLightPosition[0] = glm::vec3(0.0f, 0.0f, 3.0f);
        light.turnOnTheLights();
        
        //sphere:
        //..material:
        TextureClass::enable(mainShader, containerTex, containerSpecTex);
        //..model:
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
        mainShader.setMat4("model", model);

        //..draw:
        vao.Bind(); ebo.Bind();
        glDrawElements(GL_TRIANGLES, sphere.getIndexCount(), GL_UNSIGNED_INT, (void*)0); 
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0f));
        mainShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, sphere.getIndexCount(), GL_UNSIGNED_INT, (void*)0); 


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
