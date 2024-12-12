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
        Camera camera = controller.getCamera();
        
        // render
        scene.render(camera);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(controller.getWindow());
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}