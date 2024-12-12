#ifndef DMODELS_H
#define DMODELS_H

#include "App.h"
#include "Model.h"

class ThreeDModels : public App
{
public:
    map<string, Model> threeDModels;
    
    ThreeDModels()
    {
        threeDModels[mirror] = Model("../resources/objects/mirror/ornate_mirror_01_2k.gltf");


    }


    
};

#endif
