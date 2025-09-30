#include <iostream>
#include <vector>
#include "pilha.h" //DFS
#include "fila.h" //BFS
#include <locale>
#define TAM 100
using namespace std;

//adiciona arco/aresta
void adicionar(int mat[TAM][TAM], int i, int j, bool dirigido = false) {
    mat[i][j] = 1;
    if (!dirigido) {
        mat[j][i] = 1;
    }
}

void mostrar(int mat[TAM][TAM], int vert) {
    cout << "\nMatriz de Adjacência:\n";
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void DFS(int mat[TAM][TAM], int vert, int inicio, vector<string>& nomes) {
    vector<bool> visitado(vert, false); //marca os visitados
    TPilha<int> pilha;
    inicializa_pilha(pilha);
    int visitados = 0;

    cout << "\nDFS completa (a partir do vértice " << nomes[inicio] << "): ";

    //começa a DFS pelo vértice inicial dado
    insere_pilha(pilha, inicio);

    while (visitados < vert) {
        while (!vazia_pilha(pilha)) {
            int v = remove_pilha(pilha);
            //visita os que faltam
            if (!visitado[v]) {
                visitado[v] = true;
                visitados++;
                cout << nomes[v] << " ";

                for (int i = vert - 1; i >= 0; i--) {
                    if (mat[v][i] == 1 && !visitado[i]) 
                        insere_pilha(pilha, i);
                }
            }
        }

        if (vazia_pilha(pilha)) { //vértices não visitados + pilha vazia
            for (int i = 0; i < vert; i++) {
                if (!visitado[i]) {
                    insere_pilha(pilha, i);
                    break; 
                }
            }
        }
      }

    cout << endl;
}

void BFS(int mat[TAM][TAM], int vert, int inicio, vector<string>& nomes) {
    vector<bool> visitado(vert, false);
    TFila<int> fila;
    inicializa_fila(fila);
    int visitados = 0;

    cout << "\nBFS partindo do vértice " << nomes[inicio]  << ": ";
    while (visitados < vert) {
        if (fila.inicio == NULL) { //grafo desconectado
            for (int i = 0; i < vert; i++) {
                if (!visitado[i]) {
                    insere_fila(fila, i);
                    visitado[i] = true;
                    visitados++;
                    break;
                }
            }
        }
        while (fila.inicio != NULL) {
            int v = remove_fila(fila);
            cout << nomes[v] << " ";

            for (int i = 0; i < vert; i++) {
                if (mat[v][i] == 1 && !visitado[i]) {
                    insere_fila(fila, i);
                    visitado[i] = true;
                    visitados++;
                }
            }
        }
    }

    cout << endl;
}

void fecho_transi_direto(int mat[TAM][TAM], int vert, int inicio, vector<string>& nomes) {
    vector<bool> visitado(vert, false);
    vector<int> distancia(vert, -1); //distancia a partir do vertice
    TFila<int> fila;
    inicializa_fila(fila);

    insere_fila(fila, inicio);
    visitado[inicio] = true;
    distancia[inicio] = 0;

    cout << "\nFecho Transitivo Direto partindo do vértice " << nomes[inicio]  << ": \n";
    cout << nomes[inicio] << " (comprimento " << distancia[inicio] << ")\n";

    while (fila.inicio != NULL) {
        int v = remove_fila(fila);
        
        for (int i = 0; i < vert; i++) {
            if (mat[v][i] == 1 && !visitado[i]) {
                insere_fila(fila, i);
                visitado[i] = true;
                distancia[i] = distancia[v] + 1;
                cout << nomes[i] << " (comprimento " << distancia[i] << ")\n";
            }
        }
    }

    cout << endl;
}

void fecho_transi_indireto(int mat[TAM][TAM], int vert, int inicio, vector<string>& nomes) {
    //transpoem matriz adjacencia
    int mat_transposta[TAM][TAM] = {0};
    for (int i=0; i<vert; i++){
        for (int j=0; j<vert; j++)
            mat_transposta[i][j] = mat[j][i];
    }

    vector<bool> visitado(vert, false);
    vector<int> distancia(vert, -1);
    TFila<int> fila;
    inicializa_fila(fila);

    insere_fila(fila, inicio);
    visitado[inicio] = true;
    distancia[inicio] = 0;

    cout << "\nFecho Transitivo Indireto partindo do vértice " << nomes[inicio]  << ": ";
    cout << nomes[inicio] << " (comprimento " << distancia[inicio] << ")\n";

    while (fila.inicio != NULL) {
        int v = remove_fila(fila);
        
        for (int i = 0; i < vert; i++) {
            if (mat_transposta[v][i] == 1 && !visitado[i]) {
                insere_fila(fila, i);
                distancia[i] = distancia[v]+1;
                cout << nomes[i] << " (comprimento " << distancia[i] << ")\n";
                visitado[i] = true;
            }
        }
    }

    cout << endl;
}

bool verticeExiste(int v, int totalVertices) {
    return v >= 1 && v <= totalVertices;
}

int indiceVertice( vector<string>& nomes, string v) {
    for (int i = 0; i < (int)nomes.size(); i++) {
        if (nomes[i] == v)
            return i;
    }
    return -1; 
}

void inserirVertice(int mat[TAM][TAM], vector<string>& nomes, int& vert) {
    if (vert >= TAM) {
        cout << "Número máximo de vértices atingido!" << endl;
        return;
    }

    string nome;
    cout << "Digite o nome do novo vértice: ";
    cin >> nome;

    nomes.push_back(nome);
    //inicializa linhas e colunas com 0
    for (int i = 0; i <= vert; i++) {
        mat[vert][i] = 0;
        mat[i][vert] = 0;
    }

    vert++;
    cout << "Vértice " << nome << " inserido com sucesso!" << endl;
}

void editarNomeVertice(vector<string>& nomes, int vert){
    string nome, nome_alterado;
    cout << "Digite o nome do vértice que deseja alterar:"<< endl;
    cin>>nome;
    int encontrado = -1;
    for (int i=0; i<vert; i++){
        if (nomes[i] == nome)
            encontrado = i;
    }
    if(encontrado == -1)
        cout<< "Não encontrado" << endl;
    else{
        cout << "Digite o nome do novo vértice:"<< endl;
        cin>>nome_alterado;
        nomes[encontrado] = nome_alterado;
        cout << "Alterado com sucesso" << endl;
    }
}

void editarConexao(int mat[TAM][TAM], vector<string>& nomes, bool dirigido){
    string v1, v2, v1_alterado, v2_alterado;
    cout << "Digite os vértices da conexão que deseja alterar:" << endl;
    cout << "v1 atual: ";
    cin >> v1;
    cout << "v2 atual: ";
    cin >> v2;

    cout << "Digite os novos vértices da conexão:" << endl;
    cout << "v1 novo: ";
    cin >> v1_alterado;
    cout << "v2 novo: ";
    cin >> v2_alterado;

    int i_vert = indiceVertice(nomes, v1);
    int j_vert = indiceVertice(nomes, v2);
    int i_vert_alterado = indiceVertice(nomes, v1_alterado);
    int j_vert_alterado = indiceVertice(nomes, v2_alterado);

    if (i_vert == -1 || j_vert == -1) {
        cout << "Algum vértice inválido!" << endl;
    } else {//remove antiga e adiciona nova
        mat[i_vert][j_vert] = 0;
        if (!dirigido) 
            mat[j_vert][i_vert] = 0;

        adicionar(mat, i_vert_alterado, j_vert_alterado, dirigido);
        cout << "Alterado com sucesso!" << endl;
    }
}

void removerVertice(int mat[TAM][TAM], vector<string>& nomes, int& vert){
    string nome;
    cout << "Digite o nome do vértice que deseja remover:"<< endl;
    cin>>nome;
    int pos = indiceVertice(nomes, nome);
    if (pos == -1) {
        cout << "Vértice não encontrado!" << endl;
        return;
    }

    //remove linha
    for (int i=pos; i<vert-1; i++){
        for (int j=0; j<vert; j++){
            mat[i][j] = mat[i+1][j];
        }
    }
    //remover coluna
    for (int j=pos; j<vert-1; j++){
        for (int i=0; i<vert; i++){
            mat[i][j] = mat[i][j+1];
        }
    }

    //remove o nome
    nomes.erase(nomes.begin() + pos);
    vert--;
    cout << "Vértice removido com sucesso" << endl;

}

void removerConexao(int mat[TAM][TAM], vector<string>& nomes, bool dirigido){
    string v1, v2;
    cout << "Digite os vértices da conexão que deseja remover:" << endl;
    cout << "v1: ";
    cin >> v1;
    cout << "v2: ";
    cin >> v2;

    int i_vert = indiceVertice(nomes, v1);
    int j_vert = indiceVertice(nomes, v2);

    if (i_vert == -1 || j_vert == -1) {
        cout << "Algum vértice inválido!" << endl;
    } else {//remove antiga
        mat[i_vert][j_vert] = 0;
        if (!dirigido) 
            mat[j_vert][i_vert] = 0;
    }
    cout << "Conexão removida com sucesso" << endl;
}

void verifica_componentes(int mat[TAM][TAM], int vert, vector<string>& nomes) {
    vector<bool> visitado(vert, false);
    TFila<int> fila;
    int comp = 0;

    for (int i = 0; i < vert; i++) {
        if (!visitado[i]) { //novo componente
            comp++;
            cout << "Componente " << comp << ": " << endl;
            
            inicializa_fila(fila);
            insere_fila(fila, i);
            visitado[i] = true;

            vector<int> distancia(vert, -1); //guarda distancia do vertice inicial
            distancia[i] = 0;
            //BFS
            while (fila.inicio != NULL) {
                int v = remove_fila(fila);
                cout << nomes[v] << " (distância " << distancia[v] << ")  ";

                for (int j = 0; j < vert; j++) {
                    if (mat[v][j] == 1 && !visitado[j]) {
                        insere_fila(fila, j);
                        visitado[j] = true;
                        distancia[j] = distancia[v] + 1;
                    }
                }
            }
            cout << endl << endl;
        }
    }
    if (comp == 1)
        cout << "O grafo é conexo." << endl;
    else
        cout << "O grafo possui " << comp << " componentes desconexos." << endl;
}

void mostrarSubgrafos(int mat[TAM][TAM], int vert, vector<string>& nomes) {
    vector<bool> visitado(vert, false);
    int contador = 0;

    //transposta para o transitivo inverso
    int mat_transposta[TAM][TAM] = {0};
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            mat_transposta[i][j] = mat[j][i];
        }
    }

    for (int i = 0; i < vert; i++) {
        if (!visitado[i]) {
            contador++;

            // Fecho direto
            vector<bool> direto(vert, false);
            TFila<int> fila;
            inicializa_fila(fila);
            insere_fila(fila, i);
            direto[i] = true;
            while (fila.inicio != NULL) {
                int v = remove_fila(fila);
                for (int j = 0; j < vert; j++) {
                    if (mat[v][j] == 1 && !direto[j]) {
                        insere_fila(fila, j);
                        direto[j] = true;
                    }
                }
            }

            // Fecho inverso
            vector<bool> inverso(vert, false);
            inicializa_fila(fila);
            insere_fila(fila, i);
            inverso[i] = true;
            while (fila.inicio != NULL) {
                int v = remove_fila(fila);
                for (int j = 0; j < vert; j++) {
                    if (mat_transposta[v][j] == 1 && !inverso[j]) {
                        insere_fila(fila, j);
                        inverso[j] = true;
                    }
                }
            }

            // Interseção
            cout << "Subgrafo " << contador << ": ";
            for (int j = 0; j < vert; j++) {
                if (direto[j] && inverso[j]) {
                    cout << nomes[j] << " ";
                    visitado[j] = true; // marca como já visto
                }
            }
            cout << endl;
        }
    }

    if (contador == 1)
        cout << "O grafo é fortemente conexo.\n";
    else
        cout << "O grafo possui " << contador << " subgrafos fortemente conectados.\n";
}


