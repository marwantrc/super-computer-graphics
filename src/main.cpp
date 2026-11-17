#include <sil/sil.hpp>
#include <random.hpp>
#include <cmath>
#include <numbers>

void keep_green_only(sil::Image& image)
{
   for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void channels_swap(sil::Image& image)
{
    float tmp {0};
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void black_white(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float grey {(color.r + color.g + color.b)/3};

        color = glm::vec3{grey, grey, grey};
    }
}

void invert(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float invr {1 - color.r};
        float invg {1 - color.g};
        float invb {1 - color.b};

        color = glm::vec3{invr, invg, invb};
    }
}

void gradient(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3{x/float(image.width())};
        }
    }
}

void mirror(sil::Image& image)
{
    for (int x{0}; x < image.width()/2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.width() - (x+1), y));
        }
    }
}

void noise(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int aleatoire = random_int(0, 5);
            if (aleatoire == 1)
            {
                image.pixel(x, y) = glm::vec3{
                    random_float(0, 1),
                    random_float(0, 1),
                    random_float(0, 1)
                };
            }
        }
    }
}

void rotate90(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height()-x; y++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.height()-y-1, image.width()-x-1));
        }
    }
}

void rgbsplit(sil::Image& image)
{
    sil::Image output{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            output.pixel(x, y).g = image.pixel(x, y).g;
            if(x>50){
                output.pixel(x, y).r = image.pixel(x-50, y).r;
            }
            if(x<image.width()-50){
                output.pixel(x, y).b = image.pixel(x+50, y).b;
            }
        }
    }
    image = output;
}

void disc(sil::Image& image)
{
    for (int x{0}; x<image.width(); x++)
    {
        for (int y{0}; y<image.height(); y++)
        {
            int radius {100};
            int centerx {image.width()/2};
            int centery {image.height()/2};

            if ((std::pow(x - centerx, 2) + std::pow(y - centery, 2)) <= std::pow(radius, 2)) {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
}

void circle(sil::Image& image)
{
    for (int x{0}; x<image.width(); x++)
    {
        for (int y{0}; y<image.height(); y++)
        {
            int radius {100};
            int thickness {15};
            int centerx {image.width()/2};
            int centery {image.height()/2};
            double disk_equation {(std::pow(x - centerx, 2) + std::pow(y - centery, 2))};

            if (std::pow(radius - thickness, 2) <= disk_equation && disk_equation <= std::pow(radius, 2)) {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
}


int main()
{
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     keep_green_only(image); 
    //     image.save("output/keep_green_only.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     channels_swap(image); 
    //     image.save("output/channels_swap.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     black_white(image); 
    //     image.save("output/black_white.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     invert(image); 
    //     image.save("output/invert.png");
    // }
    // {
    //     sil::Image image{300, 200};
    //     gradient(image); 
    //     image.save("output/gradient.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     mirror(image); 
    //     image.save("output/mirror.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     noise(image); 
    //     image.save("output/noise.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     rotate90(image); 
    //     image.save("output/rotate90.png");
    // }
    // {
    //     sil::Image image{"images/image.jpg"}; 
    //     rgbsplit(image); 
    //     image.save("output/rgbsplit.png");
    // }
    // {   
    //     sil::Image image{500, 500}; 
    //     disc(image); 
    //     image.save("output/disc.png");
    // }
    {   
        sil::Image image{500, 500}; 
        circle(image); 
        image.save("output/circle.png");
    }
}