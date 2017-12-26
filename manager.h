//
// Created by 方浩 on 2017/12/24.
//

#ifndef MANAGER_H
#define MANAGER_H

#include "obj/model.h"

class Manager {
public:
    virtual void add(glm::vec3 position, string path, int ID)=0;
    virtual void remove(int ID)=0;
    virtual void update(float t)=0;
    virtual void draw(Camera &camera)=0;

};


#endif //MANAGER_H
