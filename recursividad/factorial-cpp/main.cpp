#include <iostream>
using namespace std;

// Función para calcular el factorial de un número
int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Ejemplo de uso
int main() {
    int numero = 5;
    int resultado = factorial(numero);
    cout << "Factorial de " << numero << " es: " << resultado << endl;

    return 0;
}