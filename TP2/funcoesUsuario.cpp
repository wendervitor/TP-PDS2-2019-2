#include "funcoesUsuario.h"
#include "classesUsuario.h"
int verificaIdUsuario(int id, vector<Adulto*> &usuarios){
	for(int i=0;i<usuarios.size();++i)
		if(usuarios[i]->getID()==id) return id;
	return -1;
}

void imprimeUsuarios (vector<Adulto*> &Adultos, vector<Crianca*> &Criancas, vector<Idoso*> &Idosos){

		
		for(int j=0; j < Adultos.size(); j++ ){
			cout <<"	ID: "<< Adultos[j]->getID() << endl;
			cout <<"	Nome: "<< Adultos[j]->getNome() << endl;
			cout <<"	Saldo: "<< Adultos[j]->getSaldo() << endl;
			cout <<"	Categoria: Adulto\n" << endl;
		}
		
		for(int k=0; k < Idosos.size(); k++ ){
			cout <<"	ID: "<< Idosos[k]->getID() << endl;
			cout <<"	Nome: "<< Idosos[k]->getNome() << endl;
			cout <<"	Saldo: "<< Idosos[k]->getSaldo() << endl;
			cout <<"	Categoria: Idoso\n" << endl;
		}
		
		for(int i=0; i < Criancas.size(); i++ ){
			cout <<"	ID: "<< Criancas[i]->getID() << endl;
			cout <<"	Nome: "<< Criancas[i]->getNome() << endl;
			cout <<"	Saldo: "<<Criancas[i]->getSaldo() << endl;
			cout <<"	ID do Responsavel: " <<Criancas[i]->getResponsavel()->getID() << endl;
			cout <<"	Categoria: Crianca\n" << endl;
		}		
}

bool possuiDependentes(Adulto* &a,vector<Crianca*> &c){
	for(int i=0;i<c.size();i++) if(c[i]->getResponsavel() == a) return true;
	return false;
}

void imprimeDependentes(vector<Adulto*> &Adultos, vector<Crianca*> &Criancas){
	if(!Adultos.empty()){
		cout<<"getDependentes():"<<endl;
		for(int i=0;i<Adultos.size();i++){
			if(possuiDependentes(Adultos[i],Criancas)){
				Adultos[i]->getNome();
				cout<<" (ID: "<<Adultos[i]->getID();cout<<"): ";
				for(int j=0;j<Criancas.size();j++){
					if(Criancas[j]->getResponsavel() == Adultos[i]){
						cout<<Criancas[j]->getNome();
						cout<<" (ID: "<<Criancas[j]->getID();cout<<")";
						cout<<", ";
					}
				}
				cout<<endl;
			}
		}
	}
}

void qtdUsuarios(vector<Adulto*> &a, vector<Crianca*> &c, vector<Idoso*> &v){
	cout<<"Numero de Usuarios:"<<endl;
	cout<<"Criancas: ";
	int cont=0;
	for(int i=0;i<c.size();i++) cont++;
	cout<<cont<<endl;
	cont=0;
	cout<<"Adultos: ";
	for(int i=0;i<a.size();i++) cont++;
	cout<<cont<<endl;
	cont=0;
	cout<<"Idosos: ";
	for(int i=0;i<v.size();i++) cont++;
	cout<<cont<<endl;
	
}

void idade(vector<Adulto*> &a, vector<Crianca*> &c, vector<Idoso*> &v){

	cout<<"Idade dos Usuarios:"<<endl;
	cout<<"Minima: ";
	if(!c.empty())
	{
		int menor = c[0]->getIdade();
		for(int i=0;i<c.size();i++) {
	    	if(menor> c[i]->getIdade())
	        	menor= c[i]->getIdade(); }
		cout<<menor<<endl;
	}
	else if(!a.empty()){
		int menor = a[0]->getIdade();
		for(int i=0;i<a.size();i++) {
	    	if(menor> a[i]->getIdade())
	        	menor= a[i]->getIdade(); }
		cout<<menor<<endl;
	}
	else{
		int menor = v[0]->getIdade();
		for(int i=0;i<v.size();i++) {
	    	if(menor> v[i]->getIdade())
	        	menor= v[i]->getIdade(); }
		cout<<menor<<endl;
	}

	cout<<"Maxima: ";
	if(!v.empty()){
		int maior = v[0]->getIdade();
		for(int i=0;i<v.size();i++)  {
	        if(maior< v[i]->getIdade())
	            maior= v[i]->getIdade(); }
		cout<<maior<<endl;	
	}
	else if(!a.empty()){
		int maior = a[0]->getIdade();
		for(int i=0;i<a.size();i++)  {
	        if(maior< a[i]->getIdade())
	            maior= a[i]->getIdade(); }
		cout<<maior<<endl;	
	}
	else{
		int maior = c[0]->getIdade();
		for(int i=0;i<c.size();i++)  {
	        if(maior< c[i]->getIdade())
	            maior= c[i]->getIdade(); }
		cout<<maior<<endl;	
	}

	cout<<"Media: ";
	int cont1=0, cont2=0, cont3=0;
	for(int i=0;i<a.size();i++)
		{ cont1 = cont1+a[i]->getIdade() ;  }

	for(int i=0;i<c.size();i++)
		{ cont2 = cont2+c[i]->getIdade();  }

	for(int i=0;i<v.size();i++)
		{ cont3 = cont3+v[i]->getIdade();  }

	double soma = cont1+cont2+cont3;
	double totalPessoas = a.size()+c.size()+v.size();
	double media = (double) soma/totalPessoas;
	printf("%.2f\n",media);
}

void qtdDependentes(vector<Adulto*> &Adultos){

	cout<<"Numero de Dependentes:"<<endl;
	cout<<"Minimo: ";

	int minimo = Adultos[0]->getDependentes().size();
	for(int i=0;i<Adultos.size();i++) if(Adultos[i]->getDependentes().size() < minimo) minimo = Adultos[i]->getDependentes().size();		
	cout << minimo << endl;

	cout<<"Maximo: ";
	int maximo = Adultos[0]->getDependentes().size();
	for(int i=0;i<Adultos.size();i++) if(Adultos[i]->getDependentes().size() > maximo) maximo = Adultos[i]->getDependentes().size();
	cout << maximo << endl;


	cout<<"Media: ";
	int cont = 0;
	for(int i=0;i<Adultos.size();i++) cont+=Adultos[i]->getDependentes().size();
	double media = (double) cont/Adultos.size();
	printf("%.2f\n",media);
		
}
