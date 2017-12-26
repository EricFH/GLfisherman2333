//
// Created by 方浩 on 2017/12/23.
//

#ifndef MODEL_H
#define MODEL_H

#include "common.h"
#include "mesh.h"
#include "shader.h"
#include "stb_image.h"
#include "camera.h"

#include "collision.h"
#include <map>

using namespace std;

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

unsigned int TextureFromFile(const char *path, const string &directory);
static map<string, vector<Mesh>> meshDict; // mesh记录表，减少开销

class Model{
public:
    explicit Model(string path, glm::vec3 position);
    // 在指定位置，按比例画出模型，旋转先不考虑
    void modelDraw(Camera& camera);
    // 获取顶点坐标信息，用于碰撞检测
    vector<glm::vec3>& getVertex();

    // update接口
    virtual void update(float t)=0;

    float scale; // 模型导入后调整尺度

    obb_box box; // 添加
protected:
    glm::vec3 position;
private:
    // 模型数据
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded; // 记录已经导入的模型，减小开销
    vector<glm::vec3> vertices; // 专门记录坐标，用于碰撞检测
    Shader shader;


    // 内部操作
    void loadModel(string path);
    // 遍历时处理每个mesh节点
    void processNode(aiNode *node, const aiScene *scene);
    // 处理每个节点上的mesh信息
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    // 处理每个mesh的texture，返回一组texture
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};



#endif