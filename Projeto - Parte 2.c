#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  int matricula;
  char nome[30];
  int idade;
  float horas;
} ficha;

int main() {

  int inicio(), menuGerente(), menuFuncionario();
  void configurar(), cadastrar(), alterar(), remover(), imprimir(), cadastraHora(), verificar();
  
  switch (inicio()) {
    case 1:
      while (1) {
        switch (menuGerente()) {
          case 1: configurar();
          break;
          case 2: cadastrar();
          break;
          case 3: alterar();
          break;
          case 4: remover();
          break;
          case 5: imprimir();
          break;
          default: printf ("\nSessao encerrada\n"); exit(0);
        }
      }
    default:
      while (1) {
        switch (menuFuncionario()) {
          case 1: cadastraHora();
          break;
          case 2: verificar();
          break;
          default: printf ("\nSessao encerrada\n"); exit(0);
        }
      }   
  }  
}

// menu inicial

int inicio(){
  int chaveInicio;
  while (1) {
    printf ("\nIniciar sessao como:\n\nAdministrador: digite 1\nFuncionario: digite 2\n\nOpcao: ");

    scanf ("%i",&chaveInicio);

    if (chaveInicio == 1 || chaveInicio == 2) {
      return chaveInicio;
    }
    else {printf ("\nOpcao invalida. Tente novamente\n");}
  }
}

// menu do gerente

int menuGerente(){
  int chaveGerente;

  while (1) {

    printf ("\nMENU GERENTE\n\nDigite 1 para: Configurar o sistema\nDigite 2 para: Cadastro de funcionario\nDigite 3 para: Alteracao de informacoes de funcionario\nDigite 4 para: Remocao de funcionario\nDigite 5 para: Relatorios\nDigite 0 para: Encerrar sessão\n\nOpcao: ");
  
    scanf ("%i",&chaveGerente);

    if (chaveGerente == 1 || chaveGerente == 2 || chaveGerente == 3 || chaveGerente == 4 || chaveGerente == 5 || chaveGerente == 0) {
      return chaveGerente;
    }
    else {printf ("\nOpcao invalida. Tente novamente\n");}
  }
}

// modulo de configuracao

void configurar() {

  int vetorConfig[4];
  
  do {
    printf ("\nDigite o numero maximo de funcionarios da empresa: ");
    scanf ("%i",&vetorConfig[0]);
    if (vetorConfig[0] < 1) {printf ("\nOpcao invalida. Tente novamente\n");}
  } while (vetorConfig[0] < 1);

  do {
    printf ("\nDigite o numero de dias de trabalho: ");
    scanf ("%i",&vetorConfig[1]);
    if (vetorConfig[1] < 1) {printf ("\nOpcao invalida. Tente novamente\n");}
  } while (vetorConfig[1] < 1);

  do {
    printf ("\nDigite a quantidade de horas diarias de trabalho: ");
    scanf ("%i",&vetorConfig[2]);
    if (vetorConfig[2] < 1) {printf ("\nOpcao invalida. Tente novamente\n");}
  } while (vetorConfig[2] < 1);

  do {
    printf ("\nDigite a quantidade maxima de horas diarias de trabalho: ");
    scanf ("%i",&vetorConfig[3]);
    if (vetorConfig[3] < 1) {printf ("\nOpcao invalida. Tente novamente\n");}
  } while (vetorConfig[3] < 1);

  printf ("\nConfiguracao concluida com sucesso\n");

  FILE *config;
  config = fopen ("configuracoes.txt", "w");
  
  for (int x = 0; x < 4; ++x) {
    fprintf (config,"%i ",vetorConfig[x]);
  }
  fclose(config);
}

// modulo de cadastro de funcionario

