#include "../lib/tcalendario.cpp"
#include "../lib/tvectorcalendario.cpp"
#include "../lib/tabbcalendario.cpp"



int main(){
	TCalendario tc1del3(1, 3, 2024, "texto1");
	TCalendario tc2del3(2, 3, 2024, "texto2");
	TCalendario tc3del3(3, 3, 2024, "texto3");
	TCalendario tc4del3(4, 3, 2024, "texto4");
	TCalendario tc5del3(5, 3, 2024, "texto5");

	TCalendario tc6del3(6, 3, 2024, "texto6");
	TCalendario tc7del3(7, 3, 2024, "texto7");
	TCalendario tc8del3(8, 3, 2024, "texto8");
	TCalendario tc9del3(9, 3, 2024, "texto9");
	TCalendario tc10del3(10, 3, 2024, "texto10");

	TCalendario tc15del3(15, 3, 2024, "texto15"); // para el buscar

	
	TABBCalendario def;

	TABBCalendario arbol;

	// PARA INSERTAR: si es igual no inserta, sino: visita raiz si < izq si > der, 
	// si raiz NULL inserta.
	arbol.Insertar(tc5del3);
	arbol.Insertar(tc8del3);
	arbol.Insertar(tc3del3);

	arbol.Insertar(tc2del3);
	arbol.Insertar(tc1del3);
	arbol.Insertar(tc7del3);
	
	arbol.Insertar(tc4del3);
	arbol.Insertar(tc6del3);
	arbol.Insertar(tc10del3);
	
	arbol.Insertar(tc9del3);


	// ARBOL:
	// 	            5
	//        	   / \
	//       	  /   \
	//     		 /     \
	//			/       \
 	//     	   3         8
	//    	  / \       / \
	//   	 2   4     7   10
	//  	/         /    /  
	// 	   1         6    9 

	bool comprobaciones = false;
	if(comprobaciones){
		cout << "Nodos del Árbol: " << arbol.Nodos() << endl;
		cout << "Nodos Hoja del Árbol: " << arbol.NodosHoja() << endl;

		cout << "Altura del Árbol: " << arbol.Altura() << endl;
		// cout << "Altura del Árbol def: " << def.Altura() << endl;
		// def.Insertar(tc5del3);
		// cout << "Altura del Árbol def: " << def.Altura() << endl;


		// RECORRIDOS
		// cout << "Recorrido Inorden: " << arbol.Inorden() << endl;
		// cout << "Recorrido Postorden: " << arbol.Postorden() << endl;
		// cout << "Recorrido Preorden: " << arbol.Preorden() << endl;


		// RAÍZ
		// cout << "Raíz def: " << def.Raiz() << endl;
		// cout << "Raiz: " << arbol.Raiz() << endl;


		// BUSCAR
		// cout << "Buscando tc1del3: ";
		// if(arbol.Buscar(tc1del3))
		// 	cout << "ENCONTRADO." << endl;
		// else
		// 	cout << "ERROR." << endl;

		// cout << "Buscando tc9del3: ";
		// if(arbol.Buscar(tc9del3))
		// 	cout << "ENCONTRADO." << endl;
		// else
		// 	cout << "ERROR." << endl;

		// cout << "Buscando tc15del3: ";
		// if(arbol.Buscar(tc15del3))
		// 	cout << "ENCONTRADO." << endl;
		// else
		// 	cout << "ERROR." << endl;


		// NIVELES
		// TVectorCalendario niv = arbol.Niveles();
		// cout << "Recorrido Niveles: " << niv << endl;


		// BORRADO
		// cout << "Último elemento del vector es: " << niv[niv.Tamano()] << endl;
	}


	bool pruebaBorrado = true;
	if(pruebaBorrado){

		// BORRADO
		// nodo hoja
		arbol.Borrar(tc9del3);
		cout << "Borrado el tc9del3: " << arbol << endl;
		arbol.Insertar(tc9del3); // vuelve a su posicion

		// nodo con solo hijo izquierdo
		arbol.Borrar(tc2del3);
		cout << "Borrado el tc2del3: " << arbol << endl;
		arbol.Borrar(tc1del3);
		arbol.Insertar(tc2del3); // vuelve a su posicion
		arbol.Insertar(tc1del3);
		cout << endl << arbol << endl << endl;

		// nodo con hijo izquierdo Y derecho
		//     	   3         7
		//    	  / \       / \
		//   	 2   4     6   10
		//  	/              /  
		// 	   1              9 
		arbol.Borrar(tc8del3);
		cout << "Borrado el tc8del3: " << arbol << endl;
		arbol.Insertar(tc8del3);
	}




	return 0;
}







