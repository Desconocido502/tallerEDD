
#* Función para calcular el factorial de un número
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

if __name__ == "__main__":
    #* Ejemplo de uso
    numero = 5
    resultado = factorial(numero)
    print("Factorial de", numero, "es: ", resultado)