void cadastrar() {

  if (fopen("configuracoes.txt", "r") == NULL) { 
    printf ("\nPara iniciar o cadastro de funcionarios é necessario configurar o sistema\n");
    return;
    }

  FILE *config;
  config = fopen ("configuracoes.txt", "r");
  int maxFunc;
  fscanf (config,"%i",&maxFunc);
  fclose(config);

  ficha cadastro[maxFunc]; 
  FILE *funcionarios;
  FILE *numFunc;
  int numF;
  int i;

  if (fopen("funcionarios.txt", "r") == NULL) {numF = 0;}
  else {
    numFunc = fopen ("numFunc.txt", "r");
    fscanf (numFunc,"%i",&numF);
    fclose(numFunc);

    funcionarios = fopen("funcionarios.txt", "r");   
    for (i = 0; i < numF; ++i) {
     fscanf (funcionarios,"%i %s %i %f",&cadastro[i].matricula,cadastro[i].nome,&cadastro[i].idade,&cadastro[i].horas);
    }
    fclose(funcionarios);
  }

  if(numF >= maxFunc) {printf ("\nO número máximo de funcionarios foi atingido\n"); return;}
  

  int cont = 0;

  while (1) {
    printf ("\nDigite a matrícula do funcionario: ");                       
    scanf ("%i",&cadastro[numF].matricula);
    if (cadastro[numF].matricula <= 0) {printf ("\nPor gentileza, insira uma matrícula positiva\n");}
    else { 
      for (i = 0; i < numF; ++i) {
        if (cadastro[numF].matricula == cadastro[i].matricula) { ++cont;} 
      }
      if (cont > 0) {
        printf ("\nEssa matrícula já está cadastrada. Tente novamente\n"); 
        cont =0;
      }
      else {break;}
    }
  }

    printf ("\nDigite o nome do funcionario: ");
    scanf (" %s",cadastro[numF].nome);

    while (1) {
      printf ("\nDigite a idade do funcionario: ");                       
      scanf ("%i",&cadastro[numF].idade);
      if (cadastro[numF].idade >= 14 && cadastro[numF].idade <= 65) {break;}
      else {printf ("\nPor gentileza, insira uma idade dentro das normas da empresa\n");}
    }

    cadastro[numF].horas = 0;

    printf ("\nCadastro concluido com sucesso\n");

    funcionarios = fopen("funcionarios.txt", "w");
    for (i = 0; i <= numF; ++i) {
      fprintf (funcionarios,"%i %s %i %f\n", cadastro[i].matricula, cadastro[i].nome, cadastro[i].idade, cadastro[i].horas);
    }
    fclose(funcionarios);

    ++numF;

    numFunc = fopen ("numFunc.txt", "w");
    fprintf (numFunc,"%i",numF);
    fclose(numFunc); 
  }

// modolo de alteracao de informacoes de funcionario
  
void alterar() {
  
  if (fopen("funcionarios.txt", "r") == NULL) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  FILE *funcionarios;
  FILE *numFunc;
  int numF;
  int i;

  numFunc = fopen ("numFunc.txt", "r");
  fscanf (numFunc,"%i",&numF);
  fclose(numFunc);

  if (numF == 0) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  ficha cadastro[numF];

  funcionarios = fopen("funcionarios.txt", "r");   
  for (i = 0; i < numF; ++i) {
    fscanf (funcionarios,"%i %s %i %f",&cadastro[i].matricula,cadastro[i].nome,&cadastro[i].idade,&cadastro[i].horas);
  }
  fclose(funcionarios);

  int matriDesejada;

  while (1) {
    printf ("\nInforme a matricula do funcionario para alterar suas informacoes: ");
    scanf ("%i",&matriDesejada);

    for (i = 0; i < numF; ++i) {
        if (matriDesejada == cadastro[i].matricula) {
          int opcao;
          while (1) {
            printf ("\nDigite 1 para: Alterar nome do funcionario\nDigite 2 para: Alterar idade do funcionario\nDigite 0 para: Retornar ao MENU\n\nOpcao: ");
            scanf ("%i",&opcao);

            switch (opcao) {
              case 1:
                 printf ("\nInsira o novo nome: ");
                 scanf (" %s",cadastro[i].nome);
                 printf ("\nNome atualizado com sucesso\n");
              break;

              case 2:
                 while (1) {
                    printf ("\nDigite a nova idade do funcionário: ");                       
                    scanf ("%i",&cadastro[i].idade);
                    if (cadastro[i].idade >= 14 && cadastro[i].idade <= 65) {
                      printf ("\nIdade atualizada com sucesso\n"); 
                      break;
                    }
                    else {printf ("\nPor gentileza, insira uma idade dentro das normas da empresa\n");}
                 }                 
              break;

              case 0:
                 funcionarios = fopen("funcionarios.txt", "w");
                 for (i = 0; i < numF; ++i) {
                   fprintf (funcionarios,"%i %s %i %f\n", cadastro[i].matricula, cadastro[i].nome, cadastro[i].idade, cadastro[i].horas);
                 }
                 fclose(funcionarios);
                 return;

              default: printf ("\nOpcao invalida. Tente novamente\n");
              break;
            }
          }

        } 
    }

    printf ("\nMatricula nao encontrada. Por gentileza, insira uma matricula valida\n");
  }
}

