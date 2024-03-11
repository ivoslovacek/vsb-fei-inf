import tkinter as tk


class App:
    def __init__(self, name: str):
        self.root = tk.Tk()
        self.root.title(name)
        # used_conversion: 1 - c -> f, 2 f -> c
        self.used_conversion = tk.IntVar()
        self.input = tk.StringVar()
        self.output = tk.StringVar()
        self.image = tk.PhotoImage(file="th_empty.png")

        self.used_conversion.set(1)

    def unit_selectors(self):
        unit_box = tk.LabelFrame(self.root, relief="groove",
                                 borderwidth=2, text="Směr převodu")

        btn1 = tk.Radiobutton(unit_box, text="C -> F",
                              variable=self.used_conversion, value=1, pady=5,
                              anchor=tk.CENTER)
        btn1.pack(side="left")

        btn2 = tk.Radiobutton(unit_box, text="F -> C",
                              variable=self.used_conversion, value=2, pady=5,
                              anchor=tk.CENTER)
        btn2.pack(side="right")

        unit_box.grid(column=0, row=0, padx=5, pady=5, sticky="ewn")

    def input_fields(self):
        def on_convert(self):
            try:
                if self.used_conversion.get() == 1:
                    tmp = ((9 * float(self.input.get())/5.0)+32)
                    self.output.set(f"{tmp}")
                elif self.used_conversion.get() == 2:
                    tmp = ((int(self.input.get()) - 32) * 5) / 9.0
                    self.output.set(f"{tmp}")
            except ValueError:
                print("String containing letters was entered for conversion")

        input_box = tk.Frame(self.root, relief="groove",
                             borderwidth=2)

        entry1label = tk.Label(input_box, text="Input", padx=5, pady=5)
        entry1label.pack()

        entry1 = tk.Entry(input_box, textvariable=self.input)
        entry1.pack()

        entry2label = tk.Label(input_box, text="Output", padx=5, pady=5)
        entry2label.pack()

        entry2 = tk.Entry(input_box, textvariable=self.output)
        entry2.pack()

        btn = tk.Button(input_box, text="Convert",
                        anchor=tk.CENTER, command=lambda: on_convert(self))
        btn.pack(side="bottom", pady=5)

        input_box.grid(column=0, row=1, padx=5, pady=5, sticky="ewns")

    def image_field(self):
        image_box = tk.Frame(self.root, relief="groove", borderwidth=2)
        image_box.grid(column=1, row=0, rowspan=2, padx=5, pady=5)

        canvas = tk.Canvas(image_box)
        canvas.pack(fill="both", expand=True)

        canvas.config(width=self.image.width(), height=self.image.height())
        canvas.create_image(0, 0, anchor="nw", image=self.image)

    def run(self):
        self.input_fields()
        self.unit_selectors()
        self.image_field()
        self.root.rowconfigure(0, weight=0)
        self.root.rowconfigure(1, weight=3)
        self.root.mainloop()


if __name__ == '__main__':
    app = App('Ivo Slováček : SLO0168')
    app.run()
