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
    vec3 color(0,0,0);
    vec3 color_d(0,0,0);                //diffuse component of color
    
    

   
    vec3 intensity;
    for(unsigned i = 0; i < world.lights.size(); ++i){
        intensity = world.lights.at(i)->Emitted_Light(world.lights.at(i)->position - intersection_point);
        vec3 l = (world.lights.at(i)->position - intersection_point).normalized();
        if(dot(normal,l) >= 0)
            color_d +=  color_diffuse * intensity * dot(normal,l);
        
        // if(debug_pixel)
        //     std::cout << "diffuse = " << color_d << std::endl;

    }
    color = color_d;
    Hit closest = world.Closest_Intersection(ray);
    // int j = -1;
    // for (unsigned i = 0; i <= world.objects.size(); ++i){ // debugging, ignore
    //     if (i == world.objects.size()){
    //         break;
    //     }
    //     if(world.objects.at(i) == closest.object){
    //         j = i; 
    //         break;
    //     }  

    // if(debug_pixel){
    // std::cout << "intersection with obj[" <<  j << "] part = "<< closest.part << " dist = " << closest.dist << std::endl;
    // std::cout << "call Shade_Surface with: location = " << intersection_point << "; normal = " << normal << std::endl;

    
    return color;
}
