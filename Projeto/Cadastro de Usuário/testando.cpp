#include<iostream> // Para entrada e saída padrão (cin, cout).
#include<fstream> // Para manipulação de arquivos (fstream, ofstream).
#include<string> // Para trabalhar com strings (usando a classe string).
using namespace std;
void cadastrarUsuario(){
    string nome;
    int idade;
    // Abrindo o arquivo em modo append para adicionar novos usuários
    ofstream arquivo("usuarios.txt", ios::app);
    if(!arquivo){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return;
    }
    cout<<"Digite o nome do usuário: ";
    getline(cin, nome);
    cout<<"Digite a idade do usuário: ";
    cin>>idade;
    cin.ignore(); // Limpar o buffer do cin.
    // Escrever os dados no arquivo.
    arquivo<<nome<<","<<idade<<endl;
    cout<<"Usuário cadastrado com sucesso!"<<endl;
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
    cout<<"\nLista de usuários cadastrados:\n";
    while(getline(arquivo, nome, ',')&&arquivo>>idade){
        arquivo.ignore(); // Ignorar a quebra de linha.
        cout<<"Nome: "<<nome<<", Idade: "<<idade<<endl;
    }
    arquivo.close();
}
void excluirUsuario(){
    string nomeExcluir;
    cout<<"Digite o nome do usuário a ser excluído: ";
    getline(cin, nomeExcluir);
    ifstream arquivo("usuarios.txt");
    ofstream temp("temp.txt"); // Arquivo temporário para reescrever os dados.
    if(!arquivo||!temp){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return;
    }
    string nome;
    int idade;
    bool encontrado = false;
    // Ler o arquivo original e copiar para o arquivo temporário.
    while(getline(arquivo, nome, ',')&&arquivo>>idade){
        arquivo.ignore(); // Ignorar a quebra de linha.
        if(nome!=nomeExcluir){
            // Se o nome não for o que queremos excluir, copiar para o arquivo temporário.
            temp<<nome<<","<<idade<<endl;
        }else{
            encontrado=true; // Encontramos o usuário a ser excluído.
        }
    }
    arquivo.close();
    temp.close();
    // Se o usuário foi encontrado, substituímos o arquivo original pelo temporário.
    if(encontrado){
        remove("usuarios.txt"); // Apagar o arquivo original.
        rename("temp.txt", "usuarios.txt"); // Renomear o arquivo temporário para o nome do arquivo original.
        cout<<"Usuário excluído com sucesso!"<<endl;
    }else{
        cout<<"Usuário não encontrado!"<<endl;
        remove("temp.txt"); // Se não encontrou, apaga o arquivo temporário.
    }
}
int main(){
    int escolha;
    do{
        cout<<"\nMenu de opções:\n";
        cout<<"1. Cadastrar usuário\n";
        cout<<"2. Listar usuários\n";
        cout<<"3. Excluir usuário\n";
        cout<<"4. Sair\n";
        cout<<"Escolha uma opção: ";
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
                cout<<"Opção inválida!\n";
        }
    }while(escolha!=4);
    return 0;
}
