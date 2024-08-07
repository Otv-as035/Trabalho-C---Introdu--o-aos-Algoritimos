#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct timesDaNBA {
    int identificador;
    string nomeDoTime;
    string nomeDosJogadores;
    int numeroDeTitulos;
    float mediaDePontos;
};

void Redimensionar(timesDaNBA*& times, int& capacidade, int incremento) {
	
    timesDaNBA* novoArray = new timesDaNBA[capacidade + incremento];
    
    for (int i = 0; i < capacidade; i++) {
        novoArray[i] = times[i];
    }
    
    delete[] times;
    times = novoArray;
    capacidade += incremento;
}

/* Esse metodo de ordenação foi escolhido com base nos slides para aula até o momento
 * sugeito a alteração.*/
void insertion_sort(timesDaNBA* &times, int tamanho){
	
	int valor_pivo;
	int j;
	
		for(int i = 1; i < tamanho; i++){
			valor_pivo = times[i].numeroDeTitulos;
			timesDaNBA aux = times[i];
			j = i - 1; // Define a posição inicial para comparação
				
				while((j >= 0) and (valor_pivo < times[j].numeroDeTitulos)){
					times[j + 1].numeroDeTitulos = times[j].numeroDeTitulos;
					j--;
					}
			times[j+1] = aux; // Insere o time na posição correta
			}
	}

void Leitor(timesDaNBA*& times, int& capacidade, int& tamanhoAtual) {
    ifstream arquivo("timesDaNBA.csv");

    if (!arquivo) {
        cout << "Arquivo não encontrado!" << endl;
        return;
    }

    char virgula;
    int identificador;

    while (arquivo >> identificador) {
		
        if (tamanhoAtual >= capacidade) {
            Redimensionar(times, capacidade, 5); // Incremento de 5 posições
        }
        arquivo >> virgula;
        times[tamanhoAtual].identificador = identificador;
        getline(arquivo, times[tamanhoAtual].nomeDoTime, ',');
        arquivo >> virgula;
        getline(arquivo, times[tamanhoAtual].nomeDosJogadores, '"');
        arquivo >> virgula >> times[tamanhoAtual].numeroDeTitulos >> virgula;
        arquivo >> times[tamanhoAtual].mediaDePontos;

        tamanhoAtual++;
        
        insertion_sort(times, tamanhoAtual); /* Esta ordenado do menor para o maior
												desde quem tem memenos titulos até quem tem mais*/
    }
}

int ObterProximoIdentificador(timesDaNBA* times, int tamanhoAtual) {
	
    int maxIdentificador = 0;
    
    for (int i = 0; i < tamanhoAtual; i++) {
		
        if (times[i].identificador > maxIdentificador) {
            maxIdentificador = times[i].identificador;
        }
    }
    return maxIdentificador + 1;
}

void GravarInformacoes(timesDaNBA*& times, int& tamanho, int& tamanhoAtual) {
	
	if (tamanhoAtual == tamanho) {
		Redimensionar(times, tamanho, 5);
	}

    int identificador = ObterProximoIdentificador(times, tamanhoAtual);
    string nomeDoTime;
    string nomeDosJogadores;
    int numeroDeTitulos;
    float mediaDePontos;

    cout << "Digite o nome do time: ";
    getline(cin, nomeDoTime);

    cout << "Digite o nome dos jogadores (use aspas para delimitar): ";
    getline(cin, nomeDosJogadores);

    cout << "Digite o numero de titulos: ";
    cin >> numeroDeTitulos;
    cin.ignore(); // Limpar buffer de entrada

    cout << "Digite a media de pontos: ";
    cin >> mediaDePontos;
    cin.ignore(); // Limpar buffer de entrada

    // Adicionar ao vetor
    times[tamanhoAtual].identificador = identificador;
    times[tamanhoAtual].nomeDoTime = nomeDoTime;
    times[tamanhoAtual].nomeDosJogadores = nomeDosJogadores;
    times[tamanhoAtual].numeroDeTitulos = numeroDeTitulos;
    times[tamanhoAtual].mediaDePontos = mediaDePontos;
    tamanhoAtual++;
    
    insertion_sort(times,tamanhoAtual);   // Ordena o array após a inserção do novo time

    ofstream gravar("timesDaNBA.csv", ios::app); // Abrir em modo append
		if (!gravar) {
			cout << "Erro ao abrir o arquivo para gravação!" << endl;
			return;
		}
    // Gravar no arquivo
    gravar << identificador << ','
           << nomeDoTime << ','
           << '"' << nomeDosJogadores << '"' << ','
           << numeroDeTitulos << ','
           << mediaDePontos << '\n';

    gravar.close();

}

void RemoverTime(timesDaNBA*& times,int tamanhoAtual, int identificadorParaRemover){
	for(int i = 0; i < tamanhoAtual; i++){
		if(times[i].identificador == identificadorParaRemover){
			times[i].identificador = -1;
			cout << "Time removido com sucesso !" << endl;
			return;
			}
		}
	cout << "Time não encontrado." << endl;
	}
	

void ExibirInformacoes(timesDaNBA* times, int tamanhoAtual) {
	
    cout << "Lista de Times da NBA:" << endl;
    
		for (int i = 0; i < tamanhoAtual; i++) {
			
			cout << "Identificador: " << times[i].identificador << endl;
			cout << "Nome do Time: " << times[i].nomeDoTime << endl;
			cout << "Nome dos Jogadores: " << times[i].nomeDosJogadores << endl;
			cout << "Numero de Titulos: " << times[i].numeroDeTitulos << endl;
			cout << "Media de Pontos: " << times[i].mediaDePontos << endl;
			cout << "-------------------------------" << endl;
		}
}



int main() {
	
    int capacidade = 40;
    int tamanhoAtual = 0;
    int idParaRemover;
    timesDaNBA* times = new timesDaNBA[capacidade];

    // Ler os dados do arquivo
    Leitor(times, capacidade, tamanhoAtual);

    // Exibir os dados lidos do arquivo
    ExibirInformacoes(times, tamanhoAtual);

    // Adicionar novas informações
    GravarInformacoes(times, capacidade, tamanhoAtual);
    
    // Remover logicamente um time pelo identificador
    cout << "\nDigite o identificador do time a ser removido: ";
    cin >> idParaRemover;
    RemoverTime(times, tamanhoAtual, idParaRemover);

    // Exibir os dados atualizados na tela
    cout << "\nApós adicionar novo time:" << endl;
    ExibirInformacoes(times, tamanhoAtual);

    // Liberar a memória alocada
    delete[] times;

    return 0;
}

