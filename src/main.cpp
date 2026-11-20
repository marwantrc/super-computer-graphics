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

void greyscale(sil::Image& image)
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

void noise(sil::Image& image, bool mono, int strength)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int aleatoire = random_int(0, strength);
            if (aleatoire == 1)
            {
                if (!mono){
                    image.pixel(x, y) = glm::vec3{
                        random_float(0, 1),
                        random_float(0, 1),
                        random_float(0, 1)
                    };
                } else {
                    image.pixel(x, y) = glm::vec3{random_float(0,0.5)};
                }
            }
        }
    }
}

void noise2(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float brightness {(color.r + color.g + color.b)/3};

        color = glm::vec3{brightness + random_float(-0.5, 0.5)};
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

void rgbsplit(sil::Image& image, int split_strength)
{
    sil::Image output{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            output.pixel(x, y) = glm::vec3{0.75, image.pixel(x, y).g, 0.75};
            if(x>split_strength){
                output.pixel(x, y).r = image.pixel(x-split_strength, y).r;
            }
            if(x<image.width()-split_strength){
                output.pixel(x, y).b = image.pixel(x+split_strength, y).b;
            }
        }
    }
    image = output;
}

void colorsplit(sil::Image& image, int split_strength)
{
    sil::Image output{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            output.pixel(x, y) = glm::vec3{0.75, image.pixel(x, y).g, 0.75};
            if(x>split_strength){
                output.pixel(x, y).r = image.pixel(x-split_strength, y).r;
            }
            if(x<image.width()-split_strength){
                output.pixel(x, y).b = image.pixel(x+split_strength, y).b;
            }
        }
    }
    image = output;
}

void disc(sil::Image& image, int dist_from_center)
{
    for (int x{0}; x<image.width(); x++)
    {
        for (int y{0}; y<image.height(); y++)
        {
            int radius {150};
            int centerx {image.width()/2 + dist_from_center};
            int centery {image.height()/2};

            if ((std::pow(x - centerx, 2) + std::pow(y - centery, 2)) <= std::pow(radius, 2)) {
                image.pixel(x, y) = glm::vec3{0.749, 0.863, 1};
            } else {
                image.pixel(x, y) = glm::vec3{1};
            }
        }
    }
}

// image, centres, radius et épaisseur
void circle(sil::Image& image, int centerx, int centery, int radius, int thickness)
{
    for (int x{0}; x<image.width(); x++)
    {
        for (int y{0}; y<image.height(); y++)
        {
            double disk_equation {(std::pow(x - centerx, 2) + std::pow(y - centery, 2))};

            if (std::pow(radius - thickness, 2) <= disk_equation && disk_equation <= std::pow(radius, 2)) {
                image.pixel(x, y) = glm::vec3{0};
            }
        }
    }
}

void rosace(sil::Image& image, int roscenterx, int roscentery, int rosradius, int thickness)
{
    circle(image, roscenterx, roscentery, rosradius, thickness);

    for(float angle{0}; angle <= (5*M_PI/3); angle += M_PI/3){
        double centerx {(roscenterx + (cos(angle)*rosradius))};
        double centery {(roscentery + (sin(angle)*rosradius))};  
        
        circle(image, centerx, centery, rosradius, thickness);
    }
}

void mosaic(sil::Image& image, int tiles)
{
    sil::Image new_image{image.width()*tiles, image.height()*tiles}; 
    
    for (int x{0}; x < new_image.width(); x++)
    {
        for (int y{0}; y < new_image.height(); y++)
            {
            new_image.pixel(x, y) = image.pixel(x%image.width(), y%image.height());
        }
    }

    sil::Image final_image{image.width(), image.height()}; 

   for (int x{0}; x < final_image.width(); x++)
    {
        for (int y{0}; y < final_image.height(); y++)
        {
            final_image.pixel(x, y) = new_image.pixel(x*tiles, y*tiles);
        }
    }

    image = final_image;
}

void mosaic_mirror(sil::Image& image, int tiles)
{
    // crée le receptacle de l'opération mosaique
    sil::Image new_image{image.width()*tiles, image.height()*tiles}; 

    // cordonnées en tiles
    int tile_x {0};
    int tile_y {0};

    // taille d'une tile en pixel
    int tile_sizex = new_image.width()/tiles;
    int tile_sizey = new_image.height()/tiles; 
    
    for (int x{0}; x < new_image.width(); x++)
    {
        if(x%tile_sizex == 0){
            tile_x ++;
        }
        for (int y{0}; y < new_image.height(); y++){
            
            if(y%tile_sizey == 0){
                tile_y ++;
            }

            if(tile_x%2 == tile_y%2){
                if(tile_y%2 == 0){
                    new_image.pixel(x, y) = image.pixel((tile_x*tile_sizex - x)%image.width(), (tile_y*tile_sizey - y)%image.height());
                } else{
                    new_image.pixel(x, y) = image.pixel(x%image.width(), y%image.height());
                }
            } else if (tile_y%2 == 1){
                new_image.pixel(x, y) = image.pixel((tile_x*tile_sizex - x)%image.width(), y%image.height());
            } else if (tile_y%2 == 0){
                new_image.pixel(x, y) = image.pixel(x%image.width(), (tile_y*tile_sizey - y)%image.height());
            }
        }
        tile_y = 0;
    }
    
    sil::Image final_image{image.width(), image.height()}; 

   for (int x{0}; x < final_image.width(); x++)
    {
        for (int y{0}; y < final_image.height(); y++)
        {
            final_image.pixel(x, y) = new_image.pixel(x*tiles, y*tiles);
        }
    }

    image = final_image;
}


void background(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
        //  image.pixel(x, y) = glm::vec3{1, y/float(image.height()*5)+0.85, y/float(image.height()*5)+0.95};
            image.pixel(x, y) = glm::vec3{1};
        }
    }
}

//ATTENTION : à appliquer sur greyscale
void threshold(sil::Image& image, float value)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(image.pixel(x, y).r > value){
                image.pixel(x, y) = glm::vec3{1};
            } else {
                image.pixel(x, y) = glm::vec3{0};
            }
        }
    }
}

int main()
{ 
    
    sil::Image image{500, 500};
    // sil::Image image{"images/image.jpg"}; 

    background(image);
    rosace(image, image.width()/2, image.height()/2, 100, 10);
    image.save("output/rosace.png");



    // channels_swap(image);
    // image.save("output/channels_swap.png");

    // greyscale(image);
    // image.save("output/greyscale.png");

    // keep_green_only(image);
    // image.save("output/green.png");

    // rgbsplit(image, 10);
    // image.save("output/rgb_split.png");

    // invert(image);
    // image.save("output/invert.png");

    // rotate90(image);
    // image.save("output/rotate90.png");

    // noise(image, true, 5);
    // image.save("output/noise.png");

    
    // for (int x{0}; x < 450; x++){
    //     sil::Image image{500, 500};
    //     background(image);
    //     rosace(image, image.width()/2, image.height()/2, 1+x, 15+x/5); 
    //     mosaic_mirror(image, 6);
    //     channels_swap(image);
    //     std::stringstream stream;
    //     stream << "output/anim2/anim_" << x << ".png";
    //     image.save(stream.str());
    // }

}