#include "Maquinas.h"
#include "MaquinaFantoche.h"
#include "MaquinaCinema.h"
#include "MaquinaShow.h"
#include "MaquinaBoate.h"

Totem* Totem::criaMaquina(int idEvento,vector<Cinema*> &Cinemas,vector<Show*> &shows,vector<TeatroFantoche*> &teatros,vector<Boate*> &boates){
	switch(idEvento){
		case 1:
			return MaquinaCinema::getInstance(Cinemas);
		break;
		case 2:
			return MaquinaShow::getInstance(shows);
		break;
		case 3:
			return MaquinaFantoche::getInstance(teatros);
		break;
		case 4:
			return MaquinaBoate::getInstance(boates);
		break;
	}
}

void Totem::impressaoFinal(){
	map<Evento*,int>::iterator it1;
	map<Usuario*,int>::iterator it2;
	it1= ingressosVendidos.begin();
	cout<<"\nMaquina Atual: "<<it1->first->getTipo()<<endl;
	cout<<"\n Usuarios que realizaram compras: \n"<<endl;
	for (it2= ingressosComprados.begin(); it2 != ingressosComprados.end(); ++it2) {
        cout<<"\n 	ID: "<<it2->first->getID()<<"\n 	Nome: "<<it2->first->getNome()<<"\n 	Ingressos Comprados: "<<it2->second<<"\n 	Saldo Final: "<<it2->first->getSaldo()<<endl;
        
    }
  	cout<<"\n Ingressos Vendidos: \n"<<endl;
    for (it1= ingressosVendidos.begin(); it1 != ingressosVendidos.end(); ++it1) {
        cout<<"\n 	ID: "<<it1->first->getId()<<"\n 	Nome: "<<it1->first->getNome()<<"\n 	Ingressos Vendidos: "<<it1->second<<endl;
        
    }
}