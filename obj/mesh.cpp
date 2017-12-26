//
// Created by 方浩 on 2017/12/23.
//

#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
    // 读取数据
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);
    // 初始化缓存
    setupMesh();
}

void Mesh::setupMesh() {
    /** 初始化 **/
    //创建缓存
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定VAO和VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 导入定点数据
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // 导入索引坐标，防止重画
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    /** 设置定点属性，解释如何解析定点数据 **/
    // 第一组是定点坐标，这里利用了结构体内存连续分配的原理
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) nullptr);
    // 定点法向
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 定点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    // 设置完毕
    glBindVertexArray(0);
}

void Mesh::draw(Shader shader){
    // 绑定内容
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < textures.size(); i++) {
        // 在绑定之前激活各个纹理单元
        glActiveTexture(GL_TEXTURE0 + i);
        // 获得纹理序号
        string number;
        string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);
        else if(name == "texture_normal")
            number = std::to_string(normalNr++);
        else if(name == "texture_height")
            number = std::to_string(heightNr++);
        // 设置uniform属性
        shader.setInt(name + number, i);
        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // 绘制网格
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    // 激活默认纹理
    glActiveTexture(GL_TEXTURE0);
}