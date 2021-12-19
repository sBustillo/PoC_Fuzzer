#include <iostream>
#include <string>
#include <fstream>
#include <random>


#include <windows.h>

using namespace std;

int getRandomNumber(int);

int main(){
	
	int nArchivos, nBytes;
	char * memblock;
	
	bool dbg = true;
	int randpost;
	std::string outname = "badfile.pdf";
	std::string outnameConcat;
	std::string randstr;
	streampos size;
	
	ofstream copyFile;
			
	
	cout << "\n\n Introduce el numero de archivos a generar: ";
	cin >> nArchivos;
	//check for int only
	cout << "\n\n Introduce el numero de bytes a introducir";
	cin >> nBytes; // -> pòr el momento es inutil
	//check for int only
	
	ifstream originalFile("bueno.pdf");
	//check if its open
	if (!originalFile){
		cout << "archivo original no encontrado";
		return -1;
	}
	
	//obtememos tamaño del archivo
	originalFile.seekg(0,ios::end);
	size = originalFile.tellg();
	originalFile.seekg (0, ios::beg);
	
	
	memblock = new char [size];
    originalFile.read (memblock, size);
    
    
    if (debug){
	    //- - - - debug - - - -//
	    cout << "size is: ";
		cout << size;
		cout <<"\n\n";
		//- - - - ---- - - - -//
	}
    
	
	while(nArchivos > 0){
		//generamos el nuevo nombre;
	 	outnameConcat = std::to_string(nArchivos) + "-" + outname;
	 	
	 	//Abrimos el archivo nuevo
		copyFile.open(outnameConcat);
		
		originalFile.read (memblock, size);
		
		randpost = getRandomNumber(size);
		if (debug){
			//- - - - debug - - - -//
			cout << "rand number is: ";
			cout << randpost;
			cout <<"\n\n";
			//- - - - ---- - - - -//
		}
		
		//Generamos una string random para insertar en una posicion aleatoria.
		randstr = std::to_string(randpost) + "_";
		
		if (debug){
			//- - - - debug - - - -//
			cout << "pos in memblock is :";
			cout << &memblock[randpost];
			cout <<"\n\n";
			cout << "size of the chunk is:";
			cout << sizeof(memblock[randpost]);
			cout <<"\n\n";
			cout << "str content: ";
			cout << randstr;
			cout << "\n";
			cout << randstr[0];
			cout << "\n";
			//- - - - ---- - - - -//
		}
		
		//to do: insertar cadenas de bytes de longitud que nos de la gana
		memblock[randpost] = randstr[0];
		
		
		if (debug){
			cout << "memblock mod -> ";
			cout << memblock[randpost];
			cout << "\n";
		}
		
		copyFile.write (memblock,size);
		
		nArchivos--;
		copyFile.close();
		if (debug){
			system("pause");
		}
	}
	originalFile.close();
	return 0;	
}


int getRandomNumber(int maxRange){
	return rand() % maxRange + 1;
}
