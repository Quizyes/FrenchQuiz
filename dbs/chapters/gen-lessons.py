import sqlite3
import re


con = sqlite3.connect("paradigms.db")
cur = con.cursor()
            
with open("chapters/01.txt", "r") as f:
    for line in f:
        line = line.strip()
        cur.execute("update paradigms set lesson = ? where inf = ?;", (1, line))


con.commit()
con.close()