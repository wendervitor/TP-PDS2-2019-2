#include <iostream>
#include <string>
#include <vector>

#ifndef CLASSESUSUARIO_H
#define CLASSESUSUARIO_H

using namespace std;

struct Usuario{
	public:
		Usuario(const int ID, const string NOME, const int IDADE, float SALDO): id(ID), nome(NOME), idade(IDADE), saldo(SALDO) {}
		int getID();
		string getNome();
		int getIdade();
		float getSaldo();
		virtual string getTipo(){};
		bool setSaldo(float valor);
	private:
		const int id;
		const string nome;
		const int idade;
		float saldo;
};

struct Crianca;
struct Adulto : public Usuario{
	
	public:
		Adulto(const int ID, const string NOME, const int IDADE, float SALDO): Usuario(ID, NOME, IDADE, SALDO) {}	
		void addDependente(Crianca* c1);
		vector<Crianca*> getDependentes();
		string getTipo();
	private:
		vector<Crianca*> dependentes;
};

struct Crianca : public Usuario{
	
	public:
		Crianca(const int ID, const string NOME, const int IDADE, float SALDO, Adulto* responsavell): Usuario(ID, NOME, IDADE, SALDO), responsavel(responsavell) {}
		Adulto* getResponsavel();
		string getTipo();
	private:
		Adulto* responsavel;
};

struct Idoso : public Adulto{
	public:
		Idoso(const int ID, const string NOME, const int IDADE, float SALDO): Adulto(ID, NOME, IDADE, SALDO){}
		string getTipo();	
};
#endif
