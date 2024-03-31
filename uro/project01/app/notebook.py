import app.data as data
import tkinter as tk
from tkinter import ttk
import webbrowser


class Notebook:
    def __init__(self, root: tk.Tk, trail: data.TrailData):
        self.root = root
        self.container = tk.Frame(
            self.root, relief="raised", borderwidth=0)
        self.notebook = ttk.Notebook(self.container)

        self.details_frame = tk.Frame(self.notebook)
        self.details = Details(self.details_frame, trail)

        self.input_frame = tk.Frame(self.notebook, padx=5, pady=5)
        self.input = NewTrail(self.input_frame)

        self.notebook.add(self.details_frame, text="Details")
        self.notebook.add(self.input_frame, text="New trail")

        self.notebook.pack(pady=5, expand=True, fill="both")


class Details:
    def __init__(self, root: tk.Misc, trail: data.TrailData):
        self.root = root
        self.container = tk.Frame(self.root, borderwidth=0)

        self.start = tk.Label(
            self.container, text=f"Start: {trail.start}", padx=10, pady=5)
        self.start.grid(row=0, column=0)

        self.end = tk.Label(
            self.container, text=f"End: {trail.end}", padx=10, pady=5)
        self.end.grid(row=0, column=1)

        self.distance = tk.Label(
            self.container, text=f"Distance: {trail.distance}km",
            padx=10, pady=5)
        self.distance.grid(row=1, column=0)

        self.difficulty = tk.Label(
            self.container, text=f"Difficulty: {trail.difficulty}",
            padx=10, pady=5)
        self.difficulty.grid(row=1, column=1)

        self.ascent = tk.Label(
            self.container, text=f"Ascent: {trail.ascent}m",
            padx=10, pady=5)
        self.ascent.grid(row=2, column=0)

        self.descent = tk.Label(
            self.container, text=f"Descent: {trail.descent}m",
            padx=10, pady=5)
        self.descent.grid(row=2, column=1)

        self.rating = tk.Label(
            self.container, text=f"Rating: {trail.rating}\u2605",
            padx=10, pady=5)
        self.rating.grid(row=3, column=0)

        self.link = tk.Button(
            self.container, text="Route", padx=10, pady=5,
            command=lambda: webbrowser.open_new_tab(trail.link))
        self.link.grid(row=3, column=1)

        self.container.pack(pady=5, padx=5)

    def update(self, trail):
        self.start.config(text=f"Start: {trail.start}")
        self.end.config(text=f"End: {trail.end}")
        self.distance.config(text=f"Distance: {trail.distance}km")
        self.difficulty.config(text=f"Difficulty: {trail.difficulty}")
        self.ascent.config(text=f"Ascent: {trail.ascent}m")
        self.descent.config(text=f"Descent: {trail.descent}m")
        self.rating.config(text=f"Rating: {trail.rating}\u2605")
        self.link.config(
            command=lambda: webbrowser.open_new_tab(trail.link))

        self.container.update_idletasks()


class NewTrail:
    def __init__(self, root: tk.Misc):
        self.container = root

        self.start_label = tk.Label(
            self.container, text="Start: ", padx=5, pady=5)
        self.start_label.grid(row=0, column=0, sticky="E")
        self.start_entry = tk.Entry(self.container, width=10)
        self.start_entry.grid(row=0, column=1, sticky="W")

        self.end_label = tk.Label(
            self.container, text="End: ", padx=5, pady=5)
        self.end_label.grid(row=0, column=2, sticky="E")
        self.end_entry = tk.Entry(self.container, width=10)
        self.end_entry.grid(row=0, column=3, sticky="W")

        self.start_label = tk.Label(
            self.container, text="Distance: ", padx=5, pady=5)
        self.start_label.grid(row=1, column=0, sticky="E")
        self.start_entry = tk.Entry(self.container, width=5)
        self.start_entry.grid(row=1, column=1, sticky="W")

        self.end_label = tk.Label(
            self.container, text="Difficulty: ", padx=5, pady=5)
        self.end_label.grid(row=1, column=2, sticky="E")
        self.end_entry = tk.Entry(self.container, width=2)
        self.end_entry.grid(row=1, column=3, sticky="W")

        self.start_label = tk.Label(
            self.container, text="Ascent: ", padx=5, pady=5)
        self.start_label.grid(row=2, column=0, sticky="E")
        self.start_entry = tk.Entry(self.container, width=5)
        self.start_entry.grid(row=2, column=1, sticky="W")

        self.end_label = tk.Label(
            self.container, text="Descent: ", padx=5, pady=5)
        self.end_label.grid(row=2, column=2, sticky="E")
        self.end_entry = tk.Entry(self.container, width=5)
        self.end_entry.grid(row=2, column=3, sticky="W")

        self.start_label = tk.Label(
            self.container, text="Rating: ", padx=5, pady=5)
        self.start_label.grid(row=3, column=0, sticky="E")
        self.start_entry = tk.Entry(self.container, width=2)
        self.start_entry.grid(row=3, column=1, sticky="W")

        self.end_label = tk.Label(
            self.container, text="Route link: ", padx=5, pady=5)
        self.end_label.grid(row=3, column=2, sticky="E")
        self.end_entry = tk.Entry(self.container, width=10)
        self.end_entry.grid(row=3, column=3, sticky="W")

        self.create_button = tk.Button(self.container, text="Create Trail")
        self.create_button.grid(row=4, column=1, columnspan=2)

        self.container.pack()
