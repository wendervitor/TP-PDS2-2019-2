#include "classesUsuario.h"
#ifndef FUNCOESUSUARIO_H
#define FUNCOESUSUARIO_H
/**
	Funcao que faz duas funcoes: verifica se o id digitado pelo usuario existe e se for verdadeiro retorna a posicao dele no vector

	@param id do Usuario requerido
	@return posicao do evento no vector, caso exista, e -1 caso nao exista
*/
int verificaIdUsuario(int id, vector<Adulto*> &usuarios);
/**
	Segunda opcao do TP, imprime todos os usuarios e suas caracteristicas

	@param Vectors para cada tipo de usuario(Crianca, Adulto e Idoso)
*/
void imprimeUsuarios (vector<Adulto*> &Adultos, vector<Crianca*> &Criancas, vector<Idoso*> &Idosos);

/////////////////
//Funcoes do TP1
/////////////////

bool possuiDependente(Adulto* &a, vector <Crianca*> &c);
void imprimeDependentes(vector<Adulto*> &Adultos, vector<Crianca*> &Criancas);
void qtdUsuarios(vector<Adulto*> &a, vector<Crianca*> &c, vector<Idoso*> &v);
void idade(vector<Adulto*> &a, vector<Crianca*> &c, vector<Idoso*> &v);
void qtdDependentes(vector<Adulto*> &Adultos);

#endif
