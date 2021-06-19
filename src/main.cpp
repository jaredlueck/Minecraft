// include glad before glfw
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include "Model.h"
#include "Shader.h"
#include "LightSource.h"

void CheckGLError();
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void window_size_callback(GLFWwindow* window, int width, int height);

int SCR_WIDTH;
int SCR_HEIGHT;

bool mouseDown = false;
double initX = 0.0f;
double initY = 0.0f;

double deltaX = 0.0f;
double deltaY = 0.0f;

double rotationSpeed = 0.01;

glm::mat4 projection;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);

    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
  
    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    
    glEnable(GL_DEPTH_TEST);  

    Shader shader("./shaders/vertex.vs", "./shaders/fragment.fs");

    shader.Bind();

    Model model("./models/backpack.obj");
    
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_HEIGHT/(float)SCR_WIDTH, 0.1f, 200.0f);

    glm::mat4 lookat = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    glm::mat4 mvp;

    shader.setMat4("view", lookat);

    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 modelMat = glm::mat4(1.0f);

    struct LightSource 
    {
        glm::vec3 position;

        float constant;
        float linear;
        float quadratic;
    };

    LightSource l1;

    l1.position = glm::vec3(1.0f, 0.0f, 0.0f);

    l1.constant = 1.0f;
    l1.linear = 0.1f;
    l1.quadratic = 0.1f;

    LightSource lights[] = {l1};
    
    unsigned int ubo;
    glGenBuffers(1, &ubo);
    
    int lightIndex = glGetUniformBlockIndex(shader.ID, "Light");
    glUniformBlockBinding(shader.ID, lightIndex, 0);
    CheckGLError();

    if(lightIndex == GL_INVALID_INDEX)
    {
        std::cout << "Failed to get location of uniform buffer" << std::endl;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(lights),  &lights[0], GL_STATIC_DRAW);
    CheckGLError();
    
    // glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo); 

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

        if(mouseDown)
        {
            modelMat = glm::rotate(modelMat, glm::radians((float)deltaX * 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            modelMat = glm::rotate(modelMat, glm::radians((float)deltaY * 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        
        shader.setMat4("model", modelMat);
        shader.setMat4("projection", projection);
        model.Draw(shader);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(mouseDown)
    {
        deltaX = (xpos - initX)/SCR_WIDTH;
        deltaY = (ypos - initY)/SCR_HEIGHT;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &initX, &initY);
        mouseDown = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mouseDown = false;
        
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_HEIGHT = height;
    SCR_WIDTH = width;

    glViewport(0, 0, width, height);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 200.0f);
}

const char * GetGLErrorStr(GLenum err)
{
    switch (err)
    {
    case GL_NO_ERROR:          return "No error";
    case GL_INVALID_ENUM:      return "Invalid enum";
    case GL_INVALID_VALUE:     return "Invalid value";
    case GL_INVALID_OPERATION: return "Invalid operation";
    case GL_STACK_OVERFLOW:    return "Stack overflow";
    case GL_STACK_UNDERFLOW:   return "Stack underflow";
    case GL_OUT_OF_MEMORY:     return "Out of memory";
    default:                   return "Unknown error";
    }
}

void CheckGLError()
{
    while (true)
    {
        const GLenum err = glGetError();
        if (GL_NO_ERROR == err)
            break;

        std::cout << "GL Error: " << GetGLErrorStr(err) << std::endl;
    }
}


