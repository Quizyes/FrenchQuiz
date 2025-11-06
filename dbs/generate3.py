import sqlite3
import json
import re

def acc(str):
    str = re.sub(r'[\"\[\]]', '', str)
    str = re.sub(r'\\u00e7', 'ç', str)
    str = re.sub(r'\\u00e9', 'é', str)
    str = re.sub(r'\\u00e8', 'è', str)
    str = re.sub(r'\\u00ea', 'ê', str)
    str = re.sub(r'\\u00ee', 'î', str)
    str = re.sub(r'\\u00ef', 'ï', str)
    str = re.sub(r'\\u00e2', 'â', str)
    str = re.sub(r'\\u00fb', 'û', str)
    str = re.sub(r' !', '', str)
    return str

con = sqlite3.connect("paradigms.db")
cur = con.cursor()

cur.execute("drop table if exists paradigms;")
cur.execute("create table if not exists paradigms(verbID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "inf TEXT, "
            "pastPart TEXT, "
            "presPart TEXT, "
            "aux TEXT, "
            "pres TEXT, "
            "impf TEXT, "
            "past TEXT, "
            "fut TEXT, "
            "cond TEXT, "
            "subjPres TEXT, "
            "subjImpf TEXT, "
            "imperat TEXT "
            ");");



with open("conjugations.json", "r") as f:
    data = json.load(f)

for verb in data:
    if verb["infinitif"][2] == ' ': # check for reflexives
        continue
    if verb["infinitif"][1] == '\'': # elided reflexives
        continue
    #print(verb["infinitif"])
    inf = verb["infinitif"]
    inf = acc(inf)
    try:
        pres = json.dumps(verb["present"])
        pres = acc(pres)
    except KeyError:
        continue
    presents = pres.split(', ')
    
    try:
        impf = json.dumps(verb["imparfait"])
        impf = acc(impf)
    except KeyError:
        continue
    imperfects = impf.split(', ')
    
    try:
        past = json.dumps(verb["passeSimple"])
        past = acc(past)
    except KeyError:
        continue
    pasts = past.split(', ')
    
    try:
        fut = json.dumps(verb["futurSimple"])
        fut = acc(fut)
    except KeyError:
        continue
    futures = fut.split(', ')

    try:
        cond = json.dumps(verb["conditionnelPresent"])
        cond = acc(cond)
    except KeyError:
        continue
    conditionals = cond.split(', ')

    try:
        subjPres = json.dumps(verb["subjonctifPresent"])
        subjPres = acc(subjPres)
    except KeyError:
        continue
    subjunctivePresents = subjPres.split(', ')
    
    try:
        subjImpf = json.dumps(verb["subjonctifImparfait"])
        subjImpf = acc(subjImpf)
    except KeyError:
        continue
    subjunctiveImperfects = subjImpf.split(', ')

    try:
        pastPart = json.dumps(verb["participePasse"])
        pastPart = acc(pastPart)
    except KeyError:
        continue

    try:
        presPart = json.dumps(verb["participePresent"])
        presPart = acc(presPart)
    except KeyError:
        continue

    try:
        aux = json.dumps(verb["auxiliaire"])
        aux = acc(aux)
    except KeyError:
        continue

    try:
        imperat = json.dumps(verb["imperatif"])
        imperat = acc(imperat)
    except KeyError:
        continue
    
    #for key, value in {"present": presents, "imperfect": imperfects, "passeSimple": passeSimples, "future": futures, "conditional": conditionals, "subjunctivePresent": subjunctivePresents, "subjunctiveImperfect": subjunctiveImperfects}.items():
    
    cur.execute("insert into paradigms (inf, pastPart, presPart, aux, pres, impf, past, fut, cond, subjPres, subjImpf, imperat) values (?,?,?,?,?,?,?,?,?,?,?,?);", (inf, pastPart, presPart, aux, pres, impf, past, fut, cond, subjPres, subjImpf, imperat))


con.commit()
con.close()