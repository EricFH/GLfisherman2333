//
// Created by 方浩 on 2017/12/24.
//

#include "fish.h"

Fish::Fish(glm::vec3 position, float scale, string path, int ID):Model(path, position) {
    this->ID = ID;
    this->direction = glm::vec3(uniform(engine), uniform(engine), uniform(engine));
    this->speed = normal(engine);
    this->state = NORMAL;
    this->scale = scale;
}

void Fish::draw(Camera &camera) {
    modelDraw(camera);
}

void Fish::update(float t) {
    think();
    direction = glm::normalize(direction);
    position += direction * speed * t;
}

void Fish::think() {
//    direction = float(0.01) * glm::vec3(uniform(engine), uniform(engine), uniform(engine));
    speed += float(0.1) * uniform(engine);
}