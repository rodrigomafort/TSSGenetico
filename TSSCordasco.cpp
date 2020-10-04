#include "LocalLib.h"
#include "TSSCordasco.h"

TSSCordasco::TSSCordasco(Grafo* pG, VetorRequisitos pR): R(pR)
{
	G = new Grafo(pG);
	n = G->N();
}

double calcularAvaliacao(double k, double delta)
{
	return k / (delta * (delta + 1));
}

set<Vertice> TSSCordasco::Executar()
{
	set<Vertice> S;
	set<Vertice> U(G->Vertices.begin(), G->Vertices.end());
	int n = G->N();

	//Variáveis do Algoritmo
	int delta[n];
	int k[n];
	set<Vertice> N[n];

	//Variáveis auxiliares para desempenho
	Vertice mapa[n];

	vector<Vertice> k0;
	set<Vertice> delta_k;
	bool inDelta_k[n];

	for (Vertice v : U)
	{
		delta[v.Indice()] = G->Grau(v);
		k[v.Indice()] = R[v];
		N[v.Indice()] = G->Adjacentes(v);

		mapa[v.Indice()] = v;
		if (k[v.Indice()] == 0) k0.push_back(v);

		if (delta[v.Indice()] < k[v.Indice()])
		{
			delta_k.insert(v);
			inDelta_k[v.Indice()] = true;
		}
		else
		{
			inDelta_k[v.Indice()] = false;
		}
	}


	while (U.size() > 0)
	{
		Vertice v;
		//Caso 1: Existe v em U tal que k(v) = 0 => v foi dominado e sua dominação deve ser propagada
		if (k0.size() > 0)
		{
			v = k0.back();
			k0.pop_back();

			//cout << "Caso 1: " << v.Id() << endl;

			if (inDelta_k[v.Indice()] == true) delta_k.erase(v);

			for (Vertice u : N[v.Indice()])
			{
				N[u.Indice()].erase(v);

				delta[u.Indice()] = delta[u.Indice()] - 1;
				if (k[u.Indice()] > 0)
				{
					k[u.Indice()] = k[u.Indice()] - 1;
					if (k[u.Indice()] == 0) k0.push_back(u);
				}
			}
		}
		else
		{
			//Caso 2: Existe v em U tal que delta(v) < k(v) => v não possui vizinhos o suficiente para ser dominado, logo v é adicionado
			if (delta_k.size() > 0)
			{
				auto it = prev(delta_k.end());
				v = *it;

				//cout << "Caso 2: " << v.Id() << endl;

				delta_k.erase(it);
				inDelta_k[v.Indice()] = false;

				S.insert(v);

				for (Vertice u : N[v.Indice()])
				{
					N[u.Indice()].erase(v);

					k[u.Indice()] = k[u.Indice()] - 1;
					delta[u.Indice()] = delta[u.Indice()] - 1;
					if (k[u.Indice()] == 0)	k0.push_back(u);
				}
			}
			else //Caso 3: Escolher um vértice v que será dominado por seus vizinhos
			{
				//v é o vértice que maxima a expressão
				double max_x = -1;
				for (Vertice u : U)
				{
					double x =  calcularAvaliacao(k[u.Indice()], delta[u.Indice()]);
					if (x > max_x)
					{
						max_x = x;
						v = u;
					}
				}

				//cout << "Caso 3: " << v.Id() << endl;

				//v será dominado por seus vizinhos
				for (Vertice u : N[v.Indice()])
				{
					N[u.Indice()].erase(v);
					delta[u.Indice()] = delta[u.Indice()] - 1;
					if (delta[u.Indice()] < k[u.Indice()])
					{
						delta_k.insert(u);
						inDelta_k[v.Indice()] = true;
					}
				}
			}
		}
		//A cada iteração: O vértice escolhido é removido do grafo
		U.erase(v);
	}
	return S;
}
