#include "LocalLib.h"
#include "TSSBackTrackingParalelo.h"

TSSBackTrackingParalelo::TSSBackTrackingParalelo(Grafo* pG, VetorRequisitos pR): R(pR)
{
	G = new Grafo(pG);
	n = G->N();
	resposta = false;
}

void TSSBackTrackingParalelo::Recursao(set<Vertice> NDom, vector<int> VetNR, vector<bool> MapaDom, vector<set<Vertice>> N, set<Vertice> S, int maxid, int tamMax)
{
	if (S.size() > tamMax)
	{
		return;
	}
	else
	{
		if (NDom.size() == 0)
		{
			//S domina o grafo
			if (S.size() < solucaoEncontrada.size() || resposta == false)
			{
				solucaoEncontrada = set<Vertice>(S);
				resposta = true;
			}
			return;
		}
		else
		{
			for (Vertice v : NDom)
			{
				if (v.Id() > maxid)
				{
					set<Vertice> S2(S);
					set<Vertice> NDom2(NDom);
					vector<int> VetNR2(VetNR);
					vector<bool> MapaDom2(MapaDom);
					vector<set<Vertice>> N2(N);

					queue<Vertice> fila;
					S2.insert(v);

					fila.push(v);
					MapaDom2[v.Indice()] = true;

					while (fila.empty() == false)
					{
						Vertice u = fila.front();
						fila.pop();

						for (Vertice z : N2[u.Indice()])
						{
							VetNR2[z.Indice()] = VetNR2[z.Indice()] + 1;
							if (VetNR2[z.Indice()] >= R[z] && MapaDom2[z.Indice()] == false)
							{
								fila.push(z);
								MapaDom2[z.Indice()] = true;
							}
							N2[z.Indice()].erase(u);
						}
						N2[u.Indice()].clear();

						NDom2.erase(u);
					}

					Recursao(NDom2, VetNR2, MapaDom2, N2, S2, v.Id(), tamMax);
				}
			}
		}
	}
}

bool TSSBackTrackingParalelo::Executar(int tamMax, int id, int cores)
{
	int ini, fim;
	if (n < cores)
	{
		if (id < n)
		{
			ini = id + 1;
			fim = ini;
		}
		else
		{
			ini = -1;
			fim = -1;
		}
	}
	else
	{
		if (n == cores)
		{
			ini = id + 1;
			fim = ini;
		}
		else
		{
			// n > cores
			int resto = n % cores;
			int div = n / cores;
			int shift = min(id,resto);
			if (id < resto)
			{
				ini = n + 1 - ((id * div) + 2 + shift + 1);
				fim = n + 1 - ((id * div) + 1 + shift);

			}
			else
			{
				ini = n + 1 - ((id * div) + 2 + shift);
				fim = n + 1 - ((id * div) + 1 + shift);
			}
		}
	}

	resposta = false;
	solucaoEncontrada = set<Vertice>();

	if (ini > 0 && fim > 0)
	{
		for (int i = ini; i <= fim; i++)
		{
			//cout << "Proc: " << id << " - Base: " << i << endl;
			//Vertice de Id i será adicionado
			set<Vertice> S;
			set<Vertice> NDom(G->Vertices);
			vector<int> VetNR;
			vector<bool> MapaDom;
			vector<set<Vertice>> N;

			VetNR.resize(n,0);
			MapaDom.resize(n,false);
			N.resize(n);
			for (Vertice v: G->Vertices)
			{
				N[v.Indice()] = G->Adjacentes(v);
			}
			queue<Vertice> fila;

			Vertice v = G->VerticePorId(i);
			S.insert(v);
			fila.push(v);
			MapaDom[v.Indice()] = true;

			while (fila.empty() == false)
			{
				Vertice u = fila.front();
				fila.pop();

				for (Vertice z : N[u.Indice()])
				{
					VetNR[z.Indice()] = VetNR[z.Indice()] + 1;
					if (VetNR[z.Indice()] >= R[z] && MapaDom[z.Indice()] == false)
					{
						fila.push(z);
						MapaDom[z.Indice()] = true;
					}
					N[z.Indice()].erase(u);
				}
				N[u.Indice()].clear();
				NDom.erase(u);
			}
			Recursao(NDom, VetNR, MapaDom, N, S, v.Id(), tamMax);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	//Ao final, cada um tem um próprio resultado e um próprio tamanho
	bool respostaGlobal;
	MPI_Allreduce(&resposta, &respostaGlobal, 1, MPI_C_BOOL, MPI_LOR, MPI_COMM_WORLD);
	resposta = respostaGlobal;

	if (resposta == true)
	{
		int tamLocal = solucaoEncontrada.size();
		int* vetTamGlobal = (int*) malloc (cores * sizeof(int));
		MPI_Allgather(&tamLocal, 1, MPI_INT, vetTamGlobal, 1, MPI_INT, MPI_COMM_WORLD);

		int minS = n, minPos;
		for (int i = 0; i < cores; i++)
		{
			if (vetTamGlobal[i] > 0 && vetTamGlobal[i] < minS)
			{
				minS = vetTamGlobal[i];
				minPos = i;
			}
		}

		//O processador minPos possui a menor solução
		int* sol = (int*) malloc (minS * sizeof(int));
		if (id == minPos)
		{
			int i = 0;
			for (Vertice v : solucaoEncontrada)
			{
				sol[i] = v.Id();
				i++;
			}
		}

		//cout << "Min: " << minS << " - Core: " << minPos << endl;
		MPI_Bcast(sol,minS,MPI_INT,minPos,MPI_COMM_WORLD);

		solucaoEncontrada.clear();
		for (int i = 0; i < minS; i++)
		{
			solucaoEncontrada.insert(G->VerticePorId(sol[i]));
		}
	}
	else
	{
		solucaoEncontrada.clear();
	}

	return resposta;
}

