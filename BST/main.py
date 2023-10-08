from BST import BST

if __name__ == "__main__":
    bst = BST()

    bst.agregar(45)
    bst.agregar(23)
    bst.agregar(2)
    bst.agregar(65)
    bst.agregar(38)
    bst.agregar(7)
    bst.agregar(52)
    bst.agregar(96)
    bst.agregar(48)
    bst.graficar()
    print("\n\033[32mPreOrden:\033[0m")
    bst.preOrden()
    print("\n\033[35mPostOrden:\033[0m")
    bst.postOrden()
    print("\n\033[36mInOrden:\033[0m")
    bst.InOrden()
    print("\n\033[31mSearch:\033[0m")
    bst.buscar(45)
    bst.buscar(99)