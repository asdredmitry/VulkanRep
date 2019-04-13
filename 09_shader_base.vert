#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec3 fragColor;

vec4 positions[6] = vec4[](
    vec4(0.0, 0.9, 100.0, 10.0),
    vec4(-0.9, 0.0, 100.0, 10.0),
    vec4(0.0, -0.9, 100.0, 10.0),
    vec4(0.5, -0.4, 1.0, 1.0),
    vec4(0.5, 0.4, 1.0, 1.0),
    vec4(0.1, 0.0, 1.0, 1.0)
);

vec3 colors[6] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 1.0, 0.0)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex]);
    fragColor = colors[gl_VertexIndex];
}
