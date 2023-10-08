class Node():
    id: int

    def __init__(self, id) -> None:
        self.id = id
        self.left:Node = None
        self.right:Node = None