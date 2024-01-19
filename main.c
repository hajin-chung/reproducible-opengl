#include "glad.h"
#include "glfw3.h"

#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

const char *yellowFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
    "}\0";

int main() {
  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    return -1;
  }

  // compile shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int yellowFragmentShader;
  yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
  glCompileShader(yellowFragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  unsigned int yellowShaderProgram;
  yellowShaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glAttachShader(yellowShaderProgram, vertexShader);
  glAttachShader(yellowShaderProgram, yellowFragmentShader);
  glLinkProgram(yellowShaderProgram);

  // triangle vertex data
  float vertices[] = {-0.5, -0.5, 0.0, -0.5, 0.5, 0.0, 0.5, -0.5, 0.0,
                      0.5,  -0.5, 0.0, -0.5, 0.5, 0.0, 0.5, 0.5,  0.5};

  // vertex buffer object: stores large verticies in GPU memory
  unsigned int VBO[2];
  // generate 1 vbo
  glGenBuffers(2, VBO);

  // vertex array object
  unsigned int VAO[2];
  glGenVertexArrays(2, VAO);
  for (int i = 0; i < 2; i++) {
    glBindVertexArray(VAO[i]);

    // bind VBO as GL_ARRAY_BUFFER
    // buffer calls to GL_ARRAY_BUFFER will reference this VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
    // copy data to buffer bound to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float),
                 vertices + 9 * i, GL_STATIC_DRAW);

    // explain data layout to vertex shader
    // vertex shader `layout (location = 0)`, size of `vec3`, data type,
    // data normalization, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
  }

  // render loop
  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(yellowShaderProgram);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(yellowFragmentShader);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
