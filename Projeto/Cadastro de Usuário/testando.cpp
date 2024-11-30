#include<iostream> // Para entrada e sa�da padr�o (cin, cout).
#include<fstream> // Para manipula��o de arquivos (fstream, ofstream).
#include<string> // Para trabalhar com strings (usando a classe string).
using namespace std;
void cadastrarUsuario(){
    string nome;
    int idade;
    // Abrindo o arquivo em modo append para adicionar novos usu�rios
    ofstream arquivo("usuarios.txt", ios::app);
    if(!arquivo){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return;
    }
    cout<<"Digite o nome do usu�rio: ";
    getline(cin, nome);
    cout<<"Digite a idade do usu�rio: ";
    cin>>idade;
    cin.ignore(); // Limpar o buffer do cin.
    // Escrever os dados no arquivo.
    arquivo<<nome<<","<<idade<<endl;
    cout<<"Usu�rio cadastrado com sucesso!"<<endl;
    arquivo.close();
}
void listarUsuarios(){
    ifstream arquivo("usuarios.txt");
    string nome;
    int idade;
    if(!arquivo){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return;
    }
    cout<<"\nLista de usu�rios cadastrados:\n";
    while(getline(arquivo, nome, ',')&&arquivo>>idade){
        arquivo.ignore(); // Ignorar a quebra de linha.
        cout<<"Nome: "<<nome<<", Idade: "<<idade<<endl;
    }
    arquivo.close();
}
void excluirUsuario(){
    string nomeExcluir;
    cout<<"Digite o nome do usu�rio a ser exclu�do: ";
    getline(cin, nomeExcluir);
    ifstream arquivo("usuarios.txt");
    ofstream temp("temp.txt"); // Arquivo tempor�rio para reescrever os dados.
    if(!arquivo||!temp){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return;
    }
    string nome;
    int idade;
    bool encontrado = false;
    // Ler o arquivo original e copiar para o arquivo tempor�rio.
    while(getline(arquivo, nome, ',')&&arquivo>>idade){
        arquivo.ignore(); // Ignorar a quebra de linha.
        if(nome!=nomeExcluir){
            // Se o nome n�o for o que queremos excluir, copiar para o arquivo tempor�rio.
            temp<<nome<<","<<idade<<endl;
        }else{
            encontrado=true; // Encontramos o usu�rio a ser exclu�do.
        }
    }
    arquivo.close();
    temp.close();
    // Se o usu�rio foi encontrado, substitu�mos o arquivo original pelo tempor�rio.
    if(encontrado){
        remove("usuarios.txt"); // Apagar o arquivo original.
        rename("temp.txt", "usuarios.txt"); // Renomear o arquivo tempor�rio para o nome do arquivo original.
        cout<<"Usu�rio exclu�do com sucesso!"<<endl;
    }else{
        cout<<"Usu�rio n�o encontrado!"<<endl;
        remove("temp.txt"); // Se n�o encontrou, apaga o arquivo tempor�rio.
    }
}
int main(){
    int escolha;
    do{
        cout<<"\nMenu de op��es:\n";
        cout<<"1. Cadastrar usu�rio\n";
        cout<<"2. Listar usu�rios\n";
        cout<<"3. Excluir usu�rio\n";
        cout<<"4. Sair\n";
        cout<<"Escolha uma op��o: ";
        cin>>escolha;
        cin.ignore(); // Limpar o buffer do cin.
        switch(escolha){
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                listarUsuarios();
                break;
            case 3:
                excluirUsuario();
                break;
            case 4:
                cout<<"Saindo...\n";
                break;
            default:
                cout<<"Op��o inv�lida!\n";
        }
    }while(escolha!=4);
    return 0;
}
