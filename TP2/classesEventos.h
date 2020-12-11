#include "classesUsuario.h"

#ifndef CLASSESEVENTOS_H
#define CLASSESEVENTOS_H

using namespace std;
struct Evento{
public:

	//Construtor
	Evento(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS): id(ID), nome(NOME), responsavel(RESPONSAVEL), capacidade(CAPACIDADE), precos(PRECOS){} 
	
	////////////////////
	//Getters e Setters
	////////////////////
	
	int getId();
	string getNome();
	Usuario* getResponsavel();
	vector<int> getCapacidade();
	vector<int> getPrecos();
	void retiraCapacidade(int qtd,int loteAtual);
	int getCapacidadeTotal();
	virtual string getTipo(){};
	
	
	
private:
	const int id;
	const string nome;
	Usuario* responsavel;
	vector<int> capacidade;
	vector<int> precos;
};

struct EventoInfantil : public Evento{
public:
	EventoInfantil(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS): Evento (ID, NOME,RESPONSAVEL, CAPACIDADE, PRECOS){}
};

struct TeatroFantoche : public EventoInfantil{
public:
	TeatroFantoche(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS, vector<int>HORARIOS): EventoInfantil(ID, NOME,RESPONSAVEL, CAPACIDADE, PRECOS), horarios(HORARIOS){}	
	
	////////////////////
	//Getters e Setters
	////////////////////

	vector<int> getHorarios();
	string getTipo() ;
private:
		vector<int> horarios;
};

struct Cinema : public Evento{
public:
	Cinema(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS, vector<int> HORARIO, const int DURACAO): Evento (ID, NOME,RESPONSAVEL, CAPACIDADE,PRECOS), horarios(HORARIO), duracao(DURACAO){}
	////////////////////
	//Getters e Setters
	////////////////////

	vector<int> getHorarios();
	int getDuracao();
	string getTipo();
private:
	vector<int> horarios;
	const int duracao;
};

struct EventoAdulto : public Evento{
public:
	EventoAdulto(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS, int IDOSO): Evento (ID, NOME,RESPONSAVEL, CAPACIDADE,PRECOS), quota_idoso(IDOSO){}
	int getQuotaIdoso();
	void retiraCotaIdoso(int qtd);
private:
	int quota_idoso;
};

struct Boate : EventoAdulto{
public:
	Boate(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS, const int QUOTA_IDOSO, const int HORAINICIO, const int HORAFIM): EventoAdulto(ID, NOME, RESPONSAVEL, CAPACIDADE,PRECOS,QUOTA_IDOSO) ,horaInicio(HORAINICIO), horaFim(HORAFIM){}
	int getHoraInicio();
	int getHoraFim();
	string getTipo();
private:
	const int horaInicio;
	const int horaFim;
};

struct Show : EventoAdulto{
public:
	Show(const int ID, const string NOME, Usuario* RESPONSAVEL, vector<int> CAPACIDADE, vector<int> PRECOS, const int QUOTA_IDOSO, const int PORTOES, const vector<string> ARTISTAS): EventoAdulto(ID, NOME, RESPONSAVEL, CAPACIDADE,PRECOS,QUOTA_IDOSO) ,aberturaPortoes(PORTOES), artistas(ARTISTAS){}
	int getAberturaPortoes();
	vector<string> getArtistas();
	string getTipo() ;
private:
	const int aberturaPortoes;
	const vector<string> artistas;
};
#endif
