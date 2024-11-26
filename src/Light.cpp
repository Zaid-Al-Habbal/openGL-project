#include "Light.h"

Light::Light(Shader myShader, bool enableDir, bool enablePoint, bool enableSpot, glm::vec3 cameraPos, glm::vec3 cameraFront, 
                TextureClass materialDiffuse, TextureClass materialSpecular)
{
    this->myShader = myShader;
    this->enableDir = enableDir;
    this->enablePoint = enablePoint;
    this->enableSpot = enableSpot;
    //DirLight:
    this->dirLightColor = glm::vec3(1.0f);
    this->dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
    this->dirLightSpecular = glm::vec3(1.0f);
    //PointLight:
    this->pointLightColor = glm::vec3(1.0f);
    this->pointLightSpecular = glm::vec3(1.0f);
    this->pointLightConstant = 1.0f;
    this->pointLightLinear = 0.09f;
    this->pointLightQuadratic = 0.032f;
    this->pointLightPosition = glm::vec3( 0.7f,  0.2f,  2.0f),
    //SpotLight:
    this->spotLightColor = glm::vec3(1.0f);
    
    this->spotLightSpecular = glm::vec3(1.0f);
    this->spotLightConstant = 1.0f;
    this->spotLightLinear = 0.09f;
    this->spotLightQuadratic = 0.032f;
    this->spotLightPosition = cameraPos,
    this->spotLightCutOff = 12.5f;
    this->spotLightOuterCutOff = 17.5f;
    this->spotLightDirection = cameraFront;
    //viewPos:
    this->viewPos = cameraPos;
    //material:
    this->materialShininess = 32.0f;
    this->materialDiffuse = materialDiffuse;
    this->materialSpecular = materialSpecular;
 
}

void Light::turnOnTheLights(){
    myShader.use();
    myShader.setVec3("viewPos", viewPos);
    //Material:
    materialDiffuse.texUnit(myShader, "material.diffuse", 0);
    materialSpecular.texUnit(myShader, "material.specular", 1);
    myShader.setFloat("material.shininess", 32.0f);
    

    //lights:
    // directional light
    myShader.setBool("enableDir", enableDir);
    this->dirLightDiffuse = this->dirLightColor * glm::vec3(0.8f);
    this->dirLightAmbient = this->dirLightDiffuse * glm::vec3(0.2f);
    myShader.setVec3("dirLight.direction", dirLightDirection);
    myShader.setVec3("dirLight.specular", dirLightSpecular);
    myShader.setVec3("dirLight.ambient", dirLightAmbient);
    myShader.setVec3("dirLight.diffuse", dirLightDiffuse);
    // point light 
    myShader.setBool("enablePoint", enablePoint);
    this->pointLightDiffuse = this->pointLightColor * glm::vec3(0.8f);
    this->pointLightAmbient = this->pointLightDiffuse * glm::vec3(0.2f);
    myShader.setVec3("pointLights[0].position", pointLightPosition);
    myShader.setVec3("pointLights[0].ambient", pointLightAmbient);
    myShader.setVec3("pointLights[0].diffuse", pointLightDiffuse);
    myShader.setVec3("pointLights[0].specular", pointLightSpecular);
    myShader.setFloat("pointLights[0].constant", pointLightConstant);
    myShader.setFloat("pointLights[0].linear", pointLightLinear);
    myShader.setFloat("pointLights[0].quadratic", pointLightQuadratic);
    // spotLight
    myShader.setBool("enableSpot", enableSpot);
    this->spotLightDiffuse = this->spotLightColor * glm::vec3(0.8f);
    this->spotLightAmbient = this->spotLightDiffuse * glm::vec3(0.2f);
    myShader.setVec3("spotLight.position", spotLightPosition);
    myShader.setVec3("spotLight.direction", spotLightDirection);
    myShader.setVec3("spotLight.ambient", spotLightAmbient);
    myShader.setVec3("spotLight.diffuse", spotLightDiffuse);
    myShader.setVec3("spotLight.specular", spotLightSpecular);
    myShader.setFloat("spotLight.constant", spotLightConstant);
    myShader.setFloat("spotLight.linear", spotLightLinear);
    myShader.setFloat("spotLight.quadratic", spotLightQuadratic);
    myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spotLightCutOff)));
    myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotLightOuterCutOff)));
    //material:
    materialDiffuse.texUnit(myShader, "material.diffuse", 0);
    materialSpecular.texUnit(myShader, "material.specular", 1);
    myShader.setFloat("material.shininess", materialShininess);
    
}
