#include<iostream>
#include<string>
#include<sstream>
#include<vector>

class Character {
private:
	std::string name;
	int xp;
	short int health;
	int* pointer;

public:
	static int copy;
	Character(std::string _name, int _xp = 0, short int _health = 100, int _pointer = 0) :
		name{ _name }, xp{ _xp }, health{ _health }{
		pointer = new int;
		*pointer = _pointer;
		std::cout << std::endl << "Default constructor for " << name << std::endl;
	}

	//Overloading
	Character() :
		Character{ "Anonymous" } {};

	//Copy Constructor
	Character(const Character& source) :
		name{ source.name }, xp{ source.xp }, health{ source.health }, pointer{ source.pointer }{

		Character::copy++;
		std::ostringstream oss;
		oss << name << " copy " << Character::copy;

		std::string _name;
		_name = oss.str();

		name = _name;

		std::cout << std::endl;
		std::cout << "Copy constructor for " << name << std::endl;
		std::cout << "Copying the class with Copy Constructor" << std::endl;
		std::cout << "Puntero actual: " << pointer << std::endl;
		std::cout << "Valor actual: " << *pointer << std::endl;

		int num = *pointer;
		int* _pointer = new int;
		*_pointer = num;
		pointer = _pointer;

		std::cout << std::endl;
		std::cout << "Cambiamos el puntero: " << pointer << std::endl;
		std::cout << "Queda el mismo valor: " << *pointer << std::endl;
	};

	//Move constructor
	/*
	Character(Character&& source) noexcept :
		name{ source.name }, xp{ source.xp }, health{ source.health }, pointer{ source.pointer }{

		std::cout << std::endl;
		std::cout << "Move constructor for " << name << std::endl;

		source.pointer = nullptr;

		std::cout << std::endl;
	}
	*/

	//Destructor
	~Character() {
		if (pointer == nullptr) {
			std::cout << std::endl;
			std::cout << "No hace falta eliminar nada porque "
				<< "ya está la memoria libre" << std::endl;
		}
		else {
			std::cout << std::endl;
			std::cout << "Llamamos al destructor de " << name << std::endl;
			std::cout << "Liberamos memoria en: " << pointer << std::endl;
			delete pointer;
		}
	}

	int* get_pointer() { return pointer; }
	std::string get_name() { return name; }
	std::string get_name_const() const { return name; }
};

int Character::copy{ 0 };

void test_move() {
	/*
	* Bueno, cómo es esto?? Cuando creamos, por ejemplo, un vector de Character y
	* añadimos elementos con push_back sin haberlos creaado anteriormente,
	* C++ crea una copia temporal del elemento con el constructor y después
	* copia esa copia con el copy constructor dentro del vector.
	* Haciendo esto, consumimos bastantes recursos que se pueden evitar haciendo un
	* MOVE CONSTRUCTOR. Empecemos creando el vector normal, sin el nuevo constructor:
	*/

	std::vector<Character> enemies;
	std::cout << "Creamos el vector ENEMIES..." << std::endl;
	std::cout << "Añadimos 5 elementos..." << std::endl;

	int copy = Character::copy;

	enemies.push_back(Character());
	enemies.push_back(Character());
	enemies.push_back(Character());
	enemies.push_back(Character());
	enemies.push_back(Character());

	std::cout << std::endl << std::endl;
	std::cout << "*-------------------------------------------------------------------*" << std::endl;
	std::cout << "*- Acá podemos ver como se crearon " << Character::copy - copy
		<< " copias para solo 5 elementos -*"
		<< std::endl;
	std::cout << "*-------------------------------------------------------------------*" << std::endl;

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "*-----------------------------------------------------------------------*" << std::endl;
	std::cout << "*-------------- TERMINA EL TEST_MOVE, ARRANCAN LOS DELETE --------------*" << std::endl;
	std::cout << "*-----------------------------------------------------------------------*" << std::endl;
	std::cout << "*- Para ver el ejemplo con move constructor, descomentarlo de la clase -*" << std::endl;
	std::cout << "*-----------------------------------------------------------------------*" << std::endl;
}

