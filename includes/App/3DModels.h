#ifndef DMODELS_H
#define DMODELS_H

#include <iostream>
#include <map>

#include "Model.h"


using namespace std;

class ThreeDModels {
public:
    map<string, Model> threeDModels;
    
    ThreeDModels()
    {
        threeDModels["mirror"] = Model("../resources/objects/mirror/ornate_mirror_01_2k.gltf");


    }


    
};

#endif
