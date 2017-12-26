#ifndef CAMERA_H
#define CAMERA_H

//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f;
#define SENSITIVTY 0.1f;
#define ZOOM 45.0f;

class Camera
{
private:
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f);
        float yaw = YAW;
        float pitch = PITCH;
        float speed = SPEED;
        float sensitivty = SENSITIVTY;
        float zoom = ZOOM;
        bool firstmouse;
        double lastx, lasty;
        void renew();
public:
        /*
        ¦Ë(0,0,0),yz
        */
        Camera();
        /*
        ¦Ë¨´
        @param position ¦Ë
        @param worldup 
        @param yaw  -90
        @param pitch   0
        */
        Camera(glm::vec3 position, glm::vec3 worldup, float yaw, float pitch);
        /*
        
        */
        ~Camera();
        /*
        LookAt
        @return lookAt
        */
        glm::mat4 get_view();
        /*
        
        @return 
        */
        glm::vec3 get_front();
        /*
        
        @return 
        @param ratio  800/600
        @parm rear  0.1
        @parm far_dis   100
        */
        glm::mat4 get_projection(float ratio, float rear, float far_dis);
        /*
        ()
        @param key ascii
        */
        void onKeyBoard(char key, float t);
        /*
        (
        @param xpos x
        @param ypos y
        */
        void onMouseMove(int xpos, int ypos);
        /*
        (
        @param yoffset 
        */
        void onMouseScroll(float yoffset);
};
#endif
