#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>

using namespace std;

bool esPalabraClave(const char* str) {
    const char* palabrasClave[] = { "if", "else", "while", "return", "cout", "endl" };
    for (const char* palabra : palabrasClave) {
        if (strcmp(str, palabra) == 0) {
            return true;
        }
    }
    return false;
}

bool esTipo(const char* str) {
    const char* tipo[] = { "int", "float", "void" };
    for (const char* palabra : tipo) {
        if (strcmp(str, palabra) == 0) {
            return true;
        }
    }
    return false;
}

bool contieneLetras(const char* texto) {
    int longitud = strlen(texto);
    for (int i = 0; i < longitud; i++) {
        if (isalpha(texto[i])) {
            return true; // El texto contiene al menos una letra
        }
    }
    return false; // El texto no contiene letras
}

bool contienePuntos(const char* texto) {
    int longitud = strlen(texto);
    int puntos = 0;
    for (int i = 0; i < longitud; i++) {
        if (texto[i] == '.') {
            puntos++;
            if (puntos > 1) {
                return true; // El texto contiene al menos un punto
            }
        }
    }
    return false; // El texto no contiene puntos
}

bool esNumero(const char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool esNumeroDecimal(const char* str) {
    int len = strlen(str);
    int puntosDecimales = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            puntosDecimales++;
            if (puntosDecimales > 1) {
                return false;
            }
        } else if (!isdigit(str[i]) && (i != 0 || str[i] != '-')) {
            return false;
        }
    }
    return puntosDecimales == 1;
}

bool esCadenaTexto(const char* str) {
    int len = strlen(str);
    return len >= 2 && str[0] == '"' && str[len - 1] == '"';
}

void imprimirTabla(const char* elemento, const char* tipo, const char* numTipo) {
    const int anchoElemento = 25;
    const int anchoTipo = 20;
    const int anchoNumTipo = 25;

    cout << left << setw(anchoElemento) << elemento << " => " << setw(anchoTipo) << tipo << setw(anchoNumTipo) << numTipo << endl;
}

