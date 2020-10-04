#include "LocalLib.h"

template <class T>
ItemRoleta<T>::ItemRoleta(T k, double p) : key(k)
{
	key = k;
	prob = p;
	lowerBound = 0;
	upperBound = 0;
	probCalc = 0;
}

template <class T>
Roleta<T>::Roleta()
{
	soma = 0;
}

template <class T>
Roleta<T>::~Roleta()
{
}

template <class T>
void Roleta<T>::Adicionar(T key, double probabilidade)
{
	if (probabilidade < 0)
		itens.push_back(ItemRoleta<T>(key, 0));
	else
		itens.push_back(ItemRoleta<T>(key, probabilidade));

	/*
	if (probabilidade < 0)
		throw std::runtime_error("Probabilidade Negativa na Roleta");

	auto res = itens.insert(make_pair(key,probabilidade));
	if (res.second == true)
	{
		soma = soma + probabilidade;
	}*/
}

template <class T>
int Roleta<T>::TamanhoRoleta()
{
	return itens.size();
}

template <class T>
bool Roleta<T>::AlterarProbalilidade(T key, double novaProb)
{
	/*if (itens.find(key) != itens.end())
	{
		soma = soma - itens[key];
		itens[key] = novaProb;
		soma = soma + itens[key];
		return true;
	}
	else
	{
		return false;
	}*/

	for (ItemRoleta<T> i : itens)
	{
		if (i.key == key)
		{
			i.prob = novaProb;
			return true;
		}
	}
	return false;
}


template <class T>
void Roleta<T>::Preparar()
{
	double soma = 0;
	for (int i = 0; i < itens.size(); i++)
		soma = soma + itens[i].prob;
	
	double step = 0;
	for (int i = 0; i < itens.size(); i++)
	{
		itens[i].probCalc = itens[i].prob / soma;
		itens[i].lowerBound = step;
		itens[i].upperBound = step + itens[i].probCalc;
		step = step + itens[i].probCalc;
	}
}

template <class T>
T Roleta<T>::Sortear()
{
	uniform_real_distribution<> rndInterval(0, 1);
	random_device rd;
	mt19937_64 e2(rd());
	double d = rndInterval(e2);

	/*
	uniform_real_distribution<> rndInterval(0, soma);
	random_device rd;
	mt19937_64 e2(rd());
	double d = rndInterval(e2);

	if (itens.size() > 0)
	{
		double t = 0;

		for (auto it = itens.begin(); it != itens.end(); ++it)
		{
			t = t + it -> second;
			if (d <= t)
			{
				T key = it -> first;
				soma = soma - it->second;
				itens.erase(it);
				return key;
			}
		}

		auto last = itens.rbegin();
		T key = last -> first;
		soma = soma - last->second;
		itens.erase(key);
		return key;
	}*/
	for (ItemRoleta<T> i : itens)
	{
		if (d >= i.lowerBound && d < i.upperBound)
		{
			return i.key;
		}
	}
	return itens[itens.size() - 1].key;
}
