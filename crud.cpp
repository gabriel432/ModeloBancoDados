#include <iostream>
#include "string.h"
#include "stdio.h"
#include  "C:\Program Files\PostgreSQL\11\include\libpq-fe.h"
using namespace std;
int main()
{

    PGconn *conexao = PQconnectdb("host=localhost port=5432 dbname=republica user=gabriel password=gabriel"); // necessario alterar para valores específicos
    if (PQstatus(conexao) != CONNECTION_OK)
    {
        cout << "NÃO FOI POSSÍVEL ACESSAR O BANCO,SAINDO...";
        PQfinish(conexao);
        return 1;
    }
    string republica,idCaixinha,celularUsuario,descricaoCaixinha,res;
    int condicao,quantidadeTuplas,quantidadeAtributos;
    PGresult *resultado = NULL;
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
                cout << republica << endl;
                res = string("SELECT USUARIO.NOME,NICKNAME,CELULAR FROM USUARIO,REPUBLICA WHERE USUARIO.TELEFONE_REPUBLICA = REPUBLICA.TELEFONE AND REPUBLICA.NOME = \'" + republica + "\'");
                cout << res << endl;
                resultado = PQexec(conexao,res.c_str());
                if(PQresultStatus(resultado) != PGRES_TUPLES_OK)
                {
                    cout << "ALGO NÃO FUNCIONOU BEM...    " << PQerrorMessage(conexao);
                    PQclear(resultado);
                    PQfinish(conexao);
                    return 0;
                }
                quantidadeTuplas = PQntuples(resultado);
                quantidadeAtributos = PQnfields(resultado);
                cout << "NOME       NICKNAME        CELULAR" << quantidadeAtributos << " " << quantidadeTuplas << endl;
                for(int i = 0;i < quantidadeTuplas;i++){
                    for(int j = 0;j < quantidadeAtributos;j++)
                    {
                        try{
                        cout << "Be" << endl;
                        cout << PQgetlength(resultado,i,j) << " ";
                        PQgetvalue(resultado,i,j);
                        }
                        catch(exception msg)
                        {
                            cout << "BI" << endl;
                            cout << msg.what() << endl;
                        }
                    }
                    cout << endl;
                }
                PQclear(resultado);
                //PQfinish(conexao);                   
                break;
            case 2:
                cout << "INISIRA O CELULAR DO USUARIO E O ID DA CAIXINHA : ";
                cin >> celularUsuario >> idCaixinha;
                resultado = PQexec(conexao,strcat(strcat(strcat("SELECT VALOR_POR_MORADOR FROM USUARIO_PAGA_CAIXINHA WHERE ID_CAIXINHA ",idCaixinha.c_str())," AND CELULAR_USUARIO = "),celularUsuario.c_str()));
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
                //PQfinish(conexao);               
                break;
            case 3:
                cout << "INISIRA O CELULAR DO USUÁRIO : ";
                cin >> celularUsuario;
                resultado = PQexec(conexao,strcat(strcat("SELECT DESCRICAO,STATUS  FROM PROBLEMA,AFAZER WHERE PROBLEMA.CELULAR_USUARIO = ",celularUsuario.c_str())," AND PROBLEMA.ID_FAZER = AFAZER.ID_AFAZER"));
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
                //PQfinish(conexao);                   
                
                break;
            case 4:
                cout << "INISIRA O ID DA CAIXINHA E A NOVA DESCRICAO: ";
                cin >> idCaixinha >> descricaoCaixinha;
                resultado = PQexec(conexao,strcat(strcat(strcat("UPDATE CAIXINHA SET DESCRICAO = ",descricaoCaixinha.c_str())," WHERE ID_CAIXINHA = "),idCaixinha.c_str()));
                if(PQresultStatus(resultado) != PGRES_TUPLES_OK)
                {
                    cout << "ALGO NÃO FUNCIONOU BEM...    " << PQerrorMessage(conexao);
                    PQclear(resultado);
                    PQfinish(conexao);
                    return 0;
                }
                cout << "ATUALIZACAO REALIZADA COM SUCESSO! \n";
                PQclear(resultado);
                //PQfinish(conexao);                  
                break;
            case 0:
                PQfinish(conexao);
                return 0;
            default:
                cout << "valor inválido,digite novamente! \n ";
            } 
    }
}
