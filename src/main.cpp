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
    TextureClass containerTex("../resources/textures/container2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    TextureClass containerSpecTex("../resources/textures/container2_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

    // create a sphere with default params;
// radius=1, sectors=36, stacks=18, smooth=true
    Sphere sphere;

    // create VAO to store all vertex array state to VAO
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // create VBO to copy interleaved vertex data (V/N/T) to VBO
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
                sphere.getInterleavedVertexSize(), // data size, # of bytes
                sphere.getInterleavedVertices(),   // ptr to vertex data
                GL_STATIC_DRAW);                   // usage

    // create VBO to copy index data to VBO
    GLuint iboId;
    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
                sphere.getIndexSize(),             // data size, # of bytes
                sphere.getIndices(),               // ptr to index data
                GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // set attrib arrays with stride and offset
    int stride = sphere.getInterleavedStride();     // should be 32 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float)*3));
    glVertexAttribPointer(2,  2, GL_FLOAT, false, stride, (void*)(sizeof(float)*6));


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
        mainShader.setFloat("shininess", 32.0f);
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
        Light light(mainShader, true, 0, false, camera.Position, camera.Front);
        light.turnOnTheLights();

        // draw a sphere with VAO
        glBindVertexArray(vaoId);
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
