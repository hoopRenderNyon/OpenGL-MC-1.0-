#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"layout (location = 3) in vec3 aOffset;\n"
"layout (location = 4) in float aBlockType;\n"
"out vec2 TexCoord;\n"
"out vec3 ourColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   float uOffset = 0.0;\n"
"   float vOffset = 0.0;\n"
"   float uScale = 1.0 / 3.0;\n"
"   int id = int(aBlockType);\n"
"   \n"
"   if (id <= 1) { uScale = 1.0; uOffset = 0.0; vOffset = 0.0; }\n"
"   else if (id == 2) { uOffset = 0.2; vOffset = 0.0; }\n"
"   else if (id == 3) { uOffset = 0.3; vOffset = 0.0; }\n"
"   else if (id == 4) { uOffset = 0.4; vOffset = 0.0; }\n"
"   else if (id == 5) { uOffset = 0.5; vOffset = 0.0; }\n"
"   else if (id == 6) { uOffset = 0.6; vOffset = 0.0; }\n"
"   else if (id == 7) { uScale = 2.0 / 3.0; uOffset = 0.7; vOffset = 0.0; }\n"
"   else if (id == 8) { uOffset = 0.9; vOffset = 0.0; }\n"
"   else if (id == 9) { uOffset = 0.0; vOffset = 0.1; }\n"
"   else if (id == 10) { uOffset = 0.1; vOffset = 0.1; }\n"
"   else { uOffset = 0.2; vOffset = 0.1; }\n"
"   \n"
"   if (id == 7) { TexCoord = vec2(0.9 - (aTexCoord.x * uScale), aTexCoord.y + vOffset); }\n"
"   else { TexCoord = vec2(aTexCoord.x * uScale + uOffset, aTexCoord.y + vOffset); }\n"
"   vec3 finalPos = aPos + aOffset;\n"
"   gl_Position = projection * view * model * vec4(finalPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
"   FragColor = texture(ourTexture, TexCoord);\n"
"}\0";

const int WindowWidth = 800, WindowHeight = 800;
float grass_block_vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.2f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.3f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.3f, 0.1f,
     0.5f, -0.5f,  0.5f,  0.3f, 0.1f,
    -0.5f, -0.5f,  0.5f,  0.2f, 0.1f,
    -0.5f, -0.5f, -0.5f,  0.2f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.1f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.1f, 0.1f,
     0.5f,  0.5f,  0.5f,  0.1f, 0.1f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.1f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.1f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.2f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.2f, 0.1f,
     0.5f,  0.5f, -0.5f,  0.2f, 0.1f,
    -0.5f,  0.5f, -0.5f,  0.1f, 0.1f,
    -0.5f, -0.5f, -0.5f,  0.1f, 0.0f,

     0.5f, -0.5f,  0.5f,  0.1f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.2f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.2f, 0.1f,
    -0.5f,  0.5f,  0.5f,  0.2f, 0.1f,
     0.5f,  0.5f,  0.5f,  0.1f, 0.1f,
     0.5f, -0.5f,  0.5f,  0.1f, 0.0f,

     -0.5f, -0.5f,  0.5f,  0.1f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.2f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.2f, 0.1f,
     -0.5f,  0.5f, -0.5f,  0.2f, 0.1f,
     -0.5f,  0.5f,  0.5f,  0.1f, 0.1f,
     -0.5f, -0.5f,  0.5f,  0.1f, 0.0f,

      0.5f, -0.5f, -0.5f,  0.1f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.2f, 0.0f,
      0.5f,  0.5f,  0.5f,  0.2f, 0.1f,
      0.5f,  0.5f,  0.5f,  0.2f, 0.1f,
      0.5f,  0.5f, -0.5f,  0.1f, 0.1f,
      0.5f, -0.5f, -0.5f,  0.1f, 0.0f
};

glm::vec3 cubePositions[8192] = {};
short cubeState[8192] = {0};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.75f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 300, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;

