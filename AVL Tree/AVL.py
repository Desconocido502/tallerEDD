from Nodo import Nodo
import os

class AVL():
    root:Nodo

    def __init__(self) -> None:
        self.root = None

    def getAltura(self, temp: Nodo)-> int:
        if(temp != None):
            return temp.alturaN
        return -1

    def max(self, val1:int, val2:int) -> int:
        if(val1 > val2): 
            return val1
        return val2
    
    #*Rotacion simple izquierda
    def srl(self, pivote:Nodo) -> Nodo:
        aux:Nodo = pivote.left
        pivote.left = aux.right
        aux.right = pivote
        pivote.alturaN = self.max(self.getAltura(pivote.left), self.getAltura(pivote.right)) + 1
        aux.alturaN = self.max(self.getAltura(aux.left), pivote.alturaN) + 1
        return aux
    
    #*Rotacion simple derecha
    def srr(self, pivote:Nodo) -> Nodo:
        aux:Nodo  = pivote.right
        pivote.right = aux.left
        aux.left = pivote
        pivote.alturaN = self.max(self.getAltura(pivote.right), self.getAltura(pivote.left)) + 1
        aux.alturaN = self.max(self.getAltura(aux.right), pivote.alturaN) + 1
        return aux
    
    #*Rotacion doble izquierda
    def drl(self, pivote:Nodo) -> Nodo:
        pivote.left = self.srr(pivote.left)
        return self.srl(pivote)
    
    #*Rotacion doble derecha
    def drr(self, pivote:Nodo) -> Nodo:
        pivote.right = self.srl(pivote.right)
        return self.srr(pivote)
    
    def agregar(self, value:int) -> None:
        self.root = self.agregarInterno(self.root, value)
    
    def agregarInterno(self, root:Nodo, value:int):
        if(root == None):
            root = Nodo(value)
        else:
            if(value < root.value):
                root.left = self.agregarInterno(root.left, value)
                if((self.getAltura(root.right) - self.getAltura(root.left)) == -2):
                    if(value < root.left.value):
                        root = self.srl(root)
                    else:
                        root = self.drl(root)
            else:
                if(value > root.value):
                    root.right = self.agregarInterno(root.right, value)
                    if((self.getAltura(root.right) - self.getAltura(root.left)) == 2):
                        if(value > root.right.value):
                            root = self.srr(root)
                        else:
                            root = self.drr(root)
        root.alturaN = self.max(self.getAltura(root.left), self.getAltura(root.right)) + 1
        return root
    
    def buscar(self, value:int) -> bool:
        return self.buscarInterno(self.root, value)

    def buscarInterno(self, pivote:Nodo, value:int) -> bool:
        if(pivote != None):
            if(pivote.value == value):
                return True
            
            if(pivote.left != None):
                return self.buscarInterno(pivote.left, value)
            else:
                return self.buscarInterno(pivote.right, value)
        return False

    def PreOrden(self) -> None:
        self.PreOrdenInterno(self.root)

    def PreOrdenInterno(self, node:Nodo) -> None:
        if(node != None):
            print(node.value, end=" | ")
            self.PreOrdenInterno(node.left)
            self.PreOrdenInterno(node.right)

    def PostOrden(self) -> None:
        self.PostOrdenInterno(self.root)

    def PostOrdenInterno(self, node:Nodo) -> None:
        if(node != None):
            self.PostOrdenInterno(node.left)
            self.PostOrdenInterno(node.right)
            print(node.value, end=" | ")

    def InOrden(self) -> None:
        self.InOrdenInterno(self.root)

    def InOrdenInterno(self, node:Nodo) -> None:
        if(node != None):
            self.InOrdenInterno(node.left)
            print(node.value, end=" | ")
            self.InOrdenInterno(node.right)
    
    def graficar(self):
        nombreEstructura = "AVL"
        file = open(nombreEstructura + ".dot", 'w')
        file.write("digraph G { \nlabel=\"Avl Tree\";\n")
        file.write("rankdir=TB; \n")
        file.write("node [shape = record, color=blue ,style=\"rounded,filled\", fillcolor=gray93];\n")        
        file.write(self.__graficadora(self.root))
        file.write("} \n")
        file.close()
        os.system("dot -Tpng " + nombreEstructura + ".dot -o " + nombreEstructura + ".png")
        #os.system("xdg-open " + nombreEstructura + ".png") # para linux
        os.startfile(nombreEstructura + ".png") # para windows

    def __graficadora(self, root:Nodo):
        cadena = ""
        if(root.right == None) and (root.left == None):
            cadena = "nodo" + str(root.value) + "[label =\"" + str(root.value) + "\"]; \n"
        else:
            cadena = "nodo" + str(root.value) + "[label =\"<C0>| " + str(root.value) + " |<C1> \"]; \n"

        if(root.left != None):
            cadena = cadena + self.__graficadora(root.left)+"nodo"+str(root.value)+":C0->nodo"+str(root.left.value)+"\n"
        if(root.right != None):
            cadena = cadena + self.__graficadora(root.right)+"nodo"+str(root.value)+":C1->nodo"+str(root.right.value)+"\n"

        return cadena