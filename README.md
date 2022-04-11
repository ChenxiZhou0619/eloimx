# eloimx
embree3 based renderer
## 2022.3.13
Finish the basic pathTracer, supports 
-   Shape : Triangle、Rectangle and sphere
-   Integrators : path (russian roulette has not been finished yet)
-   bsdf : diffuse only
![image](../project_PathTracer/build/out/Release/cornellBox_100spp_10maxPath_sphere.jpg)
## 2022.3.17
Add gamma correction
## 2022.3.18
Currently support
-   bsdf : conductor、dieletric
-   texture : bitmap(with out mipmap)
next: microfacet model
## 2022.4.11
embree3.dll and tbb12.dll in lib/Windows