// modolo de remocao de funcionario 

void remover() {

  if (fopen("funcionarios.txt", "r") == NULL) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  FILE *numFunc;
  int numF;
 
  numFunc = fopen ("numFunc.txt", "r");
  fscanf (numFunc,"%i",&numF);
  fclose(numFunc);

  if (numF == 0) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  ficha cadastro[numF];
  FILE *funcionarios;
  int i;

  funcionarios = fopen("funcionarios.txt", "r");   
  for (i = 0; i < numF; ++i) {
    fscanf (funcionarios,"%i %s %i %f",&cadastro[i].matricula,cadastro[i].nome,&cadastro[i].idade,&cadastro[i].horas);
  }
  fclose(funcionarios);
  
  int matriDesejada, cont = 0;

  while (1) {
    printf ("\nInforme a matricula do funcionario que deseja demitir: ");
    scanf ("%i",&matriDesejada);

    for (i = 0; i < numF; ++i) {
      if (matriDesejada == cadastro[i].matricula) {
        while (i < numF) {
          if (i == (numF - 1)) {
            ++cont;
            break;
          }
          cadastro[i] = cadastro[i + 1];
          ++i;
        }
        break;
      }
    }

    if (cont == 1) {break;}

    printf ("\nMatricula nao encontrada. Por gentileza, insira uma matricula valida\n");
  }

  printf ("\nFuncionário demitido com sucesso\n");

  numF = numF - 1;

  funcionarios = fopen("funcionarios.txt", "w");
  for (i = 0; i < numF; ++i) {
    fprintf (funcionarios,"%i %s %i %f\n", cadastro[i].matricula, cadastro[i].nome, cadastro[i].idade, cadastro[i].horas);
  }
  fclose(funcionarios);

  numFunc = fopen ("numFunc.txt", "w");
  fprintf (numFunc,"%i",numF);
  fclose(numFunc); 
}

// modolo de relatorios de funcionarios

