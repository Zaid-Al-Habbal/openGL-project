#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include <stb_image.h>
#include "Controller.h"
#include "Scene.h"

using namespace std;

int main()
{
    //Controller:
    Controller controller;
    if (!controller.initializeWindow("Learning CG")) return -1;
    controller.initializeOpenGLSettings();
    
    //Scene:
    Scene scene;
    
    // render loop:
    while(!controller.shouldClose()){
        controller.updateDeltaTime();
        controller.processInput();

        // render
        scene.render(controller);
        
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}