### swap channels

```
tmp = color.r;
color.r = color.b;
color.b = tmp;
```

j'ai fait une variable tmp avant de voir que y'avait la fonction native swap, soit

### noir et blanc

on fait une moyenne de chaque canal et on l'assigne cette moyenne à tous les canaux pcq les gris ont tjrs des valeurs de canaux égales (genre 12 12 12 ou 123 123 123)

### inverser

ok c'est greg qui m'a donné la solution je sais pas pourquoi j'avais pas pensé à faire 1 - la valeur du channel

### noise

mon image est super grande (j'aurai du écouter et faire 500 px max) donc on voit pas tant que ça le grain, par ailleurs : 

```
image.pixel(x, y) = glm::vec3{
    random_float(0, 1),
    random_float(0, 1),
    random_float(0, 1)
};
```

permet un bruit coloré, tandis qu'un simple argument 

```
image.pixel(x, y) = glm::vec3{random_float(0, 1)};
```

rend le bruit en nuances de gris (vu qu'on a une valeur pour tous les channels)

### rotation 90

au lieu de parcourir la moitié sur l'axe y on parcourt la moitié sur la diagonale, après j'avoue c'était beaucoup de tâtonnements pour trouver la formule. Je vois bien qu'il y a une translation intelligente qui se fait à partir de la formule, mais visuellement c'est difficile de me le représenter

### rosace et cercle

```
void rosace(sil::Image& image, int roscenterx, int roscentery, int rosradius, int thickness)
{
    circle(image, roscenterx, roscentery, rosradius, thickness);

    for(float angle{0}; angle <= (5*M_PI/3); angle += M_PI/3){
        double centerx {(roscenterx + (cos(angle)*rosradius))};
        double centery {(roscentery + (sin(angle)*rosradius))};  
        
        circle(image, centerx, centery, rosradius, thickness);
    }
}
```

en fait j'ai juste répété la fonction cercle en changeant le centre du cercle, mais du coup je me suis rendu compte avec ça que je peux empiler les fonctions pour créer des compositions si je voulais vraiment

```
{   
    sil::Image image{"images/image.jpg"}; 
    mosaic(image); 
    noise(image, true);
    image.save("output/mosaic.png");
}
```

par exemple là c comme des calques sur photoshop je mets un filtre mosaïque, puis je rajoute du bruit monochrome (paramètre mono = true sur l'exemple), et si je veux je peux rajouter du background, etc. mettre des paramètres sur les fonctions pour modifier directement les valeurs une seule fois quand je les appelle

certains dans la classe se sont amusés et ont même fait une invite de commandes pour créer un mini photoshop en version ligne de commande c'est trop cool!!