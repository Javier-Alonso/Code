# Árbol Binario de Búsqueda

Implemetación en C++ con enfoque orientado a objetos de un aŕbol binario de búsqueda. 
Mediante herencia, se implementa el Árbol de Búsqueda Binario (BST) y el Árbol AVL.
Se incluye un programa principal para testear las operaciones de inserción y búsqueda en la árbol.


## Ejecución

Para ejecutar el programa, sigue los pasos siguientes:


### Modo Demostración

Este modo permite ver una traza de las operaciones de búsqueda e inserción en el árbol.

```
cd build
```
```
make CFLAGS="-D DEMO"
```
```
./main
```

### Modo Estadística

Este modo permite ver el número de comparaciones en operaciones de búsqueda e inserción en el árbol.

```
cd build
```
```
make
```
```
./main $tamañoArbol $numeroPruebas
```

## Nota

Si deseas cambiar el tipo de árbol sobre el que realizar el estudio (BST o AVL), simplemente cambia
la siguiente línea del programa principal:

```
using TreeTemplate = AyEDA::AVLTree<AyEDA::DNI>;
```
```
using TreeTemplate = AyEDA::BinarySearchTree<AyEDA::DNI>;
```

## Authors

* **Javier Alonso** - *Initial work* - [JavierAlonso](https://github.com/Javier-Alonso)
