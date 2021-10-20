#include "light.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    // if(debug_pixel){
    // std::cout << "cast ray: end = " << ray.endpoint << std::endl;
    // std::cout << "dir = " << ray.direction << std::endl;
    // }
    // L = kd I max(0, n · l)
    // not using c = c_l * max(0, e · r)^p
    // not using r = −l + 2(l · n)n,



    vec3 color_a = color_ambient * (world.ambient_color * world.ambient_intensity);    //c_a = k_a * (I_a)
    vec3 color_d(0,0,0);
    vec3 color_s(0,0,0);
    vec3 color(0,0,0);
    // vec3 color = color_a;

    vec3 intensity;
    Ray s_ray;
    for(unsigned i = 0; i < world.lights.size(); ++i){      //calculates diffuse and spectral component
        
        vec3 l = (world.lights.at(i)->position - intersection_point);
        vec3 l_norm = l.normalized();
        vec3 r = (2* dot(l_norm,normal) * normal - l_norm).normalized();

        intensity = world.lights.at(i)->Emitted_Light(world.lights.at(i)->position - intersection_point);
        // vec3 v = (world.camera.position - intersection_point).normalized();
        // vec3 h = (v + l)/((v + l).normalized());

        s_ray.endpoint = intersection_point;
        s_ray.direction = l_norm;
        Hit intersect = world.Closest_Intersection(s_ray);
        if (!world.enable_shadows || (intersect.dist >= l.magnitude() && world.enable_shadows)){    //decides whether we use the diffuse + specular or not
            color_d +=  color_diffuse * intensity * std::max(dot(normal.normalized(),l_norm),0.0);
            color_s += color_specular * intensity * pow(std::max(dot(-1.0 * ray.direction,r),0.0), specular_power);
        }

    }
    color = color_a + color_d + color_s;
    return color;
}
