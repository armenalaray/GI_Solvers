#include "quad.h"

// NOTE(Alex): XY (0,0) (5,5) Z = 0
Color<int> Quad_XY_Z0::get_color(float u, float v)
{
    
#if 0    
    float tx = u;
    float ty = v;
    
    Vec3<float> c0 = c[0];
    Vec3<float> c1 = c[1];
    Vec3<float> c2 = c[2];
    Vec3<float> c3 = c[3];
    
    Vec3<float> a = Lerp(c0,c1, tx);
    Vec3<float> b = Lerp(c2,c3, tx);
    Vec3<float> d = Lerp(a,b,ty);
    
    int ir = int(255.99 * d.r);
    int ig = int(255.99 * d.g);
    int ib = int(255.99 * d.b);
    
    return {ir,ig,ib};
#endif
    return {};
}


// NOTE(Alex): YZ (0,0) (5,5) X = 0
Color<int> Quad_YZ_X0::get_color(float u, float v)
{
    
#if 0    
    float tx = 1.0f - u;
    float ty = v;
    
    // NOTE(Alex): In this way the parameterization u,v is CORRECT!!!
    Vec3<float> c0 = c[1];
    Vec3<float> c1 = c[0];
    Vec3<float> c2 = c[3];
    Vec3<float> c3 = c[2];
    
    Vec3<float> a = Lerp(c0,c1, tx);
    Vec3<float> b = Lerp(c2,c3, tx);
    Vec3<float> d = Lerp(a,b,ty);
    
    int ir = int(255.99 * d.r);
    int ig = int(255.99 * d.g);
    int ib = int(255.99 * d.b);
    return {ir,ig,ib};
#endif
    return {};
}


// NOTE(Alex): XZ (0,0) (5,5) Y = 0
Color<int> Quad_XZ_Y0::get_color(float u, float v)
{
#if 0    
    float tx = 1.0f - u;
    float ty = 1.0f - v;
    
    // NOTE(Alex): In this way the parameterization u,v is CORRECT!!!
    Vec3<float> c0 = c[3];
    Vec3<float> c1 = c[1];
    Vec3<float> c2 = c[2];
    Vec3<float> c3 = c[0];
    
    Vec3<float> a = Lerp(c0,c1, tx);
    Vec3<float> b = Lerp(c2,c3, tx);
    Vec3<float> d = Lerp(a,b,ty);
    
    int ir = int(255.99 * d.r);
    int ig = int(255.99 * d.g);
    int ib = int(255.99 * d.b);
    return {ir,ig,ib};
#endif
    return {};
}

// NOTE(Alex): YZ (0,0) (5,5) X = 5.0f
Color<int> Quad_YZ_X5::get_color(float u, float v)
{
    
#if 0    
    float tx = u;
    float ty = v;
    
    // NOTE(Alex): In this way the parameterization u,v is CORRECT!!!
    Vec3<float> c0 = c[0];
    Vec3<float> c1 = c[1];
    Vec3<float> c2 = c[2];
    Vec3<float> c3 = c[3];
    
    Vec3<float> a = Lerp(c0,c1, tx);
    Vec3<float> b = Lerp(c2,c3, tx);
    Vec3<float> d = Lerp(a,b,ty);
    
    int ir = int(255.99 * d.r);
    int ig = int(255.99 * d.g);
    int ib = int(255.99 * d.b);
    return {ir,ig,ib};
#endif
    return {};
}

// NOTE(Alex): XZ (0,0) (5,5) Y = 5.0f
Color<int> Quad_XZ_Y5::get_color(float u, float v)
{
    
#if 0    
    float tx = u;
    float ty = 1.0f - v;
    
    // NOTE(Alex): In this way the parameterization u,v is CORRECT!!!
    Vec3<float> c0 = c[1];
    Vec3<float> c1 = c[3];
    Vec3<float> c2 = c[0];
    Vec3<float> c3 = c[2];
    
    Vec3<float> a = Lerp(c0,c1, tx);
    Vec3<float> b = Lerp(c2,c3, tx);
    Vec3<float> d = Lerp(a,b,ty);
    
    int ir = int(255.99 * d.r);
    int ig = int(255.99 * d.g);
    int ib = int(255.99 * d.b);
    return {ir,ig,ib};
#endif
    return {};
}

bool Quad_XY_Z0::hit(Ray & r, float tMin, float tMax, HitRec & HitRecord){
    float t = (k - r.get_origin().z) / r.get_direction().z;
	
	if(t < tMin || t > tMax) return false;
	
	float x = r.get_origin().x + t * r.get_direction().x;
	float y = r.get_origin().y + t * r.get_direction().y;
	
	if(x < x0 || x > x1 || y < y0 || y > y1) return false;
	
    HitRecord.t = t;
    HitRecord.u = ((x - x0) / (x1 - x0));
	HitRecord.v = ((y - y0) / (y1 - y0));
    
	return true;
}


bool Quad_YZ_X0::hit(Ray & r, float tMin, float tMax, HitRec & HitRecord){
    float t = (k - r.get_origin().x) / r.get_direction().x;
	
	if(t < tMin || t > tMax) return false;
	
	float y = r.get_origin().y + t * r.get_direction().y;
	float z = r.get_origin().z + t * r.get_direction().z;
	
	if(y < y0 || y > y1 || z < z0 || z > z1) return false;
	
	HitRecord.t = t;
	HitRecord.u = ((z - z0) / (z1 - z0));
    HitRecord.v = ((y - y0) / (y1 - y0));
    return true;
}


bool Quad_XZ_Y0::hit(Ray & r, float tMin, float tMax, HitRec & HitRecord){
    float t = (k - r.get_origin().y) / r.get_direction().y;
	
	if(t < tMin || t > tMax) return false;
	
	float x = r.get_origin().x + t * r.get_direction().x;
	float z = r.get_origin().z + t * r.get_direction().z;
	
	if(x < x0 || x > x1 || z < z0 || z > z1) return false;
    
	HitRecord.t = t;
	HitRecord.u = ((z - z0) / (z1 - z0));
    HitRecord.v = ((x - x0) / (x1 - x0));
    return true;
}


bool Quad_YZ_X5::hit(Ray & r, float tMin, float tMax, HitRec & HitRecord){
    float t = (k - r.get_origin().x) / r.get_direction().x;
	
	if(t < tMin || t > tMax) return false;
	
	float y = r.get_origin().y + t * r.get_direction().y;
	float z = r.get_origin().z + t * r.get_direction().z;
	
	if(y < y0 || y > y1 || z < z0 || z > z1) return false;
	
	HitRecord.t = t;
	HitRecord.u = ((z - z0) / (z1 - z0));
    HitRecord.v = ((y - y0) / (y1 - y0));
    return true;
}


bool Quad_XZ_Y5::hit(Ray & r, float tMin, float tMax, HitRec & HitRecord){
    float t = (k - r.get_origin().y) / r.get_direction().y;
	
	if(t < tMin || t > tMax) return false;
	
	float x = r.get_origin().x + t * r.get_direction().x;
	float z = r.get_origin().z + t * r.get_direction().z;
	
	if(x < x0 || x > x1 || z < z0 || z > z1) return false;
    
	HitRecord.t = t;
	HitRecord.u = ((z - z0) / (z1 - z0));
    HitRecord.v = ((x - x0) / (x1 - x0));
    return true;
}
