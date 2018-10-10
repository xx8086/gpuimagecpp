#include "material.h"

namespace lh_gl {
    material::material()
    {
    }


    material::~material()
    {
    }

    void material::set_light_pos(vec3 light_pos) {
        _light_pos = light_pos;
    }

    void material::update_material(CShader* lightshader,  const vec3& viewpos) {
        lightshader->use();
        lightshader->setvec3("view_pos", viewpos);

        vec3 diffuseColor = vec3(0.5f); // decrease the influence
        vec3 ambientColor = diffuseColor * vec3(0.2f); // low influence

        lightshader->setvec3("light.position", _light_pos);
        lightshader->setvec3("light.ambient", ambientColor);
        lightshader->setvec3("light.diffuse", diffuseColor);
        lightshader->setvec3("light.specular", vec3(1.0f));

        lightshader->setvec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightshader->setvec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightshader->setvec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        lightshader->setfloat("material.shininess", 32.0f);
    }
}