int main() {

	Character* enemy_1 = new Character("Enemy 1", NULL, NULL, 25);
	std::cout << "Creamos un enemigo: " << enemy_1->get_name() << std::endl;
	std::cout << "Creamos la primera copia de Enemy:" << std::endl;
	Character* enemy_copy_1 = new Character(*enemy_1);
	std::cout << "Nombre de la copia 1: " << enemy_copy_1->get_name() << std::endl;
	std::cout << "Creamos una segunda copia:" << std::endl;
	Character* enemy_copy_2 = new Character(*enemy_1);
	std::cout << "Nombre de la copia 2: " << enemy_copy_2->get_name() << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Eliminamos las copias..." << std::endl;
	delete enemy_copy_1;
	delete enemy_copy_2;

	std::cout << std::endl << std::endl;

	Character* enemy_anonymous = new Character();
	std::cout << "Creamos un enemigo anónimo: " << enemy_anonymous->get_name() << std::endl;
	delete enemy_anonymous;
	std::cout << std::endl;

	std::cout << "Copiamos la clase Enemy:" << std::endl;
	Character* enemy_copy = new Character(*enemy_1);
	std::cout << "Puntero del enemy: " << enemy_1->get_pointer() << std::endl;
	std::cout << "Valor del puntero de enemy: " << *(enemy_1->get_pointer()) << std::endl;
	std::cout << std::endl;

	std::cout << "Puntero de la copia: " << enemy_copy->get_pointer() << std::endl;
	std::cout << "Valor del puntero de la copia: " << *(enemy_copy->get_pointer()) << std::endl;
	std::cout << std::endl;

	std::cout << "Guardamos el puntero para comprobar valor..." << std::endl;
	const int* pointer_enemy_copy = enemy_copy->get_pointer();

	std::cout << "Eliminamos la copia..." << std::endl;
	delete enemy_copy;
	std::cout << std::endl;

	std::cout << "Comprobamos el valor del puntero eliminado..." << std::endl;
	std::cout << "El valor del puntero eliminado es: " << *pointer_enemy_copy << std::endl;
	std::cout << "El valor del puntero original es: " << *(enemy_1->get_pointer()) << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	/*
	*-------------------------------------------------------*
	* EJEMPLO DE QUÉ PASARÍA SI NO CREAMOS UN NUEVO PUNTERO *
	*-------------------------------------------------------*
	*
	* Acá se genera un problema en el Copy Constructor si es que nuestra clase tiene
	* parámetros que son punteros, porque al apuntar todos al mismo lugar, si uno se libera, por
	* consecuencia, se liberan todos. Por eso hay que hacer un Copy Constructor un poco más
	* "sofisticado".
	* 
	*-------------------------------------------------------*
	* Descomentar el siguiente código para ver el ejemplo:
	*/
	
	/*
	int num = 50;
	int* pointer_1 = new int;
	*pointer_1 = num;

	std::cout << "Ya tenemos el primer puntero apuntando a: " << pointer_1 << std::endl;

	int* pointer_copy = pointer_1;

	std::cout << "Ahora creamos la copia y apunta a: " << pointer_copy << std::endl;
	std::cout << "Pasamos a destruir la copia..." << std::endl;

	delete pointer_copy;

	std::cout << "Eliminada la copia, el puntero original sigue apuntando a: " << pointer_1 << std::endl;
	std::cout << "Ahora, el valor del puntero original " << pointer_1 << " es: " << *pointer_1;
	*/

	std::cout << "*--------------------------------------------------*" << std::endl;
	std::cout << "*---------------- MOVE CONSTRUCTOR ----------------*" << std::endl;
	std::cout << "*--------------------------------------------------*" << std::endl;
	test_move();

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Ahora pasamos a ver MÉTODOS CONST:" << std::endl;
	std::cout << "Creamos un character constante:" << std::endl;

	const Character* const_character = new Character("Character CONST");
	/*
	* Ahora vamos a ver que la siguiente línea da error. Por qué?? porque C++ piensa que
	* la función puede llegar a cambiar el valor de const_character implícitamente, entonces no se
	* arriesga a ejecutarla. La solución a esto es agregar la palabra const al método para avisarle
	* al compilador que esa función NO modificará al objeto. Así, se va a poder ejecutar 
	* tranquilamente.
	*/

	//std::cout << const_character->get_name() << std::endl;

	/*
	* Haciendo eso, podemos ver que ahora corre sin problemas.
	* NOTA: obviamente, al agregarle el const al método, le prohibimos al mismo modificar
	* al objeto.
	*/
	std::cout << "Mostramos el nombre del const_character: " << std::endl;
	std::cout << const_character->get_name_const() << std::endl;

	return 0;
}