#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

vec4 positions[6] = vec4[](
    vec4(0.0, 0.9, 0.0, 1.0),
    vec4(-0.9, 0.0, 0.0, 1.0),
    vec4(0.0, -0.9, 0.0, 1.0),
    vec4(0.0, 0.5, 0.8, 1.0),
    vec4(-0.5, 0.0, 0.8, 1.0),
    vec4(0.0, -0.5, 0.8, 1.0)
    /*
    vec4(0.5, -0.4, 1.0, 1.0),
    vec4(0.5, 0.4, 1.0, 1.0),
    vec4(0.1, 0.0, 1.0, 1.0)
    */
);

vec4 colors[6] = vec4[](
    vec4(1.0, 0.0, 0.0, 1.0),
    vec4(1.0, 0.0, 0.0, 1.0),
    vec4(1.0, 0.0, 0.0, 1.0),
    vec4(0.0, 1.0, 0.0, 0.3),
    vec4(0.0, 1.0, 0.0, 0.3),
    vec4(0.0, 1.0, 0.0, 0.3)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex]);
    fragColor = colors[gl_VertexIndex];
}
