#include <iostream>
#include <fstream> 
using namespace std;

struct timesDaNBA {

    int identificador;
    string nomeDoTime;
    string nomeDosJogadores;
    int numeroDeTitulos;
    float mediaDePontos;
    
};

	/*Lê os dados armazenados no arquivo e aloca em um vetor dinâmico*/

void Leitor(timesDaNBA* times, int tamanho){
	
	ifstream arquivo("timesDaNBA.csv");
	
		if(!arquivo){
			cout << "Arquivo não encontrado!";
		}
	char virgola;

		for(int i = 0; i < tamanho ; i++){
        
		arquivo >> times[i].identificador;
		arquivo >> virgola;
		getline(arquivo, times[i].nomeDoTime, ',');
		arquivo >> virgola;
		getline(arquivo,times[i].nomeDosJogadores,'"');
		arquivo >> virgola;
		arquivo >> times[i].numeroDeTitulos;
		arquivo >> virgola;
		arquivo >> times[i].mediaDePontos;
		}
	
	}
	
void GravarInformacoes(){
	
		/*Essa função deve ser capaz de gravar novas informaçoẽs com idenficador nome do time
		 * nome dos jogadores numero de titulos, e media de pontos, e atualizar a lista
		 */
	
	}
	

int main(){
	
	int tamanho = 40;
	timesDaNBA* times = new timesDaNBA[tamanho];
	
	Leitor(times,tamanho);
	
	
	
	
	return 0;
	}