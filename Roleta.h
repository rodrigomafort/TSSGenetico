#pragma once
#include "LocalLib.h"

template <class T>
class ItemRoleta
{
public:
	double prob;
	double probCalc;
	double lowerBound;
	double upperBound;
	T key;

	ItemRoleta(T k, double prob);
};

template <class T>
class Roleta
{

	double soma;
public:
	vector<ItemRoleta<T>> itens;

	Roleta();
	~Roleta();

	void Adicionar(T key, double probalilidade);
	bool AlterarProbalilidade(T key, double novaProb);

	int TamanhoRoleta();

	void Preparar();
	T Sortear();
};

template class Roleta<int>;
