#include "MaquinaShow.h"

MaquinaShow* MaquinaShow::instancia = 0;
MaquinaShow* MaquinaShow::getInstance(vector<Show*> &shows){
	if(instancia == 0) instancia = new MaquinaShow(shows);
	return instancia;
}

MaquinaShow::MaquinaShow(vector<Show*> &shows){
	this->showsDisponiveis=shows;
}

void MaquinaShow::exibeEventos(){
	int qtd=0;
	for(int i=0;i<showsDisponiveis.size();i++){
		cout<<"\nID: ";
		cout<<showsDisponiveis[i]->getId();
		cout<<"	Nome: ";
		cout<<showsDisponiveis[i]->getNome()<<endl;
		cout<<"	Ingressos disponiveis: ";
		cout<<showsDisponiveis[i]->getCapacidadeTotal()<<endl;
		cout<<"	Quota para idosos: ";
		cout<<showsDisponiveis[i]->getQuotaIdoso()<<endl;
		cout<<"	Abertura dos portoes: ";
		cout<<showsDisponiveis[i]->getAberturaPortoes()<<endl;
		cout<<"	Artistas: ";
		for(int j=0;j<showsDisponiveis[i]->getArtistas().size();j++){
			cout<<showsDisponiveis[i]->getArtistas()[j];
			if(showsDisponiveis[i]->getArtistas().size()-j>1)cout<<", ";
		}
		cout<<"\n";
	}
}


int MaquinaShow::verificaIdEvento(int id){
	for(int i =0 ;i<this->showsDisponiveis.size();i++) if(showsDisponiveis[i]->getId()==id)return i;
	return -1;
}

bool MaquinaShow::realizaCompra(Adulto * &user, int qtdIngressos, int idEvento){
	float valorTotal=0;
	int loteAtual=0,precoAtual=0;
	int aux = qtdIngressos;
	vector<int> ingressos = showsDisponiveis[idEvento]->getCapacidade();
	vector<int> precos = showsDisponiveis[idEvento]->getPrecos();
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
	
	int cota = this->showsDisponiveis[idEvento]->getQuotaIdoso();
	
	if(user->getSaldo()>=valorTotal){
		if(user->getTipo()=="Idoso"){//se for um Idoso
			if(cota>0){//Se tiver cota de idoso
				user->setSaldo(-valorTotal);
				this->showsDisponiveis[idEvento]->retiraCotaIdoso(qtdIngressos);
				for(int i=0;i<ingressos.size();++i){
					it1 = ingressosVendidos.find(showsDisponiveis[idEvento]);
					it2 = ingressosComprados.find(user);			
					if(ingressos[i]<qtdIngressos){
						this->showsDisponiveis[idEvento]->retiraCapacidade(ingressos[i],i);
						if(it1 == ingressosVendidos.end()){
							this->ingressosVendidos.insert(pair<Evento*, int>(showsDisponiveis[idEvento], ingressos[i]));						
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
						this->showsDisponiveis[idEvento]->retiraCapacidade(qtdIngressos,i);
						
						if(it1 == ingressosVendidos.end()){
							
							this->ingressosVendidos.insert(pair<Evento*, int>(showsDisponiveis[idEvento], qtdIngressos));						
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
			}
			else{//se não tiver cota de idoso
				user->setSaldo(-valorTotal);
				for(int i=0;i<ingressos.size();++i){
					it1 = ingressosVendidos.find(showsDisponiveis[idEvento]);
					it2 = ingressosComprados.find(user);			
					if(ingressos[i]<qtdIngressos){
						this->showsDisponiveis[idEvento]->retiraCapacidade(ingressos[i],i);
						if(it1 == ingressosVendidos.end()){
							this->ingressosVendidos.insert(pair<Evento*, int>(showsDisponiveis[idEvento], ingressos[i]));						
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
						this->showsDisponiveis[idEvento]->retiraCapacidade(qtdIngressos,i);
						
						if(it1 == ingressosVendidos.end()){
							
							this->ingressosVendidos.insert(pair<Evento*, int>(showsDisponiveis[idEvento], qtdIngressos));						
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
			}
		}else{//Se for um adulto
			if(showsDisponiveis[idEvento]->getCapacidadeTotal()-qtdIngressos>=cota){
				user->setSaldo(-valorTotal);
				for(int i=0;i<ingressos.size();++i){
					it1 = ingressosVendidos.find(showsDisponiveis[idEvento]);
					it2 = ingressosComprados.find(user);			
					if(ingressos[i]<qtdIngressos){
						this->showsDisponiveis[idEvento]->retiraCapacidade(ingressos[i],i);
						if(it1 == ingressosVendidos.end()){
							this->ingressosVendidos.insert(pair<Evento*, int>(showsDisponiveis[idEvento], ingressos[i]));						
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
						this->showsDisponiveis[idEvento]->retiraCapacidade(qtdIngressos,i);
						
						if(it1 == ingressosVendidos.end()){
							
							this->ingressosVendidos.insert(pair<Evento*, int>(showsDisponiveis[idEvento], qtdIngressos));						
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
			}
			else{
				cout<<"Impossivel realizar transacao, nao ha essa quatidade de ingressos para publico geral disponivel"<<endl;
				return false;
			}
		}
	}else{
		cout<<"Saldo Indiponivel"<<endl;
		return false;
	}
}

bool MaquinaShow::TelaInicial(Adulto* &user){
	int idEvento,qtdIngressos,qtd,hora,loteAtual,valorTotal=0;
	cout<<"Bem vindo(a) a tela de compra de ingressos de Shows, "<<user->getNome()<<endl;
	cout<<"Eventos disponiveis:"<<endl;
	this->exibeEventos();
	cout<<"Digite o id do evento que voce deseja: ";
	cin>>idEvento;
	idEvento=verificaIdEvento(idEvento);
	if(idEvento != -1){
		
		cout<<"Voce selecionou "<<showsDisponiveis[idEvento]->getNome()<<endl;
		cout<<"Digite a quantidade requerida de ingressos: ";
		cin>>qtdIngressos;
		if(qtdIngressos>showsDisponiveis[idEvento]->getCapacidadeTotal()){
			cout<<"Nao tem isso tudo de ingresso"<<endl;
			return false;
		}
		if(this->showsDisponiveis[idEvento]->getCapacidadeTotal()>0){//CONSERTAR !!!
			if(qtdIngressos>0){
				bool a = realizaCompra(user,qtdIngressos,idEvento);
				return a;
			}else{
				return false;
			}
		}else cout<<"Não ha mais ingressos"<<endl;
	}else cout<<"Id inexistente"<<endl;
	return false;
}