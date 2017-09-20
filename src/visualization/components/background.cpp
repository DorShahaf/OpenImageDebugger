/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2017 GDB ImageWatch contributors
 * (github.com/csantosbh/gdb-imagewatch/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <GL/glew.h>

#include "background.h"

#include "math/linear_algebra.h"
#include "visualization/game_object.h"
#include "visualization/shader.h"
#include "visualization/shaders/giw_shaders.h"
#include "visualization/stage.h"


Background::~Background()
{
    glDeleteBuffers(1, &background_vbo);
}


bool Background::initialize()
{
    background_prog.create(shader::background_vert_shader,
                           shader::background_frag_shader,
                           ShaderProgram::FormatR,
                           "rgba",
                           {});

    // Generate square VBO
    // clang-format off
    static const GLfloat vertex_buffer_data[] = {
        -1, -1,
         1, -1,
         1,  1,
         1,  1,
        -1,  1,
        -1, -1,
    };
    // clang-format on
    glGenBuffers(1, &background_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, background_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertex_buffer_data),
                 vertex_buffer_data,
                 GL_STATIC_DRAW);

    return true;
}


void Background::draw(const mat4&, const mat4&)
{
    background_prog.use();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, background_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


int Background::render_index() const
{
    return -100;
}
