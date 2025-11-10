import sqlite3
import json
import re

con = sqlite3.connect("paradigms.db")
cur = con.cursor()

# CREATE TABLE paradigms(
# inf TEXT, ... , english TEXT

with open("words-by-chapter.txt", "r") as f:
    for line in f:
        [inf, eng] = line.split("|")
        inf = inf.strip()
        eng = eng.strip()
        print("{}\t{}".format(eng, inf))
        cur.execute("update paradigms set english = ? where inf = ?", [eng, inf])

con.commit()
con.close()