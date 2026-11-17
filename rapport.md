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