void exibirMenu() {
    cout << "\nMENU:" << endl;
    cout << "1 - Inserir conexão (aresta/arco)" << endl;
    cout << "2 - Matriz de adjacência" << endl;
    cout << "3 - DFS" << endl;
    cout << "4 - BFS" << endl;
    cout << "5 - Fecho transitivo direto" << endl;
    cout << "6 - Fecho transitivo indireto" << endl;
    cout << "7 - Verificar existência de vértice" << endl;
    cout << "8 - Editar" << endl;
    cout << "9 - Remover" << endl;
    cout << "10 - Conectividade / Componentes" << endl;
    cout << "11 - Inserir vértice " << endl; 
    cout << "0 - Sair" << endl;
    cout << "Escolha uma opção: ";
}

int main() {
   setlocale(LC_ALL,"Portuguese");

    int vert;
    int mat[TAM][TAM] = {0};
    bool dirigido;
    vector<string> nomes;
    
    cout<<"Montando o Grafo"<<endl;

    cout << "Insira o número de vértices: ";
    cin >> vert;

    if (vert > TAM || vert <= 0) {
        cout << "Número inválido!" << endl;
        return 1;
    }

    cout << "O grafo é dirigido? (1-SIM, 0-NÃO): ";
    cin >> dirigido;

    nomes.resize(vert);
    for (int i = 0; i < vert; i++) {
        cout << "Insira o nome do vértice [" << i << "]: ";
        cin >> nomes[i];
    }

    int opcao;
    string nomeV1, nomeV2, inicioNome, buscar;

    do {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: { 
                cout << "v1: ";
                cin >> nomeV1;
                cout << "v2: ";
                cin >> nomeV2;

                int v1 = indiceVertice(nomes, nomeV1);
                int v2 = indiceVertice(nomes, nomeV2);

                if (v1 == -1 || v2 == -1) {
                    cout << "Vértices inválidos!" << endl;
                } else {
                    adicionar(mat, v1, v2, dirigido);
                    cout << "Conexão adicionada!" << endl;
                }
                break;
            }
            case 2: { 
                mostrar(mat, vert);
                break;
            }
            case 3: { 
                cout << "Informe o vértice inicial (nome): ";
                cin >> inicioNome;
                int inicio = indiceVertice(nomes, inicioNome);
                if (inicio == -1) 
                    cout << "Vértice inválido!" << endl;
                else 
                    DFS(mat, vert, inicio, nomes);
                break;
            }
            case 4: { 
                cout << "Informe o vértice inicial (nome): ";
                cin >> inicioNome;
                int inicio = indiceVertice(nomes, inicioNome);
                if (inicio == -1) 
                    cout << "Vértice inválido!" << endl;
                else 
                    BFS(mat, vert, inicio, nomes);
                break;
            }
            case 5: {
                cout << "Informe o vértice inicial (nome): ";
                cin >> inicioNome;
                int inicio = indiceVertice(nomes, inicioNome);
                if (inicio == -1) 
                    cout << "Vértice inválido!" << endl;
                else 
                    fecho_transi_direto(mat, vert, inicio, nomes);
                break;
            }
            case 6: { 
                cout << "Informe o vértice inicial (nome): ";
                cin >> inicioNome;
                int inicio = indiceVertice(nomes, inicioNome);
                if (inicio == -1) 
                    cout << "Vértice inválido!" << endl;
                else 
                    fecho_transi_indireto(mat, vert, inicio, nomes);
                break;
            }
            case 7: { 
                cout << "Digite o nome de um vértice para verificar se ele existe: ";
                cin >> buscar;
                if (indiceVertice(nomes, buscar) != -1)
                    cout << "O vértice " << buscar << " existe no grafo." << endl;
                else
                    cout << "O vértice " << buscar << " não existe no grafo." << endl;
                break;
            }
            case 8: { 
                int opcao_editar;
                cout << "1 - Nome do vértice" << endl;
                cout << "2 - Conexão" << endl;
                cin >> opcao_editar;
                if (opcao_editar == 1){
                    editarNomeVertice(nomes, vert);
                }else if(opcao_editar == 2){
                    editarConexao(mat, nomes, dirigido);
                }else{
                    cout <<"Inválido" << endl;
                }
                break;
            }
            case 9: { 
                int opcao_remover;
                cout << "1 - Vértice" << endl;
                cout << "2 - Conexão" << endl;
                cin >> opcao_remover;
                if (opcao_remover == 1)
                    removerVertice(mat, nomes, vert);
                else if (opcao_remover == 2){
                    removerConexao(mat,nomes, dirigido);
                }else
                    cout << "Inválido" << endl;
                break;
            }
            case 10: {
                   if (!dirigido)
                    verifica_componentes(mat, vert, nomes);
                else
                    mostrarSubgrafos(mat, vert, nomes);
                break;
            }
            case 11:{
                inserirVertice(mat, nomes, vert);
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }

    } while (opcao != 0);

    return 0;
}