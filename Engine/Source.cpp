#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"sources/shader.hpp"


//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.6f, -0.6f, 0.0f,
     0.6f, -0.6f, 0.0f,
     0.0f,  0.6f, 0.0f,
     0.0f,  0.6f, 0.0f,
    -0.8f,  0.9f, 0.0f,
     0.8f,  0.9f, 0.0f
};

//OpenGL nesnelerinin id de�erlerini tutacak olan de�i�kenler

unsigned int VBO;
unsigned int VAO;

int main(int argc, char** argv)
{
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "�Lk Program�m", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Pencere Olusturulamadi" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ShaderProgram program;

    program.attachShader("C:/Users/ASUS/Desktop/GameEngine/Projects/GameEngine/Engine/vertex.shader", GL_VERTEX_SHADER);
    program.attachShader("C:/Users/ASUS/Desktop/GameEngine/Projects/GameEngine/Engine/fragment.shader", GL_FRAGMENT_SHADER);
    program.link();
    //vertex array object olu�turuluyor
    glGenVertexArrays(1, &VAO);
    //vertex buffer object olu�uruluyor
    glGenBuffers(1, &VBO);

    //vertex array object aktif edildi.
    glBindVertexArray(VAO);
    //vertex buffer nesnesi aktif edildi.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //vertex buffer'a nokta bilgileri ytollan�yor
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //g�nderilen vertex'e ait �zellikler etiketleniyor
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //�zellik  etiket i aktif ediliyor.
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        //olu�turulacak resim ba�lang�� rengine boyan�yor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //�izimde kullan�lacak olan program nesnesi aktif ediliyor
        program.use();

        //�izimde kullan�lacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //�izim komutu g�nderiliyor
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}