void imprimir() {

  if (fopen("funcionarios.txt", "r") == NULL) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  FILE *config;
  config = fopen ("configuracoes.txt", "r");
  int maxFunc, maxDias, numHoras, maxHoras;
  fscanf (config,"%i %i %i %i",&maxFunc, &maxDias, &numHoras, &maxHoras);
  fclose(config);

  FILE *numFunc;
  int numF;
 
  numFunc = fopen ("numFunc.txt", "r");
  fscanf (numFunc,"%i",&numF);
  fclose(numFunc);

  ficha cadastro[numF], guardaCad;
  FILE *funcionarios;
  int i;

  funcionarios = fopen("funcionarios.txt", "r");   
  for (i = 0; i < numF; ++i) {
    fscanf (funcionarios,"%i %s %i %f",&cadastro[i].matricula,cadastro[i].nome,&cadastro[i].idade,&cadastro[i].horas);
  }
  fclose(funcionarios);

  int opcao, x, k, w, guardaDem[numF], matriDesejada;

  while (1) {
    if (numF == 0) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
    }

    printf ("\nRELATÓRIOS\n\nDigite 1 para: Lista de funcionários\nDigite 2 para: Lista de funcionários adimplentes\nDigite 3 para: Lista de funcionarios inadimplentes\nDigite 4 para: Lista e remoção de funcionários demitidos\nDigite 0 para: Retornar para o MENU\n\nOpcao: ");
    scanf ("%i",&opcao);

    switch(opcao) {
      case 1:
         for (x = 0; x < numF; ++x) {
           for (k = x; k < numF; ++k) {
             if (cadastro[x].matricula > cadastro[k].matricula){
               guardaCad = cadastro[x];
               cadastro[x] = cadastro[k];
               cadastro[k] = guardaCad;
             }
           }
         }
         for (i = 0; i < numF; ++i) {

           if (cadastro[i].horas >= numHoras) {
             printf ("\nMatricula: %i\nNome: %s\nIdade: %i\nMedia de horas trabalhadas %f\nSituacao: Adimplente\n",cadastro[i].matricula,cadastro[i].nome,cadastro[i].idade,cadastro[i].horas);
           }

           if (cadastro[i].horas < numHoras && ((float)((cadastro[i].horas * 100)) / (float)(numHoras)) >= 70) {
             printf ("\nMatricula: %i\nNome: %s\nIdade: %i\nMedia de horas trabalhadas %f\nSituacao: Inadimplente\n",cadastro[i].matricula,cadastro[i].nome,cadastro[i].idade,cadastro[i].horas);
           }

           if ( ((float)((cadastro[i].horas * 100)) / (float)(numHoras)) < 70) {
             printf ("\nMatricula: %i\nNome: %s\nIdade: %i\nMedia de horas trabalhadas %f\nSituacao: Demitido\n",cadastro[i].matricula,cadastro[i].nome,cadastro[i].idade,cadastro[i].horas);
           }
         }
      break;
      case 2:
         for (x = 0; x < numF; ++x) {
           for (k = x; k < numF; ++k) {
             if (cadastro[x].horas < cadastro[k].horas){
               guardaCad = cadastro[x];
               cadastro[x] = cadastro[k];
               cadastro[k] = guardaCad;
             }
           }
         }
         for (i = 0; i < numF; ++i) {
           if (cadastro[i].horas >= numHoras) {
             printf ("\nMatricula: %i\nNome: %s\nIdade: %i\nMedia de horas trabalhadas %f\nSituacao: Adimplente\n",cadastro[i].matricula,cadastro[i].nome,cadastro[i].idade,cadastro[i].horas);
           }
         }
      break;
      case 3:
         for (x = 0; x < numF; ++x) {
           for (k = x; k < numF; ++k) {
             if (cadastro[x].horas < cadastro[k].horas){
               guardaCad = cadastro[x];
               cadastro[x] = cadastro[k];
               cadastro[k] = guardaCad;
             }
           }
         }
         for (i = 0; i < numF; ++i) {
           if (cadastro[i].horas < numHoras && ((float)((cadastro[i].horas * 100)) / (float)(numHoras)) >= 70) {
             printf ("\nMatricula: %i\nNome: %s\nIdade: %i\nMedia de horas trabalhadas %f\nSituacao: Inadimplente\n",cadastro[i].matricula,cadastro[i].nome,cadastro[i].idade,cadastro[i].horas);
           }
         }
      break;
      case 4:
         for (x = 0; x < numF; ++x) {
           for (k = x; k < numF; ++k) {
             if (cadastro[x].horas < cadastro[k].horas){
               guardaCad = cadastro[x];
               cadastro[x] = cadastro[k];
               cadastro[k] = guardaCad;
             }
           }
         }
         for (i = 0; i < numF; ++i) {
           if ( ((float)((cadastro[i].horas * 100)) / (float)(numHoras)) < 70) {
             printf ("\nMatricula: %i\nNome: %s\nIdade: %i\nMedia de horas trabalhadas %f\nSituacao: Demitido\n",cadastro[i].matricula,cadastro[i].nome,cadastro[i].idade,cadastro[i].horas);

             guardaDem[w] = cadastro[i].matricula;
             ++w;
           }
         }

         for (x = 0; x < w; ++x) {
           matriDesejada = guardaDem[x];

           for (i = 0; i < numF; ++i) {
             if (matriDesejada == cadastro[i].matricula) {
               while (i < numF) {
                 if (i == (numF - 1)) {
                 break;
                 }
                 cadastro[i] = cadastro[i + 1];
                 ++i;
               }
             break;
             }
           }
         }

         numF = numF - w;

         funcionarios = fopen("funcionarios.txt", "w");
         for (i = 0; i < numF; ++i) {
           fprintf (funcionarios,"%i %s %i %f\n", cadastro[i].matricula, cadastro[i].nome, cadastro[i].idade, cadastro[i].horas);
         }       
         fclose(funcionarios);

         numFunc = fopen ("numFunc.txt", "w");
         fprintf (numFunc,"%i",numF);
         fclose(numFunc);          
      break;
      case 0: return;
      break;
      default: printf ("\nOpcao invalida. Tente novamente\n");
      break;
    }
  }
}

// modolo de menu do funcionario

int menuFuncionario(){
  int chaveFuncionario;

  while (1) {

    printf ("\nMENU FUNCIONARIO\n\nDigite 1 para: Cadastro de horas\nDigite 2 para: Verificacao de situcao\nDigite 0 para: Encerrar sessão\n\nOpcao: ");
  
    scanf ("%i",&chaveFuncionario);

    if (chaveFuncionario == 1 || chaveFuncionario == 2 || chaveFuncionario == 0) {
      return chaveFuncionario;
    }
    else {printf ("\nOpcao invalida. Tente novamente\n");}
  }
}

// modolo de cadastro de horas

