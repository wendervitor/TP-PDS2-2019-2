//compile in linux: g++ *.cpp -o output

#include <iostream>
#include <algorithm>

#include "classesUsuario.h"
#include "classesEventos.h"
#include "leArquivo.h"
#include "Maquinas.h"
#include "funcoesUsuario.h"
#include "funcoesEvento.h"

vector<Cinema*> Cinemas;
vector<TeatroFantoche*> teatros;
vector<Boate*> boates;
vector<Show*> shows;
vector<Adulto*> Adultos;
vector<Crianca*> Criancas;
vector<Idoso*> Idosos;
vector<Adulto*> notCrianca;
vector<Totem*> maquinasAbertas;

void menu(){
	int opc,c;
	static bool controladorCarregamento=0;
	do{
		cout<<"\n		Bilheteria"<<endl;
		cout<<"\nEscolha uma das opcoes abaixo:"<<endl;
		cout<<"\n	1. Carregar usuarios e eventos"<<endl;
		cout<<"	2. Exibir usuarios cadastrados"<<endl;
		cout<<"	3. Comprar ingressos"<<endl;
		cout<<"	4. Sair"<<endl;
		cout<<"\nOpcao: ";
		cin>>opc;
		switch(opc){
			case 1:
				system("clear||cls");
				if(controladorCarregamento==0){
					leUsuarios("users-hp.csv",Adultos,Criancas,Idosos,notCrianca);
					leEventos("events-hp.csv",Cinemas,teatros,boates,shows,notCrianca);
					controladorCarregamento = 1;
					cout<<"Usuarios e Eventos carregados"<<endl;
				}
				else cout<<"Usuarios e Eventos ja foram carregados anteriormente"<<endl;
				
				break;
			case 2:
				system("clear||cls");
				if(controladorCarregamento==1){
					imprimeUsuarios(Adultos,Criancas,Idosos);
				}else{
					cout<<"Voce deve carregar os usuarios e eventos primeiro\nDeseja fazer isso?\n(1)Sim\n(2)Nao\nDigite sua opcao: ";
					cin>>c;
					if(c==1){
						leUsuarios("users-hp.csv",Adultos,Criancas,Idosos,notCrianca);
						leEventos("events-hp.csv",Cinemas,teatros,boates,shows,notCrianca);
						controladorCarregamento=1;
						imprimeUsuarios(Adultos,Criancas,Idosos);	
					}
				}
				break;
			case 3:
				system("clear||cls");
				int idUsuario,idEvento;
				bool cria;
				if(controladorCarregamento==1){
					cout<<"Digite o ID de um usuario valido: ";
					cin>>idUsuario;
					if(verificaIdUsuario(idUsuario,notCrianca)!=-1){
						idUsuario=verificaIdUsuario(idUsuario,notCrianca);
						system("clear||cls");
						cout<<"\nBem vindo(a), "<<notCrianca[idUsuario]->getNome()<<endl;
						cout<<"\n 1. Cinema(Livre)\n 2. Show(Adulto)\n 3. Teatro de fantoche(Infantil)\n 4. Boate(Adulto)\n 0. Voltar\n"<<endl;
						cout<<"Digite o tipo de evento que deseja comprar ingressos: "; //Tratar quando digitar errado aqui
						cin>>idEvento;
						if(idEvento>0 && idEvento<=4){
							system("clear||cls");
							Totem* Maquina = Totem::criaMaquina(idEvento,Cinemas,shows,teatros,boates);
							cria = Maquina->TelaInicial(notCrianca[idUsuario]);
							if(cria == true && find(maquinasAbertas.begin(), maquinasAbertas.end(), Maquina) == maquinasAbertas.end()) {
    							maquinasAbertas.push_back(Maquina);
							}
						}
					}else cout<<"Usuario nao cadastrado ou eh uma crianca"<<endl;

				}else{
					cout<<"Voce deve carregar os usuarios e eventos primeiro\nDeseja fazer isso?\n(1)Sim\n(2)Nao\nDigite sua opcao: ";
					cin>>c;
					if(c==1){
						leUsuarios("users-hp.csv",Adultos,Criancas,Idosos,notCrianca);
						leEventos("events-hp.csv",Cinemas,teatros,boates,shows,notCrianca);
						cout<<"Usuarios e Eventos carregados"<<endl;
						controladorCarregamento=1;
						cout<<"Digite o ID de um usuario valido: ";
						cin>>idUsuario;
						if(verificaIdUsuario(idUsuario,notCrianca)!=-1){
							idUsuario=verificaIdUsuario(idUsuario,notCrianca);
							system("clear||cls");
							cout<<"\nBem vindo(a), "<<notCrianca[idUsuario]->getNome()<<endl;
							cout<<"\n 1. Cinema(Livre)\n 2. Show(Adulto)\n 3. Teatro de fantoche(Infantil)\n 4. Boate(Adulto)\n 0. Voltar\n"<<endl;
							cout<<"Digite o tipo de evento que deseja comprar ingressos: "; //Tratar quando digitar errado aqui
							cin>>idEvento;
							if(idEvento>0 && idEvento<=4){
								Totem* Maquina = Totem::criaMaquina(idEvento,Cinemas,shows,teatros,boates);
								cria = Maquina->TelaInicial(notCrianca[idUsuario]);
								if(cria == true && find(maquinasAbertas.begin(), maquinasAbertas.end(), Maquina) == maquinasAbertas.end()) {
    								maquinasAbertas.push_back(Maquina);
								}
							}
						}else cout<<"Usuario nao cadastrado ou eh uma crianca"<<endl;
					}
				}
				break;
			case 4:
				system("clear||cls");
				if(!maquinasAbertas.empty()){
					for(int i=0;i<maquinasAbertas.size();i++) maquinasAbertas[i]->impressaoFinal();
					cout<<"\n\nEspero que tenha tido uma boa experiencia!!!\n"<<endl;
				}
				break;
			default:
				cout<<"Opcao invalida"<<endl;
		}
	}while(opc != 4);
}

int main(){
	menu();
	return 0;
}