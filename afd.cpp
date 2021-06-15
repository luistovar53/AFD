/* ==================================================================
 *      Programa AFD
 * ==================================================================
 * Alumnos:
 * Caridad Mireles
 * Luis Alberto Tovar Ortiz
 * 
 ================================================================== */
#include <iostream>
#include <string>
#include <stdlib.h>


using namespace std;


class AFD {
private:
	string* Q;		// Conjunto de estados
	char* Sigma;	// conjunto del Alfabeto (caracteres)
	string** delta;	// función de transición
	string q0;		// Estado inicial
	string* F;		// Conjunto de Estados de aceptación
	
	int nQ;			// Número de estados
	int nSigma;		// cantidad de elementos del alfabeto
	int nF;			// cantidad de estados de acpetación

public:
	AFD() {			// Por hacer: entrada de los parámetros del AFD al definir el objeto
		int i;
		nQ = 3;
		nSigma = 2;
		nF = 1;
		
		Q = new string[nQ];
		F = new string[nF];
		Sigma = new char[nSigma];
		delta = new string * [nQ];
		for (i = 0; i < nQ; i++) {
			delta[i] = new string[nSigma];
		}
		
		// Por hacer: generar procedimientos de entrada por el usuario para definir los parámetros del AFD
		q0 = "q0";

		Q[0] = "q0";
		Q[1] = "q1";
		Q[2] = "q2";
		
		F[0] = "q1";

		Sigma[0] = '0';		// Caracteres del alfabeto
		Sigma[1] = '1';

		delta[0][0] = "q0";
		delta[0][1] = "q1";
		delta[1][0] = "q2";
		delta[1][1] = "q1";
		delta[2][0] = "q1";
		delta[2][1] = "q1";
	}

	~AFD() {
		int i;
		for (i = 0; i < nQ; i++) {
			delete[] delta[i];
		}
		delete[] delta;
		delete[] Q;
		delete[] F;
		delete[] Sigma;
	}

	// sobre carga de operador para mostrar tabla de transiciones del AFD
	friend ostream& operator<<(ostream & stream, const AFD & afd) {
		int i, j;
		stream << "Q " << "\t" << "Sigma" << "\n";
		for (i = 0; i < afd.nSigma; i++) {
			stream << "----------";
		}
		
		stream << "\n";
		stream << "  " << "\t";
		for (i = 0; i < afd.nSigma; i++) {
			stream << afd.Sigma[i] << " \t";
		}
		stream << "\n"; 
		for (i = 0; i < afd.nSigma; i++) {
			stream << "----------";
		}
		stream << "\n";
		for (i = 0; i < afd.nQ; i++) {
			stream << afd.Q[i] << "\t";
			for (j = 0; j < afd.nSigma; j++) {
				stream << afd.delta[i][j] << "\t";
			}
			stream << "\n";
		}
		return stream;
	}

	// Retorna el índice del estado dado (posición en el arreglo Q del AFD)
	int indexQ(const string & q, const AFD & afd) {
		int i, r = -1;

		for (i = 0; i < afd.nQ; i++) {
			if (q == afd.Q[i]) {
				r = i; 
				break;
			}
		}

		return r;
	}

	// Retorna el índice del caracter del alfabeto (posición en el arreglo Sigma del AFD)
	int indexSigma(const char & c, const AFD& afd) {
		int i, r = -1;

		for (i = 0; i < afd.nSigma; i++) {
			if (c == afd.Sigma[i]) {
				r = i;
				break;
			}
		}

		return r;
	}

	// Verifica que el elemento q pertenesca al conjunto de estados finales F del AFD, retorna 0 si no pertenece y 1 si esta dentro del conjunto
	int verifyF(const string& q, const AFD& afd) {
		int i, r = 0;

		for (i = 0; i < afd.nF; i++) {
			if (q == afd.F[i]) {
				r = 1;
				break;
			}
		}

		return r;
	}

	// Verifica que el elemento q pertenesca al conjunto de estados Q del AFD, retorna 0 si no pertenece y 1 si esta dentro del conjunto
	int verifyQ(const string& q, const AFD& afd) {
		int i, r = 0;

		for (i = 0; i < afd.nQ; i++) {
			if (q == afd.Q[i]) {
				r = 1;
				break;
			}
		}

		return r;
	}

	// Procedimiento para comprobar si la cadena str es validada por el AFD, retorna 0, si es rechazada o no valida y 1 si es aceptada o válida
	int stringVerification(const string & str, const AFD & afd) {
		int i, j, q, iSigma, v = 0;

		string q1;
		string str1 = str;

		string::iterator p;
		
		p = str1.begin();

		// Obtener estado inicial
		q1 = afd.q0;

		// Obtener indice del estado inicial
		q = indexQ(q1, afd);
		
		// Recorrer cadena de entrada buscando caracteres del alfabeto
		for (i = 0; i < str.size(); i++) {
			q1 = afd.delta[q][indexSigma(str[i], afd)];		// Segun caracter y estado actuales, se busca en la delta próximo estado
			q = indexQ(q1, afd);	// Se obtiene indice del nuevo estado
		}

		if (verifyF(q1, afd)) v = 1;
		
		return v;
	}

	
	};

	int main() {
		AFD afd1;
		string str1 = "101000";		// Por hacer: procedimiento para capturar la cadena a ser analizada

		cout << afd1;		// Despliega tabla de transiciones
		
		cout << "\n\n";
		cout << "Cadena de entrada: " << str1;	// muestra la cadena de entrada

		cout << "\n\n";
		cout << "\tCadena ";
		if (afd1.stringVerification(str1, afd1)) cout << "Valida";		//Verifica si la cadena es valida y despliega mensaje "Valida"
		else cout << "Rechazada";		// en caso contrario despliega mensaje "Rechazada"

		cout << "\n\n\n";
		system("pause");
		return 0;
	}