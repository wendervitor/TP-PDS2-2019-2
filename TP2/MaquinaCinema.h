#include "Maquinas.h"
#ifndef MAQUINACINEMA_H
#define MAQUINACINEMA_H

class MaquinaCinema: public Totem{
	
	public:
		///Variavel que mantem uma instancia da maquina, caso ja tenha sido instanciada, se nao armazena 0
		static MaquinaCinema* instancia;
		///construtor
		MaquinaCinema(vector<Cinema*> &Cinemas); 
		/**
			Funcao que realiza a logica do singleton, eh chamada pelo factory method e retorna a instancia da maquina em questao caso exista, se nao cria uma

			@param	vector do tipo Cinema*
			@return	variavel instancia, caso nao seja vazia ou nova instancia caso seja vazia e ainda atualiza o valor de instancia
		*/
		static MaquinaCinema* getInstance(vector<Cinema*> &Cinemas);
		bool TelaInicial(Adulto* &user);
		void exibeEventos();
		int verificaIdEvento(int id);
		bool realizaCompra(Adulto* &user, int qtdIngressos, int idEvento);
	private:
		/**
			vector com os eventos do tipo cinemas disponiveis, serve para facilicar as operacoes nas funcoes
				(usar apenas 'this' ao inves de ficar passando o vector por referencia)
		*/
		vector<Cinema*> cinemasDisponiveis;
};

#endif