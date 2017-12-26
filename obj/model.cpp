//
// Created by 方浩 on 2017/12/23.
//

#include "model.h"


Model::Model(string path, glm::vec3 position):shader("res/shader/model_loading.vs", "res/shader/model_loading.fs") {
    this->position = position;
    // 先检索模型是否已经导入过，减少开销
    if (meshDict.find(path)==meshDict.end()){
        loadModel(path);
        meshDict[path] = this->meshes;
    }
    else{
        this->meshes = meshDict[path];
    }
    box = gen_obb_box(vertices);
}

void Model::modelDraw(Camera& camera) {

    // 先激活着色器
    shader.use();

    glm::mat4 projection = camera.get_projection((float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.get_view();

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    glm::mat4 model;
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    shader.setMat4("model", model);

    // 遍历画出所有网格
    for (auto &mesh : meshes)
        mesh.draw(shader);
}

void Model::loadModel(string path) {
    // 读取文件
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // 错误检验
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // 获取文件所在目录
    directory = path.substr(0, path.find_last_of('/'));
    // 从根部遍历整个scene树
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // 遍历叶子节点
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        // 把mesh数据存入meshes数据中
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // 对子节点递归执行
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // 遍历mesh中的顶点
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector; // 临时变量
        // 位置
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        this->vertices.push_back(vector); // 记录顶点坐标
        // 法向
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // 纹理
        // 判断是否包含纹理坐标
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }

    // 遍历所有面(三角形)，储存索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // 处理材质
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse 映射
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular 映射
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal 映射
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height 高度映射(存疑)
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // 返回整个处理好的mesh
    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        // 优先从内存中读取texture，减少开销

        for (auto &j : textures_loaded) {
            if(std::strcmp(j.path.data(), str.C_Str()) == 0) {
                textures.push_back(j);
                skip = true; // flag
                break;
            }
        }
        if(!skip)
        {
            // 添加texture
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // 注册防止重复
        }
    }
    return textures;
}

// 从文件中获取纹理，返回ID
unsigned int TextureFromFile(const char *path, const string &directory)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    // 使用stb_image读取纹理图片
    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


vector<glm::vec3>& Model::getVertex() {
    return vertices;
}