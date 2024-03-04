import tkinter as tk

root = tk.Tk()

btn1 = tk.Button(root, text='xd')
btn2 = tk.Button(root, text='xd')
btn3 = tk.Button(root, text='nice')

btn1.grid(column=0, row=0, columnspan=2)
btn2.grid(column=1, row=1)
btn3.grid(column=0, row=1, rowspan=2)

root.mainloop()
