#include "classesUsuario.h"
#include "classesEventos.h"
#include <fstream>
#include <sstream>

#ifndef LEARQUIVO_H
#define LEARQUIVO_H

/**
	Funcao para ler e carregar nos respectivos vectors os dados dos usuarios cadastrados
*/
void leUsuarios(string nome, 
			vector<Adulto*> &Adultos, 
			vector<Crianca*> &Criancas, 
			vector<Idoso*> &Idosos, 
			vector<Adulto*> &notCrianca);

/**
	Funcao para ler e carregar nos respectivos vectors os dados dos eventos cadastrados
*/
void leEventos(string nome, 
			vector<Cinema*> &Cinemas, 
			vector<TeatroFantoche*> &teatros,
			vector<Boate*> &boates,
			vector<Show*> &shows,
			vector<Adulto*> &notCrianca);

#endif