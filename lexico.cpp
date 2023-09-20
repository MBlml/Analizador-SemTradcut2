#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>

using namespace std;

bool esPalabraClave(const char* str) {
    const char* palabrasClave[] = { "if", "else", "while", "return", "int", "void", "float", "cout", "endl" };
    for (const char* palabra : palabrasClave) {
        if (strcmp(str, palabra) == 0) {
            return true;
        }
    }
    return false;
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

void imprimirTabla(const char* elemento, const char* tipo) {
    const int anchoElemento = 25;
    const int anchoTipo = 20;

    cout << left << setw(anchoElemento) << elemento << " => " << setw(anchoTipo) << tipo << endl;
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
                    imprimirTabla(cadenaTexto, "Cadena de Texto");
                } else {
                    imprimirTabla(cadenaTexto, "Error: Cadena no válida");
                }
                i = j + 1;
            } else {
                imprimirTabla("\"", "Error: Cadena no cerrada");
                i++;
            }
        }
        
        // Verificar si es un operador
        else if (str[i] == '+' || str[i] == '-') {
            imprimirTabla("+", "Operador de Adición");
            i++;
        } else if (str[i] == '*' || str[i] == '/') {
            imprimirTabla("*", "Operador de Multiplicación");
            i++;
        } else if (str[i] == '=') {
            if (i + 1 < len && str[i + 1] == '=') {
                imprimirTabla("==", "Operador Relacional");
                i += 2;
            } else {
                imprimirTabla("=", "Operador de Asignación");
                i++;
            }
        } else if (str[i] == '<' && i + 1 < len && str[i + 1] == '<') {
            imprimirTabla("<<", "Operador de Inserción");
            i += 2;
        } else if (str[i] == '<' || str[i] == '>' || (i + 1 < len && (str[i] == '=' || (str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|') || str[i] == '!'))) {
            if (str[i] == '<' || str[i] == '>') {
                imprimirTabla(&str[i], "Operador Relacional");
                i++;
            } else if (str[i] == '=') {
                imprimirTabla("==", "Operador Relacional");
                i += 2;
            } else if (str[i] == '&' && str[i + 1] == '&') {
                imprimirTabla("&&", "Operador Lógico AND");
                i += 2;
            } else if (str[i] == '|' && str[i + 1] == '|') {
                imprimirTabla("||", "Operador Lógico OR");
                i += 2;
            } else if (str[i] == '!') {
                imprimirTabla("!", "Operador Lógico NOT");
                i++;
            }
        }


        // Verificar si es un símbolo
        else if (str[i] == '(') {
            imprimirTabla("(", "Símbolo (Paréntesis)");
            i++;
        } else if (str[i] == ')') {
            imprimirTabla(")", "Símbolo (Paréntesis)");
            i++;
        } else if (str[i] == '{') {
            imprimirTabla("{", "Símbolo (Llave)");
            i++;
        } else if (str[i] == '}') {
            imprimirTabla("}", "Símbolo (Llave)");
            i++;
        } else if (str[i] == '[') {
            imprimirTabla("[", "Símbolo (Corchete)");
            i++;
        } else if (str[i] == ']') {
            imprimirTabla("]", "Símbolo (Corchete)");
            i++;
        } else if (str[i] == ';') {
            imprimirTabla(";", "Símbolo (Punto y Coma)");
            i++;
        }
        // Verificar si es una palabra clave o identificador
        else if (isalpha(str[i]) || str[i] == '_') {
            int j = i;
            while (j < len && (isalnum(str[j]) || str[j] == '_')) {
                j++;
            }
            char palabra[100];
            strncpy(palabra, &str[i], j - i);
            palabra[j - i] = '\0';
            if (esPalabraClave(palabra)) {
                imprimirTabla(palabra, "Palabra Clave");
            } else {
                imprimirTabla(palabra, "Identificador");
            }
            i = j;
        }
        // Verificar si es un número
        else if (isdigit(str[i]) || str[i] == '-' || str[i] == '.') {
            int j = i;
            while (j < len && (isdigit(str[j]) || str[j] == '.')) {
                j++;
            }
            char numero[100];
            strncpy(numero, &str[i], j - i);
            numero[j - i] = '\0';
            if (esNumero(numero)) {
                imprimirTabla(numero, "Número Entero");
            } else if (esNumeroDecimal(numero)) {
                imprimirTabla(numero, "Número Decimal");
            }
            i = j;
        } else {
            // Carácter no reconocido, avanzar al siguiente
            i++;
        }
    }
}

int main() {
    char codigo[1000];

    cout << "-ANALIZADOR LEXICO-" << endl;
    cout << "Línea a analizar: ";
    cin.getline(codigo, sizeof(codigo));

    cout << setw(25) << "Elemento" << " => " << setw(20) << "Tipo de Token" << endl;
    cout << "---------------------------------------------------------" << endl;

    analizar(codigo);

    cout << "\n\n\n";
    return 0;
}

// codigo de prueba para el analizador:
// if (a==b) { cout "hola"; }
// if (a == b) {     cout << "Hola, mundo!" << endl;     int x = 10;     float y = 3.14; } 