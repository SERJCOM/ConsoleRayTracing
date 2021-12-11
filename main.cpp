#include<iostream>
#include<cmath>

struct vec2 {
    float x, y, rad;
    vec2(float x1, float y1) :x(x1), y(y1) {}
    vec2(float value) :x(value), y(value) {}

    void set_rad(float r) { this->rad = r; }

};

struct vec3 {
    float x, y, z,r;
    vec3(float x1, float y1, float z1) :x(x1), y(y1), z(z1) {}

    vec3(float x1, float y1, float z1,float r1) :x(x1), y(y1), z(z1), r(r1) {}
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

    vec3 setZ(float z1) { this->z = z1; }

    /*vec3 norm(vec3 v) {
        vec3 v1 = v;
        v1.x = v.x / length(v);
        v1.y = v.y / length(v);
        v1.z = v.z / length(v);
        return v1;
    }*/
};

float length(vec3 const& v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

float length(float x1, float y1, float z1, float x2, float y2, float z2) { 
    return (float)(sqrt(pow(x2-x1,2) + pow(y2-y1,2) + pow(z2 - z1,2))); 
}



float sphere(vec3 cam, vec3 ray, float r) {

    float len_x = abs(ray.x - cam.x);
    float len_z = abs(cam.z);
    float len_y = abs(ray.y - cam.y);
    float len_x_z = sqrt(pow(len_x, 2) + pow(len_z, 2));
    float len_x_y_z = sqrt(pow(len_x_z, 2) + pow(len_y, 2));
    return len_x_y_z;
}

float z(float x, float y, float r) {
    return sqrt(r * r - x * x - y * y);
}

float pow2(float num) {
    return pow(num, 2);
}

float sph(vec3 cam, vec3 ray, vec3 point, vec3 obj) {
    if (pow2(ray.x) + pow2(ray.y) <= pow2(obj.r)) {
        float point_z = z(ray.x, ray.y, obj.r);
        return length(cam.x, cam.y, cam.z, ray.x, ray.y, point_z);
    }
    else {
        return 0;
    }
}

float lighting(vec3 cam, vec3 ray, vec3 light, vec3 obj) {
    if (pow2(ray.x) + pow2(ray.y) <= pow2(obj.r)) {
        float point_z = z(ray.x, ray.y, obj.r);
        return length(light.x, light.y, light.z, ray.x, ray.y, point_z);
    }
    else {
        return 0;
    }
}

int main()
{
    const int width = 120;
    const int height = 30;
    float aspect = (float)width / height;
    float pixelaspect = 11.0f / 24.0f;
    char* screen = new char[width * height + 1];
    screen[width * height] = '\n';
    char gradient[] = " .:!/r(l1Z4H9W8$@";
    int gradientSize = std::size(gradient) - 2;

    for (float t = 0; t < 10000; t++) {
        vec3 light = vec3(sin(t * 0.01)/1.5, -0.5, cos(t * 0.01)/1.5);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                float x = (float)i / width * 2.0 - 1.0;
                float y = (float)j / height * 2.0 - 1.0;
                x = x * aspect * pixelaspect;
                float r = 0.7f;
                
                vec3 obj = vec3(0, 0, 0,r);
                vec3 cam = vec3(0, 0, 1);
                vec3 ray = vec3(x, y, 0);
                vec3 point = vec3(x, y, 0);
                

                float len = sph(cam, ray, point, obj);
                float light_len = lighting(cam, ray, light, obj);
                int pixel = 0;
                
                if (len != 0 && light_len != 0) {
                    pixel = (int)(abs(8/(light_len)));
                }
                if (pixel < 0) { pixel = 0; }
                if (pixel > gradientSize) { pixel = gradientSize; }

                screen[i + j * width] = gradient[pixel];
            }
        }
        printf(screen);
    }
    delete[] screen;
    getchar();

    return 0;
}