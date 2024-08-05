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
	
    ofstream gravar("timesDaNBA.csv", ios::app); // Abrir em modo append

		if (!gravar) {
			cout << "Erro ao abrir o arquivo para gravação!" << endl;
			return;
		}

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

    // Gravar no arquivo
    gravar << identificador << ','
           << nomeDoTime << ','
           << '"' << nomeDosJogadores << '"' << ','
           << numeroDeTitulos << ','
           << mediaDePontos << '\n';

    gravar.close();
    tamanhoAtual++;
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
    timesDaNBA* times = new timesDaNBA[capacidade];

    // Ler os dados do arquivo
    Leitor(times, capacidade, tamanhoAtual);

    // Exibir os dados lidos do arquivo
    ExibirInformacoes(times, tamanhoAtual);

    // Adicionar novas informações
    GravarInformacoes(times, capacidade, tamanhoAtual);

    // Exibir os dados atualizados na tela
    cout << "\nApós adicionar novo time:" << endl;
    ExibirInformacoes(times, tamanhoAtual);

    // Liberar a memória alocada
    delete[] times;

    return 0;
}
