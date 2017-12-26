//
// Created by 方浩 on 2017/12/24.
//

#ifndef FISHMANAGER_H
#define FISHMANAGER_H

#include "manager.h"
#include "fish.h"

static map<string, float> scaleDict; // scale映射表

class FishManager: public Manager {
public:
    FishManager();
    void add(glm::vec3 position, string path, int ID) override;
    void update(float t) override;
    void draw(Camera &camera) override;
    void remove(int ID) override;

    ~FishManager();

private:
    vector<Fish*> fishArray;
    int currentID = 0;
};


#endif //FISHMANAGER_H
