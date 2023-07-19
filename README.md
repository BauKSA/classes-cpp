# classes-cpp
Bueno... como podrán ver, este es un archivo que ya tenía hecho hace un tiempito, de un curso que hice de C++, y que ahora me decidí a subirlo. Es un solo archivo con casi 250 líneas de código, pero bueno, traté de hacerlo lo más ordenado y comentado posible para que se entiendan algunos temas a la hora de usar clases en C++. Principalmente está el tema de constructores y punteros como atributos.
Les dejo la lsita de lo que hay en el proyecto que, dicho sea de paso, es un sln de Visual Studio, pero si quieren pueden ver solo el .cpp y ya.

#### Default constructor:
##### El constructor por defecto de la clase. No tiene mucha ciencia.
#### Overloading constructor:
##### Acá hay un ejemplo de overloading en el contructor. Básicamente, permitiendo que la clase tenga un nombre asignado por el usuario o un nombre anónimo ("Anonymous").
#### Copy constructor:
##### El constructor que se llama cuando se quiere hacer una copia de una instancia de la clase.
Esto viene principalmente por los problemas que trae tener un puntero como atributo. Hay comentado un ejemplo de qué pasaría si no se llama al copy constructor... copias superficiales (shallow) y profundas (deep).
#### Move constructor:
##### El constructor que se usa para optimizar el rendimiento cuando se quieren usar varias instancias anónimas de una clase, por ejemplo, para armar un vector de las mismas.
Acá también hay un ejemplo de qué pasaría si no se usa este Move Constructor.
#### Default destructor:
##### El destructor por defecto de la clase. Más que nada está para mostrar algunas cosas como el error de los punteros.
#### static:
##### Variables estáticas en una clase. Para qué sirven y un ejemplo de uso.

#### BONUS:
##### Como bonus, también hay algo de métodos constantes para instancias constantes y un uso de concatenación con sstrema.
