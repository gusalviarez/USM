"""
  Programa que muestra los numeros primos entre un intervalor de numeros,
   en este caso entre 500 y 1000.

  el for recorre todos los numeros entre 500 y 1000 y la funcion evalua
  si el numero es primo o no, si es primo lo imprime.

  elaborado por Jesus Villegas

  Rev mar 2024
"""

def es_primo(numero):

  if numero <= 1:
    return False
  for i in range(2, numero):
    if numero % i == 0:
      return False
  return True

print("Números primos entre 500 y 1000:")
for numero in range(500, 1001):
  if es_primo(numero):
    print(numero, end=" ")