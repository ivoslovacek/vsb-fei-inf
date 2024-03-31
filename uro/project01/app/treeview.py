import tkinter as tk
from tkinter import ttk

import app.data as data
import app.notebook as nb


class Treeview:
    def __init__(self, root: tk.Tk, trails: [data.TrailData],
                 current_trail: data.TrailData, details: nb.Details):
        self.root = root
        self.current_trail = current_trail
        self.trail_id = {}
        self.details = details
        self.container = tk.Frame(self.root, relief="flat", borderwidth=2)
        self.tree = ttk.Treeview(self.container, columns=(
            "Start", "End", "Distance", "Difficulty"), show="headings")

        self.tree.heading("Start", text="Start")
        self.tree.heading("End", text="Finish")
        self.tree.heading("Distance", text="Total distance")
        self.tree.heading("Difficulty", text="Trail difficulty")

        for trail in trails:
            item_id = self.tree.insert("", tk.END, values=(
                trail.start, trail.end, f"{trail.distance}km",
                trail.difficulty))

            self.trail_id[item_id] = trail

        self.tree.bind("<<TreeviewSelect>>", self.on_select)
        self.tree.grid(row=0, column=0, sticky="nsew")

        self.scrollbar = ttk.Scrollbar(
            self.container, orient=tk.VERTICAL, command=self.tree.yview)

        self.tree.configure(yscrollcommand=self.scrollbar.set)
        self.scrollbar.grid(row=0, column=1, sticky="ns")

    def on_select(self, event):
        selected_item = self.tree.selection()

        if selected_item:
            current_trail = self.trail_id.get(selected_item[0])

        self.details.update(current_trail)
