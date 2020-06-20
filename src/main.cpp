#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/parser/parser.hh>
#include <utils/camera.hh>

#include "glutils/shader.hh"
#include "glutils/program.hh"
#include "glutils/object.hh"

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Resizing of the Window
    glViewport(0, 0, width, height);
}

float lastTime = 0.0f;
Camera camera = Camera(glm::vec3(0.0f, 0.0f,  3.0f),
                       glm::vec3(0.0f, 0.0f,  -1.0f),
                       glm::vec3(0.0f, 1.0f,  0.0f));
Camera camera_light = Camera(glm::vec3(0.0f, 0.0f,  3.0f),
                             glm::vec3(0.0f, 0.0f,  -1.0f),
                             glm::vec3(0.0f, 1.0f,  0.0f));

void processInputs(GLFWwindow* window)
{
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position_ += cameraSpeed * camera.front_;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position_ -= cameraSpeed * camera.front_;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position_ -= glm::normalize(glm::cross(camera.front_, camera.up_)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position_ += glm::normalize(glm::cross(camera.front_, camera.up_)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.position_ += camera.up_ * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.position_ -= camera.up_ * cameraSpeed;
}

bool firstMouse = true;
double lastX;
double lastY;
double yaw = 0;
double pitch = 0;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera.front_ = glm::normalize(direction);
}

void drawing(Program program, Object object1, Object object2, Object object3)
{
    // Drawing

    // create transformations
    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::translate(model1, glm::vec3(0.0f, 0.5f, 0.0f));
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(program.id_, "model");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
    object1.render();

    // create transformations
    glm::mat4 model2 = glm::mat4(1.0f);
    model2 = glm::rotate(model2, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model2 = glm::translate(model2, glm::vec3(5.0f, 1.0f, 3.0f));
    // retrieve the matrix uniform locations
    unsigned int modelLoc2 = glGetUniformLocation(program.id_, "model");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
    object2.render();

    // create transformations
    glm::mat4 model3 = glm::mat4(1.0f);
    model3 = glm::translate(model3, glm::vec3(0.0, -50.0, 0.0));
    model3 = glm::scale(model3, glm::vec3(100.0, 100.0, 100.0));
    // retrieve the matrix uniform locations
    unsigned int modelLoc3 = glGetUniformLocation(program.id_, "model");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc3, 1, GL_FALSE, glm::value_ptr(model3));
    object3.render();
}

int main()
{
    std::cout << "Launching Shadow Map Program" << std::endl;

    const unsigned int width = 800;
    const unsigned int height = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Shadow Mapping Example", NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (window == NULL)
    {
        std::cerr << "Couldn't create the Window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit())
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Shader type 0 == VERTEX, type 1 == FRAGMENT
    Shader vertex_shader = Shader("../src/shaders/renderer/vertex.glsl", 0);
    Shader fragment_shader = Shader("../src/shaders/renderer/fragment.glsl", 1);
    Program program = Program(vertex_shader, fragment_shader);

    Shader shadow_vertex = Shader("../src/shaders/shadows/vertex.glsl", 0);
    Shader shadow_fragment = Shader("../src/shaders/shadows/fragment.glsl", 1);
    Program shadow_program = Program(shadow_vertex, shadow_fragment);

    Shader debug_vertex = Shader("../src/shaders/quad_debug/vertex_quad.glsl", 0);
    Shader debug_fragment = Shader("../src/shaders/quad_debug/fragment_quad.glsl", 1);
    Program debug_program = Program(debug_vertex, debug_fragment);

    float vertices[] = {
            // positions          // colors
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,// top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 1.0f,// bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,// bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    float vertices_normal_blue[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f, 1.0f
    };

    float vertices_normal_red[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,01.0f, 0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f, 0.0f
    };

    float vertices_normal_yellow[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,0.0f, 1.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f, 1.0f
    };

    Object object1 = Object(vertices_normal_blue, 9*6*6);
    Object object2 = Object(vertices_normal_red, 9*6*6);
    Object object3 = Object(vertices_normal_yellow, 9*6*6);

    // configure depth map FBO
    // -----------------------
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // shader configuration
    // --------------------
    program.use();
    glUniform1i(glGetUniformLocation(program.id_, "shadowMap"), 1);

    debug_program.use();
    glUniform1i(glGetUniformLocation(program.id_, "depthMap"), 0);

    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Inputs
        processInputs(window);
        glfwSetCursorPosCallback(window, mouse_callback);

        // Clearning
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        // FIRST RENDERING FOR LIGHT DEPTH
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view
        shadow_program.use();
        glUniformMatrix4fv(glGetUniformLocation(shadow_program.id_, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        // DRAWING
        drawing(shadow_program, object1, object2, object3);
        // End of Drawing
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // NORMAL RENDERING WITH THE USE OF DEPTHMAPFBO
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        program.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view  = camera.get_view();
        unsigned int viewLoc  = glGetUniformLocation(program.id_, "view");
        unsigned int projectionLoc  = glGetUniformLocation(program.id_, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        // set light uniforms
        glUniform3f(glGetUniformLocation(program.id_, "viewPos"), camera.position_.x, camera.position_.y, camera.position_.z);
        glUniform3f(glGetUniformLocation(program.id_, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniformMatrix4fv(glGetUniformLocation(program.id_, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        drawing(program, object1, object2, object3);


        // OPTIONNAL DRAWING FOR DEBUG
        debug_program.use();
        glUniform1f(glGetUniformLocation(program.id_, "near_plane"), near_plane);
        glUniform1f(glGetUniformLocation(program.id_, "far_plane"), far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        // drawing(debug_program, object1, object2, object3);
        // renderQuad();

        // glfw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}