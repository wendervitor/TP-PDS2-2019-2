#include "MaquinaFantoche.h"

MaquinaFantoche* MaquinaFantoche::instancia = 0;
MaquinaFantoche* MaquinaFantoche::getInstance(vector<TeatroFantoche*> &teatros){
	if(instancia == 0) instancia = new MaquinaFantoche(teatros);
	return instancia;
}
MaquinaFantoche::MaquinaFantoche(vector<TeatroFantoche*> &teatros){//construtor
	this->teatrosDisponiveis=teatros;
}

void MaquinaFantoche::exibeEventos(){
	int qtd=0;

	for(int i=0;i<teatrosDisponiveis.size();i++){
		cout<<"\nID: ";
		cout<<teatrosDisponiveis[i]->getId();
		cout<<"	Nome: ";
		cout<<teatrosDisponiveis[i]->getNome()<<endl;
		cout<<"	Ingressos disponiveis: ";
		cout<<teatrosDisponiveis[i]->getCapacidadeTotal()<<endl;
		cout<<"	Horarios: ";
		for(int j=0;j<teatrosDisponiveis[i]->getHorarios().size();j++){
			cout<<teatrosDisponiveis[i]->getHorarios()[j];
			if(teatrosDisponiveis[i]->getHorarios().size()-j>1)cout<<", ";
		}
		cout<<"\n";
	}
}

int MaquinaFantoche::verificaIdEvento(int id){
	int qtd=0;
	for(int i =0 ;i<this->teatrosDisponiveis.size();i++) if(teatrosDisponiveis[i]->getId()==id)return i;
	return -1;
}

bool MaquinaFantoche::realizaCompra(Adulto * &user, int qtdIngressos, int idEvento){
	float valorTotal=0;
	int loteAtual=0,precoAtual=0;
	int aux = qtdIngressos;
	vector<int> ingressos = teatrosDisponiveis[idEvento]->getCapacidade();
	vector<int> precos = teatrosDisponiveis[idEvento]->getPrecos();
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
			it1 = ingressosVendidos.find(teatrosDisponiveis[idEvento]);
			it2 = ingressosComprados.find(user);			
			if(ingressos[i]<qtdIngressos){
				this->teatrosDisponiveis[idEvento]->retiraCapacidade(ingressos[i],i);
				if(it1 == ingressosVendidos.end()){
					this->ingressosVendidos.insert(pair<Evento*, int>(teatrosDisponiveis[idEvento], ingressos[i]));						
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
				this->teatrosDisponiveis[idEvento]->retiraCapacidade(qtdIngressos,i);
				
				if(it1 == ingressosVendidos.end()){
					
					this->ingressosVendidos.insert(pair<Evento*, int>(teatrosDisponiveis[idEvento], qtdIngressos));						
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

bool MaquinaFantoche::TelaInicial(Adulto* &user){
	int idEvento,qtdIngressos,qtd,hora,loteAtual,valorTotal=0;
	cout<<"Bem vindo(a) a tela de compra de ingressos de tearo de fantoche, "<<user->getNome()<<endl;
	cout<<"Eventos disponiveis:"<<endl;
	this->exibeEventos();
	cout<<"Digite o id do evento que voce deseja: ";
	cin>>idEvento;
	idEvento=verificaIdEvento(idEvento);
	if(idEvento != -1){
		
		cout<<"Voce selecionou "<<teatrosDisponiveis[idEvento]->getNome()<<endl;
		cout<<"		Horarios: "<<endl;
		for(int j=0;j<teatrosDisponiveis[idEvento]->getHorarios().size();j++)
			cout<<"("<<j<<"). "<<teatrosDisponiveis[idEvento]->getHorarios()[j]<<endl;
		cout<<"Selecione um Horario: ";
		cin>>hora;
		if(hora>=0 && hora<this->teatrosDisponiveis[idEvento]->getHorarios().size()){
			cout<<"Digite a quantidade requerida de ingressos: ";
			cin>>qtdIngressos;
			if(qtdIngressos>teatrosDisponiveis[idEvento]->getCapacidadeTotal()){
				cout<<"Nao tem isso tudo de ingresso"<<endl;
				return false;
			}
			if(this->teatrosDisponiveis[idEvento]->getCapacidadeTotal()>0){//CONSERTAR !!!
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
