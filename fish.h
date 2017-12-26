//
// Created by 方浩 on 2017/12/24.
//

#ifndef FISH_H
#define FISH_H

// 定义鱼的各个状态
#define NORMAL 0

#include "obj/model.h"
#include <random>

// 随机值发生器
static default_random_engine engine;
static uniform_real_distribution<double> uniform(-1.0, 1.0); // 平均分布
static normal_distribution<float > normal(1, 0); // 正太分布

class Fish : public Model{
public :
    Fish(glm::vec3 position, float scale, string path, int ID);
    void update(float t) override;
    void draw(Camera& camera);
    int ID;
private:
    glm::vec3 direction;
    float speed;
    int state;

    default_random_engine e; // 随机引擎

    // 这里加入AI
    void think();
};


#endif //FISH_H
