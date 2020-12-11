#include "classesEventos.h"
#ifndef FUNCOESEVENTO_H
#define FUNCOESEVENTO_H

/////////////////
//Funcoes do TP1
/////////////////

void qtdEventos (vector<Cinema*> &c, vector<TeatroFantoche*> &t, vector<Boate*> &b, vector<Show*> &s);
void maiorCotaIdoso(vector<Show*> &s,vector<Boate*> &b);
void ingressoPorPreco(vector<Cinema*> &c,vector<TeatroFantoche*> &t,vector<Boate*> &b,vector<Show*> &s);
void eventosPorUsuario(vector<Adulto*> &a, vector<Cinema*> &c, vector<TeatroFantoche*> &t, vector<Boate*> &b, vector<Show*> &s);

#endif