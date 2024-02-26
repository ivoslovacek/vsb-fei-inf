import tkinter as tk


def nice():
    print("lasndfkas")


top = tk.Tk()

button = tk.Button(top, text="XD", command=top.destroy)
button.pack(side="left")

button2 = tk.Button(top, text="XD", command=nice)
button2.pack(side="right")

button3 = tk.Button(top, text="proč")
button3.pack()

tk.mainloop()
