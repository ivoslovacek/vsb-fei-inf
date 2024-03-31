import tkinter as tk
from tkinter import messagebox


class Menubar:
    def __init__(self, root: tk.Tk):
        self.root = root
        self.menubar = tk.Menu(self.root)

        self.fileMenu = tk.Menu(self.menubar, tearoff=0)
        self.fileMenu.add_command(label="Quit", command=self.root.destroy)

        self.menubar.add_cascade(label="File", menu=self.fileMenu)
        self.menubar.add_command(label="Help")
        self.menubar.add_command(label="Info", command=self.info)

        root.config(menu=self.menubar)

    def info(self):
        messagebox.showinfo(
            "Info", "Trail manger lets you store basic\n" +
            "information about hiking trails\n© Ivo Slováček 2024")
