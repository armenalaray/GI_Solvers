#include "canvas.h"

void Canvas::set_base()
{
    
}

Canvas::Canvas(const Vec3<float>& X_, const Vec3<float>& Y_, const Vec3<float>& O_, const int th, const int tw, const float cg_): 
X{X_}, 
Y{Y_},
Origin{O_},
cg{cg_}, 
ShiftX{cg * 0.5f * X},
ShiftY{cg * 0.5f * Y},
tx{tw}, 
ty{th}, 
// TODO(Alex): Do we want this hardcoded???
wx{5.0f},
wy{5.0f},
px{0}, 
py{th - 1}
{}

bool Canvas::open_ppm_file(std::string file_s)
{
    std::ofstream FFMatrix;
    FFMatrix.open(file_s, std::ios::trunc | std::ios::out);
    if(FFMatrix.is_open()){
        FFMatrix << "P3\n" << tx << " " << ty << "\n255\n";
        return true;
    }
    return false;
}

bool Canvas::not_finished_writing()
{
    if(py < 0) return false;
    if(px >= tx) {px = 0; --py;}
    ++px;
    return true;
}

Vec3<float> Canvas::get_p_sample()
{
    auto uv = conv_text_to_uv(px,py);
    auto pxy = conv_uv_to_world(uv);
    return std::get<0>(pxy) + std::get<1>(pxy) + Origin + ShiftX + ShiftY;
}

std::pair<float,float> Canvas::conv_text_to_uv(int u, int v)
{
    return 
    {
        (static_cast<float>(u) / static_cast<float>(tx)), 
        (static_cast<float>(v) / static_cast<float>(ty)), 
    };
}

std::pair<Vec3<float>,Vec3<float>> Canvas::conv_uv_to_world(std::pair<float,float> p)
{
    return 
    {
        (std::get<0>(p) * (wx - cg)) * X,
        (std::get<1>(p) * (wy - cg)) * Y,
    };
}

void Canvas::write_color(Color<int>& c)
{
    
}

void Canvas::close_ppm_file(){
    
}