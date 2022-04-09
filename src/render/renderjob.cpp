
#include <eloimx/render/renderjob.h>
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif 
ELX_NAMESPACE_BEGIN
void elxRenderJob::writeTga() const {
    stbi_write_tga(imageName.c_str(), width, height, 3, color);
}

ELX_NAMESPACE_END