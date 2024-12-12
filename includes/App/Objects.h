#ifndef OBJECTS_H
#define OBJECTS_H

#include <iostream>
#include <map>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "color.hpp"
#include "Sphere.h"
#include "Icosphere.h"
#include "Cubesphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Torus.h"
#include "Skybox.h"

using namespace std;

class Objects {
public:
    map<string, VAO> vaos;
    map<string, EBO> ebos;
    map<string, Sphere> spheres;
    map<string, Icosphere> icos;
    map<string, Cubesphere> cubes;
    map<string, Cylinder> cylinders;
    map<string, Cone> cones;
    map<string, Torus> toruses;
    
    Objects()
    {
        setSphere();
        setIcosphere();
        setCubesphere();
        setCylinder();
        setCone();
        setTorus();
    }

    void setSphere()
    {

    }

    void setIcosphere()
    {

    }

    void setCubesphere()
    {
        //window:
        cubes["window"] = Cubesphere(1.0f, 0, true);
        cubeBuffers("window");
        
        //cube:
        cubes["cube"] = Cubesphere(1.0f, 0, true);
        cubeBuffers("cube");
        
    }

    void setCylinder()
    {

    }

    void setCone()
    {

    }

    void setTorus()
    {

    }

    void cubeBuffers(string name)
    {
        //..vbo:
        VBO vbo(cubes[name].getInterleavedVertices(), cubes[name].getInterleavedVertexSize());
        //..vao:
        vaos[name] = VAO() ; vaos[name].init(vbo);
        //..ebo:
        ebos[name] = EBO(cubes[name].getIndices(), cubes[name].getIndexSize());
    } 
    
};

#endif
