#include <iostream>
#include "string.h"
#include "stdio.h"
#include  "C:\Program Files\PostgreSQL\11\include\libpq-fe.h"
using namespace std;
int main()
{

    PGconn *conexao = PQconnectdb("host=localhost port=5432 dbname=empresa user=postgres password=postgres"); // necessario alterar para valores específicos
    if (PQstatus(conexao) != CONNECTION_OK)
    {
        cout << "NÃO FOI POSSÍVEL ACESSAR O BANCO,SAINDO...";
        PQfinish(conexao);
        return 1;
    }
    char* republica,*idCaixinha,*celularUsuario,*descricaoCaixinha;
    int condicao,quantidadeTuplas,quantidadeAtributos;
    PGresult *resultado;
    while(true){
        cout << "SISTEMA DE GERENCIAMENTO DE REPÚBLICAS : \n \
        PARA CONSULTAR OS USUÁRIOS CADASTRADOS,DIGITE 1 ; \n \
        PARA CONSULTAR O VALOR QUE UM USUÁRIO DEVE PAGAR Á UMA CAIXINHA,DIGITE 2 ; \n \
        PARA CONSULTAR OS TAREFAS DE UM USUÁRIO,DIGITE 3 ; \n \
        PARA ATUALIZAR A DESCRICAO DE UMA CAIXINHA,DIGITE 4 ; \n \
        PARA SAIR DIGITE 0 : ";

        cin >> condicao;
            switch (condicao){
            case 1:
                cout << "INISIRA O NOME DA REPÚBLICA : ";
                cin >> republica;
                resultado = PQexec(conexao,strcat("SELECT NOME,NICKNAME,CELULAR FROM USUARIO,REPUBLICA WHERE USUARIO.TELEFONE_REPUBLICA = REPUBLICA.TELEFONE AND REPUBLICA.NOME = " ,republica));
                if(PQresultStatus(resultado) != PGRES_TUPLES_OK)
                {
                    cout << "ALGO NÃO FUNCIONOU BEM...    " << PQerrorMessage(conexao);
                    PQclear(resultado);
                    PQfinish(conexao);
                    return 0;
                }
                quantidadeTuplas = PQntuples(resultado);
                quantidadeAtributos = PQnfields(resultado);
                cout << "NOME       NICKNAME        CELULAR" << endl;
                for(int i = 0;i < quantidadeTuplas;i++){
                    for(int j = 0;j < quantidadeAtributos;j++)
                    {
                        cout << PQgetvalue(resultado,i,j) << "     ";
                    }
                    cout << endl;
                }
                PQclear(resultado);
                PQfinish(conexao);                   
                break;
            case 2:
                cout << "INISIRA O CELULAR DO USUARIO E O ID DA CAIXINHA : ";
                cin >> celularUsuario >> idCaixinha;
                resultado = PQexec(conexao,strcat(strcat(strcat("SELECT VALOR_POR_MORADOR FROM USUARIO_PAGA_CAIXINHA WHERE ID_CAIXINHA ",idCaixinha)," AND CELULAR_USUARIO = "),celularUsuario));
                if(PQresultStatus(resultado) != PGRES_TUPLES_OK)
                {
                    cout << "ALGO NÃO FUNCIONOU BEM...    " << PQerrorMessage(conexao);
                    PQclear(resultado);
                    PQfinish(conexao);
                    return 0;
                }
                quantidadeTuplas = PQntuples(resultado);
                quantidadeAtributos = PQnfields(resultado);
                cout << "VALOR = " << PQgetvalue(resultado,0,0);
                PQclear(resultado);
                PQfinish(conexao);               
                break;
            case 3:
                cout << "INISIRA O CELULAR DO USUÁRIO : ";
                cin >> celularUsuario;
                resultado = PQexec(conexao,strcat(strcat("SELECT DESCRICAO,STATUS  FROM PROBLEMA,AFAZER WHERE PROBLEMA.CELULAR_USUARIO = ",celularUsuario)," AND PROBLEMA.ID_FAZER = AFAZER.ID_AFAZER"));
                if(PQresultStatus(resultado) != PGRES_TUPLES_OK)
                {
                    cout << "ALGO NÃO FUNCIONOU BEM...    " << PQerrorMessage(conexao);
                    PQclear(resultado);
                    PQfinish(conexao);
                    return 0;
                }
                quantidadeTuplas = PQntuples(resultado);
                quantidadeAtributos = PQnfields(resultado);
                for(int i = 0;i < quantidadeTuplas;i++){
                    for(int j = 0;j < quantidadeAtributos;j++)
                    {
                        if(i % 2)
                            cout << "DESCRICAO \n" << endl;
                        else
                            cout << "STATUS" << endl;
                        cout << PQgetvalue(resultado,i,j) << "     ";
                    }
                    cout << endl;
                }
                PQclear(resultado);
                PQfinish(conexao);                   
                
                break;
            case 4:
                cout << "INISIRA O ID DA CAIXINHA E A NOVA DESCRICAO: ";
                cin >> idCaixinha >> descricaoCaixinha;
                resultado = PQexec(conexao,strcat(strcat(strcat("UPDATE CAIXINHA SET DESCRICAO = ",descricaoCaixinha)," WHERE ID_CAIXINHA = "),idCaixinha));
                if(PQresultStatus(resultado) != PGRES_TUPLES_OK)
                {
                    cout << "ALGO NÃO FUNCIONOU BEM...    " << PQerrorMessage(conexao);
                    PQclear(resultado);
                    PQfinish(conexao);
                    return 0;
                }
                cout << "ATUALIZACAO REALIZADA COM SUCESSO! \n";
                PQclear(resultado);
                PQfinish(conexao);                  
                break;
            case 0:
                return 0;
            default:
                cout << "valor inválido,digite novamente! \n ";
            } 
    }
}
