#version 300 es
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
uniform mat4 pvw;
out vec2 texture_coord;
void main(){
    texture_coord = aTexCoords;
    gl_Position = pvw * vec4(aPos.x, -aPos.y, aPos.z, 1.0);
}
