class LinkedList:
    class Node:
        def __init__(self, data):
            self.data = data
            self.next = None

    def __init__(self):
        self.head = None

    def list_empty(self):
        return self.head is None

    def insert_first(self, value):
        node = self.Node(value)
        node.next = self.head
        self.head = node

    def insert_after(self, pred_value, value):
        pred = self.head
        while pred is not None and pred.data != pred_value:
            pred = pred.next
        if pred is None:
            raise ValueError(f"Predecessor value {pred_value} not found in list")
        node = self.Node(value)
        node.next = pred.next
        pred.next = node

def print_list(linked_list):
    current = linked_list.head
    elements = []
    while current:
        elements.append(str(current.data))
        current = current.next
    print(" -> ".join(elements) if elements else "")

# Instantiate the LinkedList
my_list = LinkedList()
my_list.insert_first(3)
my_list.insert_first(5)
my_list.insert_first(7)
print_list(my_list)