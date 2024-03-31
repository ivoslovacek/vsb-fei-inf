import tkinter as tk


class Filters:
    def __init__(self, root: tk.Tk):
        self.root = root
        self.container = tk.Frame(self.root, relief="groove", borderwidth=2)

        self.container.grid()
