import networkx as nx
import random as rand
import sys

filiais_list = []
dirname = "./graphs/graph_"

def gen_fil(N, F):
	global filiais_list
	for i in range(0, F):
		r = rand.randint(1, N)	
		filiais_list = filiais_list + [r]

def gen(N):
	global filiais_list
	for out in range(0, N):
		i = rand.randint(2, 3000)
		print "Generating Graph Number: " + str(out+1) + "/" + str(N) + "   Size(nodes): " + str(i)
		filiais = rand.randint(1, i)
		G=nx.binomial_graph(i, 0.5, True)

		for n in range(0, i):
			for e in G[n]:				
				r = rand.randint(1, 10)
				G[n][e] = r

		gen_fil(i, filiais)
		f = open(dirname + str(out), "w")
		f.write(str(i) + " " + str(filiais) + " " + str(len(G.edges())) + "\n")		 

		counter = 0

		for a in filiais_list:
			if counter < len(filiais_list):
				f.write(str(a) + " ")
			else:
				f.write(str(a))
			counter = counter + 1
		f.write("\n")
		for e in G.edges():
			f.write(str(e[0]+1) + " " + str(e[1]+1) + " " + str(G[e[0]][e[1]]) + "\n")
		f.close()
		filiais_list = []
		
gen(int(sys.argv[1]))

#1000 -> 1,5s
#2000 -> 4.8s
#3000 -> 10,5s
#4000 -> 18,9s
#5000 -> 28,9s
#10000 -> 166,7s
