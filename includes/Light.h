#ifndef Light_CLASS_H
#define Light_CLASS_H

#include<glad/glad.h>
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shader.h"
#include"TextureClass.h"
#include "camera.h"



class Light
{
public:
    // directional light:
    glm::vec3 dirLightColor, dirLightDirection, dirLightAmbient, dirLightDiffuse, dirLightSpecular;
    // Point light:
    glm::vec3 pointLightColor, pointLightAmbient, pointLightDiffuse, pointLightSpecular, pointLightPosition;
    float pointLightConstant, pointLightLinear, pointLightQuadratic;
    // Spot light:
    glm::vec3 spotLightColor, spotLightPosition, spotLightDirection, spotLightAmbient, spotLightDiffuse, spotLightSpecular;
    float spotLightConstant, spotLightLinear, spotLightQuadratic, spotLightCutOff,spotLightOuterCutOff;
    
    //for turning Lights on and off
    bool enableDir, enablePoint, enableSpot;
    //shader
    Shader myShader;
    //comera position:
    glm::vec3 viewPos;
    //Material:
    
    Light(Shader myShader, bool enableDir, bool enablePoint, bool enableSpot, glm::vec3 cameraPos, glm::vec3 cameraFront);

    void turnOnTheLights();
	
};
#endif