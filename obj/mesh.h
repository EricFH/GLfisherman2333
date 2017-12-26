//
// Created by 方浩 on 2017/12/23.
//

#ifndef MESH_H
#define MESH_H


#include "common.h"
#include "shader.h"
using namespace std;

struct Vertex {
    // 位置
    glm::vec3 Position;
    // n法向量
    glm::vec3 Normal;
    // 纹理坐标
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path; // 我们储存纹理的路径用于与其它纹理进行比较
};

class Mesh{
public:
    /*网格数据*/
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;
    // 构造函数
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    // 渲染网格
    void draw(Shader shader);

private:
    // 为每个mesh对象提供底层渲染
    unsigned int VBO, EBO;
    // 初始化buffer对象
    void setupMesh();
};

#endif