from Node import Node
import os

class BST():
    root: Node

    def __init__(self) -> None:
        self.root = None

    def is_empty(self):
        return self.root == None

    def agregar(self, id):
        self.root = self.__agregarInterno(id, self.root)
    
    def __agregarInterno(self, id:int, root:Node):
        if(root == None):
            return Node(id)
        else:
            if(id < root.id):
                root.left = self.__agregarInterno(id, root.left)
            elif(id > root.id):
                root.right = self.__agregarInterno(id, root.right)
        return root
    
    def preOrden(self):
        self.__preOrdenInterno(self.root)
        print("")

    def __preOrdenInterno(self, root:Node):
        if (root != None):
            print("\033[0;32m",root.id, "\033[0m", end=" | ")
            self.__preOrdenInterno(root.left)
            self.__preOrdenInterno(root.right)
    
    def postOrden(self):
        self.__postOrdenInterno(self.root)
        print("")
        
    def __postOrdenInterno(self, root:Node):
        if (root != None):
            self.__postOrdenInterno(root.left)
            self.__postOrdenInterno(root.right)
            print("\033[0;35m", root.id, "\033[0m", end=" | ")
    
    def InOrden(self):
        self.__inOrdenInterno(self.root)
        print("")

    def __inOrdenInterno(self, root:Node):
        if (root != None):
            self.__inOrdenInterno(root.left)
            print("\033[0;36m",root.id, "\033[0m", end=" | ")
            self.__inOrdenInterno(root.right)
    
    def buscar(self, id:int):
        if(self.__buscarInterno(id, self.root) == None):
            print("\n\033[34mNo se encontro el nodo\033[0m")
        else:
            print("\n\033[33mSe encontro el nodo\033[0m")
    
    def __buscarInterno(self, id:int, root:Node):
        if(root == None or root.id == id):
            return root
        elif (id < root.id):
            return self.__buscarInterno(id, root.left)
        else:
            return self.__buscarInterno(id, root.right)
    
    def graficar(self):
        nombreEstructura = "BST"
        file = open(nombreEstructura + ".dot", 'w')
        file.write("digraph G { \nlabel=\"B Tree\";\n")
        file.write("rankdir=TB; \n")
        file.write("node [shape = record, color=blue ,style=\"rounded,filled\", fillcolor=gray93];\n")
        file.write(self.__graficadora(self.root))
        file.write("} \n")
        file.close()
        os.system("dot -Tpng " + nombreEstructura + ".dot -o " + nombreEstructura + ".png")
        #os.system("xdg-open " + nombreEstructura + ".png") # para linux
        #os.startfile(nombreEstructura + ".png") # para windows

    def __graficadora(self, root:Node):
        cadena = ""
        if(root.right == None) and (root.left == None):
            cadena = "Node" + str(root.id) + "[label =\"" + str(root.id) + "\"]; \n"
        else:
            cadena = "Node" + str(root.id) + "[label =\"<C0>| " + str(root.id) + " |<C1> \"]; \n"

        if(root.left != None):
            cadena = cadena + self.__graficadora(root.left)+"Node"+str(root.id)+":C0->Node"+str(root.left.id)+"\n"
        if(root.right != None):
            cadena = cadena + self.__graficadora(root.right)+"Node"+str(root.id)+":C1->Node"+str(root.right.id)+"\n"

        return cadena