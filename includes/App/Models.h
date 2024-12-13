#ifndef MODELS_H
#define MODELS_H

#include "App.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Models : public App
{
public:
    map<string, glm::mat4> models;
    
    Models()
    {
        //cube
        const glm::mat4 MODEL(1.0f);
        models[cube] = glm::scale(MODEL, glm::vec3(0.1f, 0.1f, 0.1f));
        models[cube] = glm::translate(models[cube], glm::vec3(0.0f, 0.0f, -8.0f));
        
        //window
        models[window] = glm::scale(MODEL, glm::vec3(1.0f, 1.0f, 0.01f));
        models[window] = glm::translate(models[window], glm::vec3(0.0f, 0.0f, -2.0f));

        //mirror (3D MODEL):
        // models[mirror] = glm::translate(MODEL, glm::vec3(0.0f, 0.0f, -6.0f));
    }
};

#endif
