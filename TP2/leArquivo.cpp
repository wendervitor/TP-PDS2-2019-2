#include "leArquivo.h"

void leUsuarios(string nome, vector<Adulto*> &Adultos, vector<Crianca*> &Criancas, vector<Idoso*> &Idosos, vector<Adulto*> &notCrianca){
	ifstream users(nome);

	if(!users.is_open()) cout<<"ERRO"<<endl;
	else{
		string linha;
		int id;
		string nome;
		int idade;
		float saldo;
		int id_responsavel;
		Adulto* responsavel;

		while (getline(users, linha)) {
	  		istringstream ss(linha);
			string token;
			getline(ss, token, ',');
			id = stoi(token);
			getline(ss, token, ',');
			if(token == "adulto"){
				getline(ss, token, ',');
				nome = token;
				getline(ss, token, ',');
				idade = stoi(token);
				getline(ss, token, ',');
				saldo = stof(token);
				Adulto* a1 = new Adulto(id,nome,idade,saldo);
				Adultos.push_back(a1);
				notCrianca.push_back(a1);
			}
			else if(token == "idoso"){
				getline(ss, token, ',');
				nome = token;
				getline(ss, token, ',');
				idade = stoi(token);
				getline(ss, token, ',');
				saldo = stof(token);
				Idoso* i1 = new Idoso(id,nome,idade,saldo);
				Idosos.push_back(i1);
				notCrianca.push_back(i1);
			}
			else if(token=="crianca"){
				getline(ss, token, ',');
				nome = token;
				getline(ss, token, ',');
				idade = stoi(token);
				getline(ss, token, ',');
				saldo = stof(token);
				getline(ss, token, ',');
				id_responsavel = stoi(token);
				for(int i=0;i<Adultos.size();i++) if(Adultos[i]->getID()==id_responsavel) responsavel = Adultos[i];
				Crianca* c1 = new Crianca(id,nome,idade,saldo,responsavel);
				for(int i=0;i<Adultos.size();i++) if(Adultos[i]->getID()==id_responsavel) Adultos[i]->addDependente(c1);
				Criancas.push_back(c1);
			}
			else{}
		}
	}

	users.close();
}

void leEventos(string nome,vector<Cinema*> &Cinemas, vector<TeatroFantoche*> &teatros,vector<Boate*> &boates,vector<Show*> &shows, vector<Adulto*> &notCrianca){
	ifstream events(nome);

	if(!events.is_open()) cout<<"ERRO"<<endl;
	else{
		string linha;
		int id;
		string categ;
		string subcateg;
		string nome;
		int id_dono;
		int num_tipos;
		Usuario* dono;
		int cap;
		int valor;
		int horario;
		int duracao;
		int quota_idoso;
		int aberturaPortoes;
		int hora_inicio;
		int hora_fim;
		int *capa;
		vector<string> artistas;
		int horarios[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

		while (getline(events, linha)) {
	  		
			istringstream ss(linha);
			string token;
			getline(ss, token, ',');
			id = stoi(token);
			getline(ss, token, ',');
			
			if(token == "infantil"){
				getline(ss, token, ',');
				subcateg = token;
				if(subcateg == "fantoche"){
					getline(ss, token, ',');
					nome = token;
					getline(ss, token, ',');
					id_dono = stoi(token);
					for(int i=0;i<notCrianca.size();i++)if(id_dono==notCrianca[i]->getID())dono=notCrianca[i];
					getline(ss, token, ',');
					num_tipos = stoi(token);
					vector<int>capacidade;
					vector<int>precos;
					vector<int>horarios;
					for(int i=0;i<num_tipos;i++){
						getline(ss, token, ',');
						cap = stoi(token);
						capacidade.push_back(cap);
						getline(ss, token, ',');
						valor = stoi(token);
						precos.push_back(valor);
					}
					while(getline(ss, token, ',')){
						horario=stoi(token);
						horarios.push_back(horario);
					}
					TeatroFantoche* t1= new TeatroFantoche(id,nome,dono,capacidade,precos,horarios);
					teatros.push_back(t1);
				}
				else{

				}
				
			}
			else if(token == "cinema"){
				getline(ss, token, ',');
				nome = token;
				getline(ss, token, ',');
				id_dono = stoi(token);
				for(int i=0;i<notCrianca.size();i++)if(id_dono==notCrianca[i]->getID())dono=notCrianca[i];
				getline(ss, token, ',');
				num_tipos = stoi(token);
				vector<int>capacidade;
				vector<int>precos;
				vector<int>horarios;
				for(int i=0;i<num_tipos;i++){
					getline(ss, token, ',');
					cap = stoi(token);
					capacidade.push_back(cap);
					getline(ss, token, ',');
					valor = stoi(token);
					precos.push_back(valor);
				}
				getline(ss, token, ',');
				do{
					horario=stoi(token);
					if(stoi(token)){
						horarios.push_back(horario);
					}else{
						duracao=horario;
						horarios.pop_back();
					}
				}while(getline(ss, token, ','));
				duracao=horarios[horarios.size()-1];
				horarios.pop_back();
				Cinema *c1= new Cinema(id,nome,dono,capacidade,precos,horarios,duracao);
				Cinemas.push_back(c1);
			}
			else if(token=="adulto"){
				getline(ss, token, ',');
				subcateg = token;
				if(subcateg=="show"){
					getline(ss, token, ',');
					nome=token;
					getline(ss, token, ',');
					id_dono = stoi(token);
					for(int i=0;i<notCrianca.size();i++)if(id_dono==notCrianca[i]->getID())dono=notCrianca[i];
					getline(ss, token, ',');
					num_tipos = stoi(token);
					vector<int>capacidade;
					vector<int>precos;
					vector<int>horarios;
					for(int i=0;i<num_tipos;i++){
						getline(ss, token, ',');
						cap = stoi(token);
						capacidade.push_back(cap);
						getline(ss, token, ',');
						valor = stoi(token);
						precos.push_back(valor);
					}
					getline(ss, token, ',');
					quota_idoso=stoi(token);
					getline(ss, token, ',');
					aberturaPortoes=stoi(token);
					while(getline(ss, token, ',')){
						artistas.push_back(token);
					}
					Show* s1 = new Show(id,nome,dono,capacidade,precos,quota_idoso,aberturaPortoes,artistas);
					shows.push_back(s1);

				}
				else if(subcateg == "boate"){
					getline(ss, token, ',');
					nome=token;
					getline(ss, token, ',');
					id_dono = stoi(token);
					for(int i=0;i<notCrianca.size();i++)if(id_dono==notCrianca[i]->getID()) dono=notCrianca[i];
					getline(ss, token, ',');
					num_tipos = stoi(token);
					vector<int>capacidade;
					vector<int>precos;
					vector<int>horarios;
					for(int i=0;i<num_tipos;i++){
						getline(ss, token, ',');
						cap = stoi(token);
						capacidade.push_back(cap);
						getline(ss, token, ',');
						valor = stoi(token);
						precos.push_back(valor);
					}
					getline(ss, token, ',');
					quota_idoso=stoi(token);
					getline(ss, token, ',');
					hora_inicio=stoi(token);
					getline(ss, token, ',');
					hora_fim=stoi(token);
					Boate* b1 = new Boate(id,nome,dono,capacidade,precos,quota_idoso,hora_inicio,hora_fim);
					boates.push_back(b1);
				}
				else{

				}
			}
			else{}

		}
	}

	events.close();
}