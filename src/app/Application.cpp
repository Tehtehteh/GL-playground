#include <iostream>

#include "GL/glew.h"

#include "Application.h"
#include "../SOIL2/SOIL2.h"

#include "GLFW/glfw3.h"
#include "utils/utils.h"

typedef struct {
    GLfloat posCord[3];
    GLfloat textCord[2];
} VertexData ;

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif

#define QEQ_SIZE 100

GLuint vertID = 0;

//VertexData vertices[] = {
//        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//        {{QEQ_SIZE, 0.0f, 0.0f}, {1.0f, 0.0f}},
//        {{QEQ_SIZE, QEQ_SIZE, 0.0f}, {1.0f, 1.0f}},
//        {{0.0f, QEQ_SIZE, 0.0f}, {0.0f, 1.0f}},
////        {{0.0f, 0.0f, QEQ_SIZE}, {0.0f, 1.0f}},
//};


Application::Application(std::string window_title, const int width, const int height, IScriptEngine* e) {
    this->initialized = false;
    this->running = false;
    this->window_title = std::move(window_title);
    this->set_script_engine(e);
    this->set_height(height);
    this->set_width(width);
    if (!glfwInit()) {
        std::cout << "Cannot initialize glfw.";
        return;
    }
#if 0
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->window = glfwCreateWindow(width, height, this->window_title.c_str(), nullptr, nullptr);
    if (this->window == nullptr) {
        std::cout << "Failed to initialize window.";
        glfwTerminate();
        return;
    }
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(this->window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(this->window);
    glewExperimental = GL_TRUE;
    this->initialized = true;
}

void Application::loop() {
    if (!this->initialized) {
        return;
    }
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(this->window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(this->window);
    glewExperimental = GL_TRUE;
    const int glew_init_ret_code = glewInit();
    if (glew_init_ret_code != GLEW_OK) {
        std::cout << "Failed to initialize GLEW lib, error code: " << glew_init_ret_code;
        return;
    }

    glViewport(0, 0, screenWidth, screenHeight);
#if 0
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    GLfloat ww = width;
    GLfloat hh = height;
    gluOrtho2D(0, ww, hh, 0);
    glMatrixMode(GL_MODELVIEW);

    glGenBuffers(1, &vertID);
    glBindBuffer(GL_ARRAY_BUFFER, vertID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(VertexData),
                    (GLvoid *)offsetof(VertexData, posCord));

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData),
            (GLvoid *)offsetof(VertexData, textCord));
#endif
    Shader ourShader("assets/shaders/texture.vs", "assets/shaders/texture.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    int cw, ch, nrChannels;
//    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//    unsigned char *data = SOIL_load_image("assets/characters/me.jpg", &cw, &ch, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cw, ch, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    SOIL_free_image_data(data);
    for (auto& entity: this->entities) {
        entity->load_and_buffer_asset("assets/characters/wall.jpg");
    }

    glfwSetWindowUserPointer(this->window, (void*) (this));
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
//        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for(auto entity: this->entities) {
            entity->render();
        }

        // bind Texture
//        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    this->running = true;
//    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
//    while ( !glfwWindowShouldClose(this->window)) {
//        glClear( GL_COLOR_BUFFER_BIT );
//        glfwWaitEvents();
////        for(auto entity: this->entities) {
////            entity->render();
////        }
//        glfwSwapBuffers(this->window);
//    }
    this->running = false;
}


void Application::update() {

}

Application::~Application() {
    glfwTerminate();
    delete this->script_engine;
}

bool Application::set_window(GLFWwindow *new_window) {
    if (new_window != nullptr) {
        this->window = new_window;
        return true;
    }
    return false;
}

void Application::set_height(int new_height) {
    if (utils::is_uint(new_height)) {
        this->height = new_height;
    }
}

void Application::set_width(int new_width) {
    if (utils::is_uint(new_width)) {
        this->width = new_width;
    }
}

void Application::set_script_engine(IScriptEngine* new_script_engine) {
    this->script_engine = new_script_engine;
}

void Application::add_entity(ICharacter *entity) {
    this->entities.push_back(entity);
}

GLuint Application::load_asset(const ICharacter &character) {
    return 0;
}
