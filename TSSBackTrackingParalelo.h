#pragma once
#include "LocalLib.h"
#include "mpi.h"

class TSSBackTrackingParalelo
{
	private:
		Grafo* G;
		VetorRequisitos R;
		bool resposta;
		int n;

		void Recursao(set<Vertice> NDom, vector<int> VetNR, vector<bool> MapaDom, vector<set<Vertice>> N, set<Vertice> S, int maxid, int tamMax);

	public:
		TSSBackTrackingParalelo(Grafo* G, VetorRequisitos R);
		bool Executar(int tamMax, int id, int cores);
		set<Vertice> solucaoEncontrada;
};
