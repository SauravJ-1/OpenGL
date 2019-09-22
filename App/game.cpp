#include "game.h"

GAE::Game::Game(char const* title)
    : Application(title)
{
    init_data();
    key_callback();
}

void GAE::Game::draw() const
{
    static const float black[] {
        .0f, .0f, .0f, .0f,
    };

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void GAE::Game::key_callback() const
{
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int, int action, int) {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_ESCAPE){
                glfwSetWindowShouldClose(window, true);
            }

            if (key == GLFW_KEY_M) {
                static GLenum mode = GL_FILL;
                mode = (mode == GL_FILL) ? GL_LINE : GL_FILL;
                glPolygonMode(GL_FRONT_AND_BACK, mode);
            }
        }
    });
}

void GAE::Game::init_data()
{
    static GLfloat const vertices[NumVertices][2] {
        { -.9f , -.9f , },
        {  .85f, -.9f , },
        { -.9f ,  .85f, },
        {  .9f , -.85f, },
        {  .9f ,  .9f , },
        { -.85f,  .9f , },
    };

    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);


    add_shader({GL_FRAGMENT_SHADER, "../shaders/triangles.frag"});
    add_shader({GL_VERTEX_SHADER, "../shaders/triangles.vert"});

    glUseProgram(get_program());

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPosition);
}
