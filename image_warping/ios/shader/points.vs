#version 300 es
precision mediump float;
layout(location = 0) in vec3 position;
uniform mat4 pvw;
void main() {
    gl_Position = pvw * vec4(position.x, -position.y, position.z, 1.0);;
    gl_PointSize = 2.;
}


