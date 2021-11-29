#include<iostream>
#include<cmath>

struct vec2 {
    float x, y,rad;
    vec2(float x1, float y1) :x(x1), y(y1) {}
    vec2(float value) :x(value), y(value) {}

    void set_rad(float r) { this->rad = r; }

};

struct vec3 {
    float x, y, z;
    //ray(float s, float d):start(s), dir(d){}
    vec3(float x1, float y1, float z1) :x(x1), y(y1), z(z1) {}

    vec3 rotateY(vec3 a, double angle)
    {
        vec3 b = a;
        b.x = a.x * cos(angle) - a.z * sin(angle);
        b.z = a.x * sin(angle) + a.z * cos(angle);
        return b;
    }
    vec3 rotateX(vec3 a, double angle)
    {
        vec3 b = a;
        b.z = a.z * cos(angle) - a.y * sin(angle);
        b.y = a.z * sin(angle) + a.y * cos(angle);
        return b;
    }
};

//float length(vec2 const& v) { return sqrt(v.x * v.x + v.y * v.y); }
float length(vec3 const& v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

vec3 norm(vec3 v) {
    vec3 v1 = v;
    v1.x = v.x / length(v);
    v1.y = v.y / length(v);
    v1.z = v.z / length(v);
    return v1;
}

float sphere(vec3 cam, vec3 ray, float r) {
    
        float len_x = abs(ray.x - cam.x);
        float len_z = abs(cam.z);
        float len_y = abs(ray.y - cam.y);
        float len_x_z = sqrt(pow(len_x, 2) + pow(len_z, 2));
        float len_x_y_z = sqrt(pow(len_x_z, 2) + pow(len_y, 2));
        return len_x_y_z;
}


//float dot(vec3 const& a, vec3 const& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
//
//vec2 sphere(vec3 ro, vec3 rd, float r) {
//    float b = dot(ro, rd);
//    float c = dot(ro, ro) - r * r;
//    float h = b * b - c;
//    if (h < 0.0) return vec2(-1.0);
//    h = sqrt(h);
//    return vec2(-b - h, -b + h);
//}

int main()
{
    const int width = 120;
    const int height = 30;
    float aspect = (float)width / height;
    float pixelaspect = 11.0f / 24.0f;

    char* screen = new char[width * height + 1];
    screen[width * height] = '\n';

    char gradient[] = ".:!/r(l1Z4H9W8$@";
    //char gradient[] = "@$8W9H471l(r/!:.";
    int gradientSize = std::size(gradient) - 2;

    for (float t = 0; t < 10000; t++) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {

                /*float x = (float)i / width * 2.0f - 1.0f;
                float y = (float)j / height * 2.0f - 1.0f;*/
                float x = i - width / 2;
                float y = j - height / 2;
                x = x / 2.1;
                vec2 obj = vec2(x, y);
                obj.set_rad(10);
                vec3 cam = vec3(0, 0, 10);
                vec3 ray = vec3(x, y, 0);
                
                vec3 light = vec3(x + 10, y + 10, 10);
                light = light.rotateY(light, t * 0.01 );
                light = light.rotateX(light, t * 0.01);
                float lighting = sphere(cam, light, obj.rad);
                
                float dist = sphere(cam, ray, obj.rad + 3);
                int color = (int)(1000 /(lighting * dist) );
                if (color > gradientSize) { color = gradientSize; }
                if (color < 0) { color = 0; }
                char pixel = ' ';
                if (dist < 15) {
                    pixel = gradient[color];
                    //std::cout << dist << " " << lighting << " " << sin(t * 0.01) << std::endl;
                }
                
                screen[i + j * width] = pixel;

            }
        }
        printf(screen);

    }

    delete[] screen;

    getchar();

    return 0;
}
