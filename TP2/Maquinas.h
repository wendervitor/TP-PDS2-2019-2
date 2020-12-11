#include "classesEventos.h"
#include "classesUsuario.h"
#include <map>

#ifndef MAQUINAS_H
#define MAQUINAS_H
/**
	Classe totem, responsavel por servir de superclasse as maquinas e tambem eh fundamental para o funcionamento do Factory Method
*/
class Totem{
public:
	/**
		Funcao que implementa a logica do factory method

		@param id do tipo de maquina que deseja abrir e vectors que contem os eventos, por referencia, para passar a info para a maquina
		@return Objeto do tipo MaquinaFantoche. MaquinaCinema, MaquinaBoate ou MaquinaShow, dependendo do id passado  
	*/
	static Totem* criaMaquina(int idEvento,vector<Cinema*> &Cinemas,vector<Show*> &shows,vector<TeatroFantoche*> &teatros,vector<Boate*> &boates);
	/**
		Funcao virtual para a tela inicial, cada maquina tera a sua e fará a interacao do usuario com programa

		@param Referência para um objeto tipo Adulto
	*/
	virtual bool TelaInicial(Adulto* &user){};
	/**
		Funcao que imprime os eventos disponiveis, dependedo de cada vetor
	*/
	virtual void exibeEventos(){};
	/**
		Funcao que faz duas funcoes: verifica se o id digitado pelo usuario existe e se for verdadeiro retorna a posicao dele no vector

		@param id do evento requerido
		@return posicao do evento no vector, caso exista, e -1 caso nao exista
	*/
	virtual int verificaIdEvento(int id){};
	/**
		Funcao responsavel pela opcao 4 do TP, imprime, para cada maquina, dados dos usuarios que compraram ingressos naquela maquina e dados dos Eventos vendidos
	*/
	void impressaoFinal();
	/**
		Funcao que realiza o processo final de compra, apos ter passado por varios testes e verificacoes

		@param	referencia para o tipo Adulto, a quantidade de ingressos que o usuario quer e o id do evento
		@return '1' se conseguir comprar o ingresso, '0' se o usuario nao tiver saldo suficiente ou se tentar comprar mais ingressos que o disponivel
	*/
	virtual bool realizaCompra(Adulto* &user, int qtdIngressos, int idEvento){};
	/// Armazena os eventos que foram vendidos e a quantidade de ingressos
	map <Evento*, int> ingressosVendidos; 	
	/// Armazena os usuarios que compraram ingressos e a quantidade de ingressos
	map <Usuario*, int> ingressosComprados; 
};
#endif