#include "mesh.h"
#include "plane.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    // TODO;
    double dist = -1;
    double max_dist = std::numeric_limits<double>::max();
    double curr_dist = max_dist;
    int min_part = part;
    if(part < 0){   //loop through all triangles
        for (int i = 0; i < triangles.size(); ++i){
            if(Intersect_Triangle(ray, i, dist)){
                if(dist < curr_dist){
                    curr_dist = dist;
                    min_part = i;
                }
            }
        }
        return {this, curr_dist, min_part};
    }
    else{   // just find intersection of triangle at index part
        if (Intersect_Triangle(ray, part, dist))
            return {this, dist, part};

        return {nullptr, max_dist, part};
    }

}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    // TODO;
    vec3 A = vertices.at(triangles.at(part)[0]);
    vec3 B = vertices.at(triangles.at(part)[1]);
    vec3 C = vertices.at(triangles.at(part)[2]);

    vec3 edge1 = B - A;
    vec3 edge2 = C - A;
    return cross(edge1, edge2).normalized();

}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    // TODO;
    vec3 A = vertices.at(triangles.at(tri)[0]);
    vec3 B = vertices.at(triangles.at(tri)[1]);
    vec3 C = vertices.at(triangles.at(tri)[2]);


    vec3 edge1 = B - A;
    vec3 edge2 = C - A;
    vec3 normal = cross(edge1,edge2).normalized();

    Plane pl = Plane(A, normal);

    Hit intersect = pl.Intersection(ray, tri);

    vec3 Q = ray.endpoint + intersect.dist * ray.direction;

    double normal_area = dot(cross(B - A, C - A), normal);

    double crossBABQ = dot(cross(B - A, Q - A),normal)/normal_area;
    double crossCBQB = dot(cross(C - B, Q - B),normal)/normal_area;
    double crossACQC = dot(cross(A - C, Q - C),normal)/normal_area;
    if(crossBABQ < -weight_tolerance || crossBABQ > (weight_tolerance + 1) 
      || crossCBQB < -weight_tolerance || crossCBQB > (weight_tolerance + 1) 
      || crossACQC < -weight_tolerance || crossACQC > (weight_tolerance + 1))
        return false;
    else{
        dist = intersect.dist;
        return true;
    }

}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
