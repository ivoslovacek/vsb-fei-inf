import tkinter as tk

import app.data as data
import app.menubar as mb
import app.treeview as tree
import app.notebook as nb


class App:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Trail Manager")
        self.data = data.AppData()
        self.current_trail = self.data.trails[0]

        self.menubar = mb.Menubar(self.root)
        self.notebook = nb.Notebook(self.root, self.current_trail)
        self.treview = tree.Treeview(
            self.root, self.data.trails, self.current_trail,
            self.notebook.details)

        self.treview.container.pack()
        self.notebook.container.pack()

    def run(self):
        self.root.mainloop()