void cadastraHora() {
  if (fopen("funcionarios.txt", "r") == NULL) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  FILE *config;
  config = fopen ("configuracoes.txt", "r");
  int maxFunc, maxDias, numHoras, maxHoras;
  fscanf (config,"%i %i %i %i",&maxFunc, &maxDias, &numHoras, &maxHoras);
  fclose(config);

  FILE *numFunc;
  int numF;
 
  numFunc = fopen ("numFunc.txt", "r");
  fscanf (numFunc,"%i",&numF);
  fclose(numFunc);

  if (numF == 0) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  ficha cadastro[numF];
  FILE *funcionarios;
  int i;

  funcionarios = fopen("funcionarios.txt", "r");   
  for (i = 0; i < numF; ++i) {
    fscanf (funcionarios,"%i %s %i %f",&cadastro[i].matricula,cadastro[i].nome,&cadastro[i].idade,&cadastro[i].horas);
  }
  fclose(funcionarios);

  int matriDesejada, k, contaHora, horasTrabalhadas = 0, diasTrabalhados = 0;

  while (1) {
    printf ("\nInforme sua matricula para cadastrar suas horas de trabalho: ");
    scanf ("%i",&matriDesejada);

    for (i = 0; i < numF; ++i) {
      if (matriDesejada == cadastro[i].matricula) {
        printf ("\nOla %s\n",cadastro[i].nome);
        for (k = 0; k < maxDias; ++k) {                    
          while (1) {
            printf ("\nDigite as horas trabalhadas do dia %i\nQuantidade de horas: ",(k+1));
            scanf ("%i",&contaHora);
            if (contaHora <= maxHoras && contaHora >= 0) {break;}
            else {printf ("\nQuantidade de horas invalida. Por gentileza, insira uma quantidade dentro das normas da empresa\n");}
          }
          horasTrabalhadas = horasTrabalhadas + contaHora;
        } 
        cadastro[i].horas = (float)(horasTrabalhadas) / (float)(maxDias);

        funcionarios = fopen("funcionarios.txt", "w");
        for (i = 0; i < numF; ++i) {
          fprintf (funcionarios,"%i %s %i %f\n", cadastro[i].matricula, cadastro[i].nome, cadastro[i].idade, cadastro[i].horas);
        }       
        fclose(funcionarios);

        printf ("\nHoras cadastradas com sucesso\n");
        return;
      }
    }
    printf ("\nMatricula nao encontrada. Por gentileza, insira uma matricula valida\n");
  }

}

// modolo de verificacao de situacao de funcionario

void verificar() {
  if (fopen("funcionarios.txt", "r") == NULL) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  FILE *config;
  config = fopen ("configuracoes.txt", "r");
  int maxFunc, maxDias, numHoras, maxHoras;
  fscanf (config,"%i %i %i %i",&maxFunc, &maxDias, &numHoras, &maxHoras);
  fclose(config);

  FILE *numFunc;
  int numF;
 
  numFunc = fopen ("numFunc.txt", "r");
  fscanf (numFunc,"%i",&numF);
  fclose(numFunc);

  if (numF == 0) {
    printf ("\nNão há funcionarios cadastrados\n"); 
    return;
  }

  ficha cadastro[numF];
  FILE *funcionarios;
  int i;

  funcionarios = fopen("funcionarios.txt", "r");   
  for (i = 0; i < numF; ++i) {
    fscanf (funcionarios,"%i %s %i %f",&cadastro[i].matricula,cadastro[i].nome,&cadastro[i].idade,&cadastro[i].horas);
  }
  fclose(funcionarios);

  int matriDesejada;

  while (1) {
    printf ("\nInforme sua matricula para verificar sua situacao: ");
    scanf ("%i",&matriDesejada);

    for (i = 0; i < numF; ++i) {
      if (matriDesejada == cadastro[i].matricula) {
        printf ("\nOla %s\n",cadastro[i].nome);

        if (cadastro[i].horas >= numHoras) {
          printf ("\nParabens. Voce e um funcionario exemplar\nSituacao: Adimplente\n");
        }

        if (cadastro[i].horas < numHoras && ((float)((cadastro[i].horas * 100)) / (float)(numHoras)) >= 70) {
          printf ("\nVoce pode se esforcar mais\nSituacao: Inadimplente\n");
        }

        if ( ((float)((cadastro[i].horas * 100)) / (float)(numHoras)) < 70) {
          printf ("\nA casa caiu, melhor procurar outro emprego\nSituacao: Demitido\n");
        } 
        return;
      }
    }
    printf ("\nMatricula nao encontrada. Por gentileza, insira uma matricula valida\n");
  }
}
