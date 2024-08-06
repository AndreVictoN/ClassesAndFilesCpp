/*
 * AndreNascimentoInfo2_Prova2_1Bimestre.cpp
 *
 *  Created on: 16 de jul. de 2024
 *      Author: user
 */


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Pet{
public:
	int code;
	string nome;
	string tipo;
	string raca;
	char genero;
	float valor;

	Pet(){
		code = 0;
		nome = "";
		tipo = "";
		raca = "";
		genero = '\0';
		valor = 0.0;
	}

	Pet(int newCode, string newNome, string newTipo, string newRaca, char newGenero, float newValor){
		code = newCode;
		nome = newNome;
		tipo = newTipo;
		raca = newRaca;
		genero = newGenero;
		valor = newValor;
	}

	void imprimir(){
		stringstream campos;

		campos << code << ";" << nome << ";" << tipo << ";" << raca << ";" << genero << ";" << valor;

		cout << campos.str() << endl;
	}
};

vector<Pet> carregaDados(string caminho){
	vector<Pet> pets;

	int petCode;
	string petNome, petTipo, petRaca;
	char petGenero;
	float petValor;

	fstream arquivo(caminho.c_str());

	if(!arquivo.is_open()){
		cout << "Erro ao abrir arquivo" << endl;

		return pets;
	}

	string linhas;

	while(getline(arquivo, linhas)){
		if(linhas[0] != 'c'){
			replace(linhas.begin(), linhas.end(), ' ', '_');
			replace(linhas.begin(), linhas.end(), ';',' ');
			replace(linhas.begin(), linhas.end(), '"', ' ');
			replace(linhas.begin(), linhas.end(), ',', '.');

			stringstream linha(linhas);

			linha >> petCode >> petNome >> petTipo >> petRaca >> petGenero >> petValor;

			Pet pet(petCode, petNome, petTipo, petRaca, petGenero, petValor);

			pets.push_back(pet);
		}
	}

	arquivo.close();

	return pets;
}

float somaValor(vector<Pet> pets, string tipo){
	float somaValores;


	if(tipo == "cao"){
		for(size_t i = 0; i < pets.size(); i++){

			if(pets[i].tipo == tipo){
				somaValores += pets[i].valor;
			}

		}
	}

	if(tipo == "gato"){
		for(size_t i = 0; i < pets.size(); i++){
			if(pets[i].tipo == tipo){
				somaValores += pets[i].valor;
			}
		}
	}

	return somaValores;
}

int calculaPares(vector<Pet> pets, string tipoPet){
	int pares;
	int numeroGatoM = 0;
	int numeroGatoF = 0;
	int numeroCaoM = 0;
	int numeroCaoF = 0;

	for(size_t i = 0; i < pets.size(); i++){
		if(pets[i].genero == 'M'){
			if(pets[i].tipo == "gato"){
				numeroGatoM++;
			}else if(pets[i].tipo == "cao"){
				numeroCaoM++;
			}
		}else if(pets[i].genero == 'F' || pets[i].tipo == "gato"){
			if(pets[i].tipo == "gato"){
				numeroGatoF++;
			}else if(pets[i].tipo == "cao"){
				numeroCaoF++;
			}
		}
	}

	int paresG = numeroGatoM * numeroGatoF;
	int paresC = numeroCaoM * numeroCaoF;

	if(tipoPet == "gato"){
		pares = paresG;
	}else if(tipoPet == "cao"){
		pares = paresC;
	}

	return pares;
}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);

	string diretorio = "pets.csv";

	vector<Pet> pets = carregaDados(diretorio);

	float somaCao, somaGato;

	if(pets.empty()){
		return 0;
	}

	for(size_t i = 0; i < pets.size(); i++){
		pets[i].imprimir();
	}

	for(size_t i = 0; i < pets.size(); i++){
		if(pets[i].tipo == "cao"){
			somaCao = somaValor(pets, pets[i].tipo);
		}

		if(pets[i].tipo == "gato"){
			somaGato = somaValor(pets, pets[i].tipo);
		}
	}

	cout << endl << "Soma dos valores de cães: " << somaCao << endl << "Soma dos valores de gatos: " << somaGato << endl;

	int paresC;
	int paresG;

	for(size_t i = 0; i < pets.size(); i++){
		if(pets[i].tipo == "gato"){
			paresG = calculaPares(pets, "gato");
		}else if(pets[i].tipo == "cao"){
			paresC = calculaPares(pets, "cao");
		}
	}

	cout << "Pares de cães: " << paresC << endl << "Pares de Gatos: " << paresG << endl;

	return 0;
}
