#ifndef COLLISION_H
#define COLLISION_H
//#include <glm\glm.hpp>
#include "common.h"
#include <vector>
const float PI = 3.14159;

struct obb_box {
	glm::vec3 center;//���ĵ�
	glm::vec3 half;//�볤
	glm::vec3 x_axis, y_axis, z_axis;//������
};


/*
���ܣ��Ÿ��ȼ�������ֵ 3*3
����: void
����:
a: ԭʼ���� ����Ϊ����ֵ
p: ��������
eps: ����
T: ��������
*/
void jacobi(glm::mat3 &a, glm::mat3 &p, double eps, int T);
/*
���ܣ�ʩ���������� 3*3
���أ�void
������
p:������������
a:����ֵ
*/
void schmidtOrthogonal(glm::mat3 &p,glm::vec3 &a);
/*
���ܣ�����Э������� 3*3
���أ�Э�������
������
vertexs����������
*/
glm::mat3 cal_cov_mat(const std::vector<glm::vec3>& vertexs);
/*
���ܣ�����obb�� private
���أ�obb�нṹ
������
vertexs����������
p����һ��������ϵ
*/
obb_box __gen_obb_box(const std::vector<glm::vec3>& vertexs, const glm::mat3 &p);
/*
����: ����obb���� public
���أ�obb�нṹ
������
vertexs : ��������
*/
obb_box gen_obb_box(const std::vector<glm::vec3>& vertexs);
/*
���ܣ���������Ƿ���ײ
���أ�����ֵ
������
����obb�нṹ
*/
bool check_collision(const obb_box& a, const obb_box& b);
#endif // !COLLISION_H

