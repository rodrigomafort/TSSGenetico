#pragma once
#include "LocalLib.h"
#include "mpi.h"

class TSSCordasco {
	Grafo* G;
	VetorRequisitos R;
	int n;
public:
	TSSCordasco(Grafo* G, VetorRequisitos R);
	set<Vertice> Executar();
};