short slot = 0;
short selectedBlockType[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int itemCount[10] = {0};
int currentBlockType = 1;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

unsigned int shaderProgram;
unsigned int instanceVBO;
unsigned int stateVBO;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Minecraft on OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false); 
    unsigned char* data = stbi_load("blocks_texture.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    for (int y = 0; y < 32; y++) {
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    int index = y * 256 + z * 16 + x;
                    if (y == 16) {
                        cubeState[index] = 1;
                    }else if (y < 8) {
                        cubeState[index] = 3;
					}
					else if (y < 16) {
						cubeState[index] = 2;
                    }
                    else {
						cubeState[index] = 0;
                    }
                    if (cubeState[index] == 0) {
                        cubePositions[index] = glm::vec3(0.0f, -1000.0f, 0.0f); // 扔到地底下看不见
                    }
                    else {
                        cubePositions[index] = glm::vec3((float)x + 0.5f, (float)y + 0.5f, (float)z + 0.5f);
                    }
                    std::cout << index << std::endl;
                    std::cout << (float)x << "," << (float)z << std::endl;
                }
            }
        }

    
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);

    
    glGenBuffers(1, &stateVBO);
    glBindBuffer(GL_ARRAY_BUFFER, stateVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeState), cubeState, GL_STATIC_DRAW);

    

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, stateVBO);
    glVertexAttribPointer(4, 1, GL_SHORT, GL_FALSE, sizeof(short), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grass_block_vertices), grass_block_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);
    
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        mouse_callback(window, lastX, lastY);

        //glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 0.0f * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glClearColor(0.7f, 0.85f, 0.95f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 8192);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    float cameraSpeed = 7.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    for (int key = GLFW_KEY_0; key <= GLFW_KEY_9; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            slot = (short)(key - GLFW_KEY_0); 
        }
    }
    currentBlockType = selectedBlockType[slot];
    //if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    //    cameraSpeed = 90.0f * deltaTime;
    //} else {
    //    cameraSpeed = 2.5f * deltaTime;
    //}
}

int getBlockIndex(glm::vec3 pos) {
    int x = (int)std::floor(pos.x);
    int y = (int)std::floor(pos.y);
    int z = (int)std::floor(pos.z);
    if (x >= 0 && x < 16 && y >= 0 && y < 32 && z >= 0 && z < 16) {
        return y * 256 + z * 16 + x;
    }
    return -1;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        for (float t = 0.0f; t < 10.0f; t += 0.05f){
            glm::vec3 samplePos = cameraPos + cameraFront * t;
            int idx = getBlockIndex(samplePos);

            if (idx != -1 && cubeState[idx] != 0){
                cubeState[idx] = 0;
                cubePositions[idx] = glm::vec3(0.0f, -1000.0f, 0.0f);
                glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubePositions), cubePositions);
                glBindBuffer(GL_ARRAY_BUFFER, stateVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeState), cubeState);
                std::cout <<  idx << " is break: " <<std::endl;
                break; 
            }
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        for (float t = 0.0f; t < 10.0f; t += 0.01f)
        {
            glm::vec3 samplePos = cameraPos + cameraFront * t;
            int idx = getBlockIndex(samplePos);

            if (idx != -1 && cubeState[idx] != 0) {
                glm::vec3 prevPos = cameraPos + cameraFront * (t - 0.01f);
                int prevIdx = getBlockIndex(prevPos);

                if (prevIdx != -1 && cubeState[prevIdx] == 0){
                    cubeState[prevIdx] = currentBlockType;
                    int px = prevIdx % 16;
                    int py = prevIdx / 256;
                    int pz = (prevIdx % 256) / 16;
                    cubePositions[prevIdx] = glm::vec3((float)px + 0.5f, (float)py + 0.5f, (float)pz + 0.5f);

                    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubePositions), cubePositions);
                    glBindBuffer(GL_ARRAY_BUFFER, stateVBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeState), cubeState);
                    break;
                }
            }
        }
    }
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);


}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}