#pragma once
//#include "..\..\lhgl\lhgl_render\lhgl_sharde_base.h"
#include "shader.hpp"
namespace lh_gl {
    class material
    {
    public:
        material();
        ~material();
    private:
        struct Material {
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
            float shininess;
        };

        struct Light {
            vec3 position;
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };
    public:
        void set_light_pos(vec3);
        void update_material(CShader*,  const vec3&);
    private:
        vec3 _light_pos;
    };
}
