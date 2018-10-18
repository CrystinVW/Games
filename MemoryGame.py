from tkinter import *
import random
import time
count = []
start_time = time.time()
total_time = 1.85
answer_time = 5
numbers = 15

def change_color():
    '''
    current_color = box.cget("background")
    next_color = "green" if current_color == "red" else "red"
    box.config(background=next_color)
    root.after(1000, change_color)
    '''
    box = Text(root, height=2, width=30)

    box.pack()
    number = random.randint(30, 300)
    box.insert(END, str(number))

    box.config(bg='navy', fg='white', bd=8)
    count.append(number)
    if time.time() - start_time < total_time:
        root.after(int((1 / (numbers / total_time))*1000), change_color)
    else:
        root.destroy()
        time.sleep(answer_time)
        print("Total", sum(count))


root = Tk()

change_color()
root.mainloop()
