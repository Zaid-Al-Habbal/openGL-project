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
    if (!controller.initializeWindow("Neighbours From Hell")) return -1;
    
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Shaders:
    Shader mainShader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");

    //Models:


    //Textures:
    
    //VBOs:

    //for Living Room:
    VBO livingRoomVBO(LivingRoom::vertices, sizeof(LivingRoom::vertices));
    VBO roomVBO(Room::vertices, sizeof(Room::vertices));
    VBO cubeVBO(Cube::vertices, sizeof(Cube::vertices));
    VBO sofaVBO(Sofa::vertices, sizeof(Sofa::vertices));


    //VAOs:
	VAO livingRoomVAO; livingRoomVAO.init(livingRoomVBO);
	VAO roomVAO; roomVAO.init(roomVBO);
    VAO cubeVAO; cubeVAO.init(cubeVBO);
    VAO sofaVAO; sofaVAO.init(sofaVBO);
    

        //texture:
    TextureClass containerTex("../resources/textures/pattern.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    TextureClass containerSpecTex("../resources/textures/container2_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

    // create a sphere with default params;
// radius=1, sectors=36, stacks=18, smooth=true
    Cubesphere sphere;


    // create VBO to copy interleaved vertex data (V/N/T) to VBO             // usage
    VBO vbo(sphere.getInterleavedVertices(), sphere.getInterleavedVertexSize());
    VAO vao; vao.init(vbo);
    EBO ebo(sphere.getIndices(), sphere.getIndexSize());

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
        mainShader.setFloat("shininess", 64.0f);
        containerTex.Bind();
        containerSpecTex.Bind();
        containerTex.texUnit(mainShader, "texture.diffuse1", 0);
        containerSpecTex.texUnit(mainShader, "texture.specular1", 1);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("projection", projection);
        mainShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        mainShader.setMat4("model", model);
        Light light(mainShader, true, 1, false, camera.Position, camera.Front);
        light.pointLightPosition[0] = glm::vec3(0.0f, 0.0f, 3.0f);
        light.turnOnTheLights();

        // draw a sphere with VAO
        vao.Bind(); ebo.Bind();
        glDrawElements(GL_TRIANGLES,                    // primitive type
        sphere.getIndexCount(),          // # of indices
        GL_UNSIGNED_INT,                 // data type
        (void*)0);                       // offset to indices



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

	// EBO1.Delete();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
