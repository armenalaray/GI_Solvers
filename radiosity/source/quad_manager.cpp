#include "quad_manager.h"

Quad_manager::Quad_manager(float fw_, int hps_):
fw{fw_},
hps{hps_},
ei{0},
quads{},
f_xy_z0{fw,hps,ei,quads},
f_yz_x0{fw,hps,ei,quads},
f_xz_y0{fw,hps,ei,quads},
f_yz_x5{fw,hps,ei,quads},
f_xz_y5{fw,hps,ei,quads},
e{fw,hps,ei,quads}
{
}

Color<int> Quad_manager::get_color(Ray r, float tMin, float tMax){
    HitRec rec{};
    std::shared_ptr<Quad> a_ref{};
    for(auto a:quads)
    {
        if(a->hit(r, tMin, tMax, rec))
        {
            tMax = rec.t;
            a_ref=a;
        }
    }
    if(a_ref.get()) return a_ref->get_color(rec.u,rec.v);
    else return {0,0,0};
}

Matrix<float,2> Quad_manager::calc_ff(){
    
    Matrix<float,2> ff(quads.size(),quads.size());
    for(auto a:quads){
        Ray r{};
        while(a->get_ray(r))
        {
            Element_ref j{};
            if(request_element(r, 0.001f, FLT_MAX, j))
                a->calc_ff(r, j, ff);
        }
    }
    return ff;
}

bool Quad_manager::request_element(Ray r, float tMin, float tMax, Element_ref& element){
    HitRec rec{};
    std::shared_ptr<Quad> a_ref{};
    for(auto a:quads){
        if(a->hit(r, tMin, tMax, rec))
        {
            tMax = rec.t;
            a_ref = a;
        }
    }
    // NOTE(Alex): Slicing
    if(a_ref.get()){element = *a_ref; return true;}
    else return false;
}

void Quad_manager::move_radiosities(const Matrix<float,1>& r,const Matrix<float,1>& g,const Matrix<float,1>& b){
    f_xy_z0.add_radiosities(r,g,b);
    f_yz_x0.add_radiosities(r,g,b);
    f_xz_y0.add_radiosities(r,g,b);
    f_yz_x5.add_radiosities(r,g,b);
    f_xz_y5.add_radiosities(r,g,b);
    e.add_radiosities(r,g,b);
    
    std::string f_xy_z0_s = "f_xy_z0.ppm";
    std::string f_yz_x0_s = "f_yz_x0.ppm";
    std::string f_xz_y0_s = "f_xz_y0.ppm";
    std::string f_yz_x5_s = "f_yz_x5.ppm";
    std::string f_xz_y5_s = "f_xz_y5.ppm";
    std::string f_e = "f_e.ppm";
    f_xy_z0.debug_print(f_xy_z0_s);
    f_yz_x0.debug_print(f_yz_x0_s);
    f_xz_y0.debug_print(f_xz_y0_s);
    f_yz_x5.debug_print(f_yz_x5_s);
    f_xz_y5.debug_print(f_xz_y5_s);
    e.debug_print(f_e);
}