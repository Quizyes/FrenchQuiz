import sqlite3
import re


con = sqlite3.connect("paradigms.db")
cur = con.cursor()
            
with open("chapters/01.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (1, line))

with open("chapters/02.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (2, line))

with open("chapters/03.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (3, line))

with open("chapters/04.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (4, line))

with open("chapters/05.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (5, line))

with open("chapters/06.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (6, line))

con.commit()
con.close()




rcon = sqlite3.connect("recognitions.db")
rcur = rcon.cursor()
            
with open("chapters/01.txt", "r") as f:
    for line in f:
        line = line.strip()
        rcur.execute("update recogs set lesson = ? where head = ?;", (1, line))

with open("chapters/02.txt", "r") as f:
    for line in f:
        line = line.strip()
        rcur.execute("update recogs set lesson = ? where head = ?;", (2, line))

with open("chapters/03.txt", "r") as f:
    for line in f:
        line = line.strip()
        rcur.execute("update recogs set lesson = ? where head = ?;", (3, line))

with open("chapters/04.txt", "r") as f:
    for line in f:
        line = line.strip()
        rcur.execute("update recogs set lesson = ? where head = ?;", (4, line))

with open("chapters/05.txt", "r") as f:
    for line in f:
        line = line.strip()
        rcur.execute("update recogs set lesson = ? where head = ?;", (5, line))

with open("chapters/06.txt", "r") as f:
    for line in f:
        line = line.strip()
        rcur.execute("update recogs set lesson = ? where head = ?;", (6, line))

rcon.commit()
rcon.close()