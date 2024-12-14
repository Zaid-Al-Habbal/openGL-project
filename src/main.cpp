#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include <stb_image.h>
#include "Controller.h"
#include "App/Renderer.h"

using namespace std;

int main()
{
    //Controller:
    Controller controller;
    if (!controller.initializeWindow("Learning CG")) return -1;
    controller.initializeOpenGLSettings();
    
    //Renderer:
    Renderer renderer;
    
    // render loop:
    while(!controller.shouldClose()){
        controller.updateDeltaTime();
        controller.processInput();

        // render
        renderer.render(controller);
        
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}