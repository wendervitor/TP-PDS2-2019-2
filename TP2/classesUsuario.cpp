#include "classesUsuario.h"

int Usuario::getID(){
	return this->id;
}
string Usuario::getNome(){
	return this->nome;
}
int Usuario::getIdade(){
	return this->idade;
}
float Usuario::getSaldo(){
	return this->saldo;
}
bool Usuario::setSaldo(float valor){
	if(valor<0 && valor>saldo) return false;
	else{
		this->saldo = this->saldo+valor;
		return true;
	}
}

void Adulto::addDependente(Crianca* c1){
	dependentes.push_back(c1);
}
vector<Crianca*> Adulto::getDependentes(){
	return this->dependentes;
}

Adulto* Crianca::getResponsavel(){
	return this->responsavel;
}

string Adulto::getTipo() {
	return "Adulto";
}
string Crianca::getTipo() {
	return "Crianca";
}
string Idoso::getTipo() {
	return "Idoso";
}