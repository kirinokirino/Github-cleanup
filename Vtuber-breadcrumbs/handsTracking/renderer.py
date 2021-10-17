import moderngl
import numpy as np
from pyrr import Matrix44


class Renderer:

    def __init__(self, ctx):
        self.program = ctx.program(vertex_shader="""
            #version 330
            uniform mat4 model;
            in vec2 in_vert;
            in vec3 in_color;
            out vec3 color;
            void main() {
                gl_Position = model * vec4(in_vert, 0.0, 1.0);
                color = in_color;
            }
            """,
                                   fragment_shader="""
            #version 330
            in vec3 color;
            out vec4 fragColor;
            void main() {
                fragColor = vec4(color, 1.0);
            }
        """)
        self.update_vertices(ctx)

    def update_vertices(self, ctx, vertices=[
        -0.6, -0.6,
        1.0, 0.0, 0.0,
        0.6, -0.6,
        0.0, 1.0, 0.0,
        0.0, 0.6,
        0.0, 0.0, 1.0,
    ]):
        self.vertices = np.array(vertices, dtype='f4')

        self.vbo = ctx.buffer(self.vertices)
        self.vao = ctx.simple_vertex_array(
            self.program, self.vbo, 'in_vert', 'in_color')
        self.fbo = ctx.framebuffer(
            color_attachments=[ctx.texture((512, 512), 4)])

        self.fbo.use()
        ctx.clear()
        self.program['model'].write(
            Matrix44.from_eulers((0.0, 0.1, 0.0), dtype='f4'))
        self.vao.render(moderngl.TRIANGLES)

    def image(self):
        data = self.fbo.read(components=3)
        img_np = np.frombuffer(data, dtype=np.int8)
        img_np = np.reshape(img_np, newshape=(
            self.fbo.size[0], self.fbo.size[1], 3))
        return img_np
