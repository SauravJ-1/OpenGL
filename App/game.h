#pragma once

#include "application.h"

#include <vector>

namespace GAE {

    constexpr size_t NumVertices = 6;

    class Game final : public Application {
        enum VAO_IDs { Triangles, NumVAOs };
        enum Buffer_IDs { ArrayBuffer, NumBuffers };
        enum Attrib_IDs { vPosition = 0 };

        GLuint VAOs[NumVAOs];
        GLuint Buffers[NumBuffers];

    public:
        Game(char const* title = nullptr);

        void draw() const override;
    private:
        void key_callback() const;
        void init_data();
    };

} // namespace GAE
