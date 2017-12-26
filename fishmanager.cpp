//
// Created by 方浩 on 2017/12/24.
//

#include "fishmanager.h"

#define MAX_FISH 100

FishManager::FishManager(): Manager() {
    // 初始化尺寸列表
    scaleDict["res/model/shark/megalodon.FBX"] = 0.03;

    add(glm::vec3(0.0f, 0.0f, -20.0f), "res/model/shark/megalodon.FBX", currentID);
    add(glm::vec3(0.0f, 0.0f, -10.0f), "res/model/b/MantaT.max", currentID);
}

FishManager::~FishManager() {
    for (auto fish : fishArray){
        delete fish;
    }
}

void FishManager::update(float t) {
    for (auto fish : fishArray){
        fish->update(t);
    }
}

void FishManager::draw(Camera &camera) {
    for (auto fish : fishArray){
        fish->draw(camera);
    }
}

void FishManager::add(glm::vec3 position, string path, int ID) {
    float scale = scaleDict[path];
    Fish* fish = new Fish(position, scale, path, ID);
    fishArray.push_back(fish);
    currentID = (currentID + 1) % MAX_FISH;
}

void FishManager::remove(int ID) {
    vector<Fish>::iterator it;
    int index = 0;
    for (auto& fish : fishArray){
        if (fish->ID == ID){
            break;
        }
        index++;
    }
    fishArray.erase(fishArray.begin()+index);
}