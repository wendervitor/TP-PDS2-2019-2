#include "funcoesEvento.h"

void qtdEventos (vector<Cinema*> &c, vector<TeatroFantoche*> &t, vector<Boate*> &b, vector<Show*> &s)	{

    cout<<"Numero de Eventos:"<<endl;
    cout<<"Adulto: "<<endl;
    int cont=0;
    for(int i=0;i<b.size();i++) cont++ ;
    cout<<" Boate: "<<cont<<endl;

	cont=0;
	for(int i=0;i<s.size();i++) cont++ ;
	cout<<" Show: " <<cont<<endl;

	cont=0;
	cout<<"Livres: "<<endl;
	for(int i=0;i<c.size();i++) cont++ ;
	cout<<" Cinema: " <<cont <<endl;

	cont=0;
	cout<<"Infantis: "<<endl;
	for(int i=0;i<t.size();i++) cont++;
	cout<<" Teatro de Fantoches: "<<cont<<endl;

}


void maiorCotaIdoso(vector<Show*> &s,vector<Boate*> &b){
	
	int quota=0;
	int id=-1;
	string nome = s[0]->getNome();
	
	for(int i=0;i<s.size();i++) {
		if(s[i]->getQuotaIdoso()>quota){
			quota=s[i]->getQuotaIdoso();
			id = s[i]->getId();
			nome = s[i]->getNome();
		}
	}
	for(int i=0;i<b.size();i++) {
		if(b[i]->getQuotaIdoso()>quota){
			quota=b[i]->getQuotaIdoso();
			id = b[i]->getId();
			nome = b[i]->getNome();
		}
	}
	if(id != -1){
		cout<<"Evento com maior cota para idoso:"<<endl;
		cout<<nome<<" (ID: "<<id<<"): "<<quota<<endl;
	}
}

void ingressoPorPreco(vector<Cinema*> &c,vector<TeatroFantoche*> &t,vector<Boate*> &b,vector<Show*> &s){
	
	int qtd=0;
	int preco=50;
	cout<<"Numero de ingressos por preco:"<<endl;
	for(int i=0;i<6;i++){

		for(int j=0;j<b.size();j++){
			for(int k=0;k<b[j]->getPrecos().size();k++)
			if(b[j]->getPrecos()[k]==preco){
				qtd+=b[j]->getCapacidade()[k];	
			}
		}
		for(int j=0;j<c.size();j++){
			for(int k=0;k<c[j]->getPrecos().size();k++)
			if(c[j]->getPrecos()[k]==preco){
				qtd+=c[j]->getCapacidade()[k];	
			}
		}
		for(int j=0;j<t.size();j++){
			for(int k=0;k<t[j]->getPrecos().size();k++)
			if(t[j]->getPrecos()[k]==preco){
				qtd+=t[j]->getCapacidade()[k];	
			}
		}
		for(int j=0;j<s.size();j++){
			for(int k=0;k<s[j]->getPrecos().size();k++)
			if(s[j]->getPrecos()[k]==preco){
				qtd+=s[j]->getCapacidade()[k];	
			}
		}	
		if(qtd != 0)cout<<"R$"<<preco<<": "<<qtd<<endl;
		qtd=0;
		preco+=50;
	}

}

void eventosPorUsuario(vector<Adulto*> &a, vector<Cinema*> &c, vector<TeatroFantoche*> &t, vector<Boate*> &b, vector<Show*> &s){

	int cont=0;
	cout<<"Numero de eventos que o usuario possui:"<<endl;
	for(int i=0;i<a.size();i++){
		for(int j=0;j<c.size();j++) if(c[j]->getResponsavel()==a[i]) cont++;
		for(int j=0;j<t.size();j++) if(t[j]->getResponsavel()==a[i]) cont++;
		for(int j=0;j<b.size();j++) if(b[j]->getResponsavel()==a[i]) cont++;
		for(int j=0;j<s.size();j++) if(s[j]->getResponsavel()==a[i]) cont++;
		if(cont>0)cout<<a[i]->getNome()<<" (ID: "<<a[i]->getID()<<"): "<<cont<<endl;
		cont =0;
	}
}