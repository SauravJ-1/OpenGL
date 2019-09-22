 #include "application.h"

#include <fstream>
#include <string>
#include <sstream>

#include <cassert>

GAE::Application::Application(char const* title)
{
    init(title);
}

GAE::Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GAE::Application::draw() const
{
    static const float black[] {
        .0f, .0f, .0f, .0f,
    };

    glClearBufferfv(GL_COLOR, 0, black);
}

void GAE::Application::run()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        draw();

        glfwSwapBuffers(window);
    }
}

void GAE::Application::add_shader(const GAE::Application::Shader &shader)
{
    shaders.push_back(std::move(shader));
}

GLuint GAE::Application::get_program()
{
    auto load = [](Shader const& _shader){
        GLuint shader = glCreateShader(_shader.shader_type);

        std::ifstream inFile(_shader.filename);
        std::stringstream buffer;

        buffer << inFile.rdbuf();
        std::string tmp = buffer.str();

        GLchar const* shader_src = tmp.c_str();
        glShaderSource(shader, 1, &shader_src, nullptr);

        return shader;
    };

    GLuint shader_program = glCreateProgram();

    for (size_t i = 0; i < shaders.size(); ++i) {
        auto shader_id = load(shaders[i]);
        glCompileShader(shader_id);

        GLint success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        assert(success);

        glAttachShader(shader_program, shader_id);
        glDeleteShader(shader_id);
    }

    GLint success;
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    assert(success);

    return shader_program;
}

void GAE::Application::init(char const* title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, title ? title : "App", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
