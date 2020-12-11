#include "MaquinaCinema.h"

MaquinaCinema* MaquinaCinema::instancia = 0;
MaquinaCinema* MaquinaCinema::getInstance(vector<Cinema*> &Cinemas){
	if(instancia == 0) instancia = new MaquinaCinema(Cinemas);
	return instancia;
}
MaquinaCinema::MaquinaCinema(vector<Cinema*> &Cinemas){
	this->cinemasDisponiveis=Cinemas;
}

void MaquinaCinema::exibeEventos(){
	int qtd=0;
	for(int i=0;i<cinemasDisponiveis.size();i++){
		cout<<"\nID: ";
		cout<<cinemasDisponiveis[i]->getId();
		cout<<"	Nome: ";
		cout<<cinemasDisponiveis[i]->getNome()<<endl;
		cout<<"	Ingressos disponiveis: ";
		cout<<cinemasDisponiveis[i]->getCapacidadeTotal()<<endl;
		cout<<"	Duracao: ";
		cout<<cinemasDisponiveis[i]->getDuracao()<<endl;
		cout<<"	Horarios: ";
		for(int j=0;j<cinemasDisponiveis[i]->getHorarios().size();j++){
			cout<<cinemasDisponiveis[i]->getHorarios()[j];
			if(cinemasDisponiveis[i]->getHorarios().size()-j>1)cout<<", ";
		}
		cout<<"\n";
	}
}

int MaquinaCinema::verificaIdEvento(int id){
	for(int i =0 ;i<this->cinemasDisponiveis.size();i++) if(cinemasDisponiveis[i]->getId()==id)return i;
	return -1;
}

bool MaquinaCinema::realizaCompra(Adulto * &user, int qtdIngressos, int idEvento){
	float valorTotal=0;
	int loteAtual=0,precoAtual=0;
	int aux = qtdIngressos;
	vector<int> ingressos = cinemasDisponiveis[idEvento]->getCapacidade();
	vector<int> precos = cinemasDisponiveis[idEvento]->getPrecos();
	map<Evento*,int>::iterator it1;
	map<Usuario*,int>::iterator it2;

	for(int i=0; i<ingressos.size();i++){
		if(ingressos[i]>0){
			loteAtual=ingressos[i];
			precoAtual=precos[i];
			if(aux>loteAtual){
				valorTotal+=(aux-loteAtual)*precoAtual;
				aux-=loteAtual;
			}
			else{
				valorTotal+=aux*precoAtual;
				break;
			}
		}
	}

	if(user->getSaldo()>=valorTotal){
		user->setSaldo(-valorTotal);
		for(int i=0;i<ingressos.size();++i){
			it1 = ingressosVendidos.find(cinemasDisponiveis[idEvento]);
			it2 = ingressosComprados.find(user);			
			if(ingressos[i]<qtdIngressos){
				this->cinemasDisponiveis[idEvento]->retiraCapacidade(ingressos[i],i);
				if(it1 == ingressosVendidos.end()){
					this->ingressosVendidos.insert(pair<Evento*, int>(cinemasDisponiveis[idEvento], ingressos[i]));						
				}else{
					it1->second+=ingressos[i];
				}
				if(it2 == ingressosComprados.end()){
					this->ingressosComprados.insert(pair<Usuario*, int>(user, ingressos[i]));
				}else{
					it2->second+=ingressos[i];
				}
				qtdIngressos-=ingressos[i];
				ingressos[i]-=ingressos[i];
			}
			else{
				this->cinemasDisponiveis[idEvento]->retiraCapacidade(qtdIngressos,i);
				
				if(it1 == ingressosVendidos.end()){
					
					this->ingressosVendidos.insert(pair<Evento*, int>(cinemasDisponiveis[idEvento], qtdIngressos));						
				}else{
					
					it1->second+=qtdIngressos;
				}
				if(it2 == ingressosComprados.end()){
					this->ingressosComprados.insert(pair<Usuario*, int>(user, qtdIngressos));
				}else{
					it2->second+=qtdIngressos;
				}
				qtdIngressos=0;
				ingressos[i]-=qtdIngressos;
				cout<<"INGRESSO(S) ADQUIRIDOS, CURTA BASTANTE !"<<endl;
				return true;
			}
		}
	}else{
		cout<<"Saldo Indiponivel"<<endl;
		return false;
	}
}

bool MaquinaCinema::TelaInicial(Adulto* &user){
	int idEvento,qtdIngressos,qtd,hora,loteAtual,valorTotal=0;
	cout<<"Bem vindo(a) a tela de compra de ingressos Cinemas, "<<user->getNome()<<endl;
	cout<<"Eventos disponiveis:"<<endl;
	this->exibeEventos();
	cout<<"Digite o id do evento que voce deseja: ";
	cin>>idEvento;
	idEvento=verificaIdEvento(idEvento);
	if(idEvento != -1){
		
		cout<<"Voce selecionou "<<cinemasDisponiveis[idEvento]->getNome()<<endl;
		cout<<"		Horarios: "<<endl;
		for(int j=0;j<cinemasDisponiveis[idEvento]->getHorarios().size();j++)
			cout<<"("<<j<<"). "<<cinemasDisponiveis[idEvento]->getHorarios()[j]<<endl;
		cout<<"Selecione um Horario: ";
		cin>>hora;
		if(hora>=0 && hora<this->cinemasDisponiveis[idEvento]->getHorarios().size()){
			cout<<"Digite a quantidade requerida de ingressos: ";
			cin>>qtdIngressos;
			if(qtdIngressos>cinemasDisponiveis[idEvento]->getCapacidadeTotal()){
				cout<<"Nao tem isso tudo de ingresso"<<endl;
				return false;
			}
			if(this->cinemasDisponiveis[idEvento]->getCapacidadeTotal()>0){//CONSERTAR !!!
				if(qtdIngressos>0){
					bool a = realizaCompra(user,qtdIngressos,idEvento);
					return a;
				}else{
					return false;
				}
			}else cout<<"Não ha mais ingressos"<<endl;
		}else cout<<"Horario nao disponivel"<<endl;
	}else cout<<"Id inexistente"<<endl;
	return false;
}