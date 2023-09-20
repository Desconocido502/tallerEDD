class Nodo():
    value: int
    alturaN: int

    def __init__(self, value) -> None:
        self.value = value
        self.left = None
        self.right = None
        self.alturaN = 0