void analizar(const char* str) {
    int len = strlen(str);
    int i = 0;

    while (i < len) {
        // Ignorar espacios en blanco
        while (i < len && isspace(str[i])) {
            i++;
        }

        // Verificar si es una cadena de texto
        if (str[i] == '"') {
            int j = i + 1;
            while (j < len && str[j] != '"') {
                j++;
            }
            if (j < len) {
                char cadenaTexto[1000];
                strncpy(cadenaTexto, &str[i], j - i + 1);
                cadenaTexto[j - i + 1] = '\0';
                if (esCadenaTexto(cadenaTexto)) {
                    imprimirTabla(cadenaTexto, "Cadena de Texto", "3");
                } else {
                    imprimirTabla(cadenaTexto, "Error: Cadena no válida", "ERROR");
                }
                i = j + 1;
            } else {
                imprimirTabla("\"", "Error: Cadena no cerrada", "ERROR");
                i++;
            }
        }

        // Verificar si es un operador
        else if (str[i] == '+') {
            imprimirTabla("+", "Operador de Adición", "5");
            i++;
        } else if (str[i] == '-') {
            imprimirTabla("-", "Operador de Sustracción", "5");
            i++;
        } else if (str[i] == '*') {
            imprimirTabla("*", "Operador de Multiplicación", "6");
            i++;
        } else if (str[i] == '/') {
            imprimirTabla("/", "Operador de División", "6");
            i++;
        } else if (str[i] == '=') {
            if (i + 1 < len && str[i + 1] == '=') {
                imprimirTabla("==", "Operador Relacional", "11");
                i += 2;
            } else {
                imprimirTabla("=", "Operador de Asignación", "18");
                i++;
            }
        } else if (str[i] == '<' && i + 1 < len && str[i + 1] == '<') {
            imprimirTabla("<<", "Operador de Inserción", "26");
            i += 2;
        } else if (str[i] == '>' && i + 1 < len && str[i + 1] == '>') { //> int main <
            imprimirTabla(">>", "Operador de Extracción", "27");
            i += 2;
        } else if (str[i] == '<' || str[i] == '>' || (i + 1 < len && (str[i] == '=' || (str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|') || str[i] == '!'))) {
            if (str[i] == '<') {
                imprimirTabla("<", "Operador Relacional", "7");
                i++;
            } else if (str[i] == '>') {
                imprimirTabla(">", "Operador Relacional", "7");
                i++;
            } else if (str[i] == '<') {
                imprimirTabla("<<", "Operador Relacional", "26");
                i += 2;
            } else if (str[i] == '>') {
                imprimirTabla(">>", "Operador Relacional", "27");
                i += 2;
            } else if (str[i] == '=') {
                imprimirTabla("==", "Operador Relacional", "11");
                i += 2;
            } else if (str[i] == '&' && str[i + 1] == '&') {
                imprimirTabla("&&", "Operador Lógico AND", "9");
                i += 2;
            } else if (str[i] == '|' && str[i + 1] == '|') {
                imprimirTabla("||", "Operador Lógico OR", "8");
                i += 2;
            } else if (str[i] == '!') {
                imprimirTabla("!", "Operador Lógico NOT", "10");
                i++;
            }
        }


        // Verificar si es un símbolo
        else if (str[i] == '(') {
            imprimirTabla("(", "Símbolo (Paréntesis)", "14");
            i++;
        } else if (str[i] == ')') {
            imprimirTabla(")", "Símbolo (Paréntesis)", "15");
            i++;
        } else if (str[i] == '{') {
            imprimirTabla("{", "Símbolo (Llave)", "16");
            i++;
        } else if (str[i] == '}') {
            imprimirTabla("}", "Símbolo (Llave)", "17");
            i++;
        } else if (str[i] == '[') {
            imprimirTabla("[", "Símbolo (Corchete)", "24");
            i++;
        } else if (str[i] == ']') {
            imprimirTabla("]", "Símbolo (Corchete)", "25");
            i++;
        } else if (str[i] == ';') {
            imprimirTabla(";", "Símbolo (Punto y Coma)", "12");
            i++;
        }
        else if (str[i] == ',') {
            imprimirTabla(",", "Coma", "13");
            i++;
        }
        // Verificar si es una palabra clave o identificador y verifica los números
        else if (isalpha(str[i]) || str[i] == '_' || isdigit(str[i]) || isdigit(str[i]) || str[i] == '-' || str[i] == '.') {
            int j = i;
            while (j < len && (isalnum(str[j]) || str[j] == '_' || str[j] == '.')) {
                j++;
            }
            char palabra[100];
            strncpy(palabra, &str[i], j - i);
            palabra[j - i] = '\0';
            if (esPalabraClave(palabra)) {
                imprimirTabla(palabra, "Palabra Clave", "CAMBIAR");
            }
            else if (esTipo(palabra)) {
                imprimirTabla(palabra, "Tipo de dato", "4");
            }
            else {
                if (!palabra[0] == '\0' && isdigit(palabra[0]) || esNumeroDecimal(palabra) || contienePuntos(palabra)) {
                    if (contieneLetras(palabra)) {
                        imprimirTabla(palabra, "Identificador no valido", "ERROR");
                    }
                }
                else {
                    imprimirTabla(palabra, "Identificador", "0");
                }
            if (esNumero(palabra)) {
                imprimirTabla(palabra, "Número Entero", "1");
            }
            else if (esNumeroDecimal(palabra)) {
                imprimirTabla(palabra, "Número Decimal", "2");
            }
            else if (contienePuntos(palabra)){
                imprimirTabla(palabra, "ERROR.", "ERROR");
            }
            }
            i = j;
        }
        else {
            i++;
        }
    }
}

int main() {
    char codigo[1000];

    cout << "-ANALIZADOR LEXICO-" << endl;
    cout << "Línea a analizar: ";
    cin.getline(codigo, sizeof(codigo));

    cout << setw(25) << "Elemento" << " => " << setw(20) << "Tipo de Token" << setw(25) << "#" << endl;
    cout << "---------------------------------------------------------" << endl;

    analizar(codigo);

    cout << "\n\n\n";
    return 0;
}

// codigo de prueba para el analizador:
// if (a==b) { cout "hola"; }
// if (a == b) {     cout << "Hola, mundo!" << endl;     int x = 10;     float y = 3.14; }
