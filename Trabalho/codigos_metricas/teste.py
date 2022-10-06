#!/usr/bin/python3

import os
import numpy as np
import pandas as pd

compilacao = "gcc recursivo_paralelo.c -O3 -fopenmp -o programa"
topologia = "likwid-topology > topologia.out"
entradas = ['11','12','13']
numThreads = ['1']
numExec = 2

print("##Gerando topologia.out##\n")
os.system(topologia)

print("##Compilando programa paralelo##\n")
os.system(compilacao)
print("##Fim compilacao##\n")

print("##Gerando dados de execucao\n")
for i in entradas:
    for x in range(numExec):
        for n in numThreads:
            os.system("./programa " + str(i) + " " + str(n) +" >> saidaExec" + "_" + str(n)+ ".out ")

print("##Fim da geracao dos dados de execucao##\n")

columns=['nRainhas', 'Tseq_mean', 'Tseq_std', 'Tpar_mean','Tpar_std', 'Ttot_mean', 'Ttot_std','threads']
rows = []

for n in numThreads:
    myarray = np.loadtxt("saidaExec" + "_" + str(n) + ".out",usecols=range(0,4))
    df = pd.DataFrame(myarray)
    df['Num Threads'] = str(n)
    df.columns = ['Rainhas','TempoSequencial','TempoParalelo', 'TempoTotal','Threads']
    tmpSeq_group = df['TempoSequencial'].groupby(df['Rainhas'])
    tmpPar_group = df['TempoParalelo'].groupby(df['Rainhas'])
    tmpTot_group = df['TempoTotal'].groupby(df['Rainhas'])
        
    for i in entradas:
        # [Rainhas,tSeq_media,tSeq_despadrao,tPar_media,tPar_despadrao,tTot_media,tTot_despadrao,numThreads]
        row = [int(i),tmpSeq_group.get_group(int(i)).mean(),tmpSeq_group.get_group(int(i)).std(),tmpPar_group.get_group(int(i)).mean(),tmpPar_group.get_group(int(i)).std(),tmpTot_group.get_group(int(i)).mean(),tmpTot_group.get_group(int(i)).std(),n]
        rows.append(row)

df1 = pd.DataFrame(rows,columns =columns)     
df1.to_csv("saida.csv", sep=';', encoding = 'utf-8')
    