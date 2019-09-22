#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>

namespace GAE {

    class Application {
    public:
        struct Shader {
            GLenum shader_type;
            char const* filename;
        };

    public:
        Application(char const* title);
        virtual ~Application();

        virtual void draw() const;

        Application(Application const &) = delete;
        Application& operator=(Application const&) = delete;

        void run();

        void add_shader(const Shader&);
        GLuint get_program();

    private:
        void init(char const* title);

    protected:
        GLFWwindow *window;
        std::vector<Shader> shaders;
    };

} // namespace GAE
