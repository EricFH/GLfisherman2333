//
// Created by 方浩 on 2017/12/23.
//

#ifndef SHADER_H
#define SHADER_H

#include "common.h"

class Shader
{
public:

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    // 激活着色器
    void use();

    // 设置Uniform参数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int ID;
    // 检查编译错误
    void checkCompileErrors(GLuint shader, std::string type);
};
#endif