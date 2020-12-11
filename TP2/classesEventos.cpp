#include "classesEventos.h"

int Evento::getId(){
	return this->id;
}
string Evento::getNome(){
	return this->nome;
}
Usuario* Evento::getResponsavel(){
	return this->responsavel;
}
vector<int> Evento::getCapacidade(){
	return this->capacidade;
}
int Evento::getCapacidadeTotal(){
	vector<int> cap = this->capacidade;
	int qtd=0;
	for(int i=0;i<cap.size();++i)qtd+=cap[i];
	return qtd;
}
void Evento::retiraCapacidade(int qtd,int loteAtual){
	this->capacidade[loteAtual]-=qtd;
}	

vector<int> Evento::getPrecos(){
	return this->precos;
}

vector<int> TeatroFantoche::getHorarios(){
	return this->horarios;
}

vector<int> Cinema::getHorarios(){
	return this->horarios;
}
int Cinema::getDuracao(){
	return this->duracao;
}

int EventoAdulto::getQuotaIdoso(){
	return this->quota_idoso;
}
void EventoAdulto::retiraCotaIdoso(int qtd){
	if(this->quota_idoso-qtd>=0)this->quota_idoso-=qtd;
	else this->quota_idoso=0;
}

int Boate::getHoraInicio(){
	return this->horaInicio;
}
int Boate::getHoraFim(){
	return this->horaFim;
}
int Show::getAberturaPortoes(){
	return this->aberturaPortoes;
}
vector<string> Show::getArtistas(){
	return this->artistas;
}

string TeatroFantoche::getTipo() {
	return "Teatro de Fantoches";
}
string Cinema::getTipo() {
	return "Cinemas";
}
string Boate::getTipo() {
	return "Boates";
}
string Show::getTipo() {
	return "Shows";
}