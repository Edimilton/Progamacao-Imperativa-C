#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUM_FUNC 5
#define NUM_DIAS 5
#define QTD_HORAS 6
#define NUM_FUNC_MAT_UNICA 3


int main() {
  
 int chaveMenu, x, k, w = 0; 
 int matricula[NUM_FUNC] = {0}, numF = 0, cont1 = 0;
 int demitidos[NUM_FUNC_MAT_UNICA] = {0}, numD = 0, cont2 = 0;
 int diasTrabalhados[NUM_FUNC] = {0}, matriHoras, cont3 = 0, contaHora = 0;
 float horasTrabalhadas[NUM_FUNC] = {0};
 int chaveRelatorio, retornaMenu = 0, guardaMatri, guardaHora, guardaDia, guardaDemitidos[NUM_FUNC] = {0};

 char saida1, saida2, saida3;
  
 while (1) {


  printf ("\nMENU\n\nDigite 1 para: Cadastro de funcionário\nDigite 2 para: Remoção de funcionário\nDigite 3 para: Cadastro de horas diárias\nDigite 4 para: Relatórios\nDigite 0 para: Encerrar sessão\n\n");

  scanf("%i",&chaveMenu);

  switch (chaveMenu) {
    case 1:
        do 
        { if (numF < NUM_FUNC) {            
            
           while (1) {
             while (1) {
               printf ("\nDigite a matrícula do funcionário\n");                       
               scanf ("%i",&matricula[numF]);
               if (matricula[numF]>0) {break;}
               else { printf ("\nPor gentileza, insira uma matrícula positiva\n");}
             }
             for (x = 0; x < NUM_FUNC; ++x) {
               if (matricula[numF] == matricula[x]) { ++cont1; }
             }
             for (x = 0; x < NUM_FUNC_MAT_UNICA; ++x) {
               if (matricula[numF] == demitidos[x]) {
                 ++cont1;
               }
             }

             if (cont1 > 1) {
               printf ("\nEssa matrícula já está cadastrada. Tente novamente\n");
               cont1 = 0;  
             }
             else {break;}
           }
           cont1 = 0;
           ++numF;           
           
          }
          else {
            printf ("\nO número máximo de funcionários foi atingido\n");
            break;
          }

          printf ("\nFuncionário cadastrado com sucesso\n");

          while (1) {
            printf ("\nDeseja cadastrar mais um funcionário?\nDigite S para Sim\nDigite N para Não\n\n");
            scanf (" %c",&saida1);
            if (saida1 != 'S' && saida1 != 'N') {
              printf ("\nComando desconhecido. Tente novamente\n");            
            }
            else {break;}
          }
          
        } while (saida1 == 'S');
        break;

    case 2:
        do
        { if (numF == 0) {
            printf ("\nNão há funcionários cadastrados\n");
            break;
          }          
          while (1) {
            printf ("\nMatrículas em uso:\n");
            for (x = 0; x < numF; ++x) {
              printf ("%i\n",matricula[x]);
            }
            printf ("\nDigite uma matrícula para remover um funcionário\n");

            scanf ("%i",&demitidos[numD]);

            for (x = 0; x < numF; ++x) {

              if (demitidos[numD] == matricula[x]) {
                while (x < numF) {
                  if (x == (numF - 1)) {
                    matricula[x] = 0;
                  }
                  matricula[x] = matricula[x + 1];
                  horasTrabalhadas[x] = horasTrabalhadas[x + 1];
                  diasTrabalhados[x] = diasTrabalhados[x + 1];
                  ++x;
                }
                numF = numF - 1;
                ++cont2;
              }
            }
            if (cont2 > 0) {              
              cont2 = 0;
              ++numD;
              if (numD == NUM_FUNC_MAT_UNICA) {
                numD = 0;
              }
              break;
            }

            printf ("\nMatrícula não encontrada. Por gentileza, insira uma matrícula válida\n");
            
          }

          printf ("\nFuncionário demitido com sucesso\n");

          while (1) {
            printf ("\nDeseja demitir mais um funcionário?\nDigite S para Sim\nDigite N para Não\n\n");
            scanf (" %c",&saida2);
            if (saida2 != 'S' && saida2 != 'N') {
              printf ("\nComando desconhecido\n");            
            }
            else {break;}
          }
             
        } while (saida2 == 'S');
        break;

    case 3:
        if (numF == 0) {
            printf ("\nNão há funcionários cadastrados\n");
            break;
          }
        do 
        { while (1) {
           printf ("\nMatrículas em uso:\n");
           for (x = 0; x < numF; ++x) {
              printf ("%i\n",matricula[x]);
           }
           printf ("\nDigite uma matrícula para cadastrar horas de trabalhado\n");

           scanf ("%i",&matriHoras);

           for (x = 0; x < numF; ++x) {
               if (matriHoras == matricula[x]) {                
                 for (k = 0; k < NUM_DIAS; ++k) {                    
                    while (1) {
                    printf ("\nDigite as horas trabalhadas do dia %i\n",(k+1));
                    scanf ("%i",&contaHora);
                    if (contaHora <= 24 && contaHora >= 0) {break;}
                    else {printf ("\nQuantidade de horas inválida. Por gentileza, insira um valor válido\n");}
                    }
                    horasTrabalhadas[x] = horasTrabalhadas[x] + contaHora;
                    if (contaHora > 0) {++diasTrabalhados[x];}
                 }
                 ++cont3;
                 horasTrabalhadas[x] = (float)(horasTrabalhadas[x]) / (float)(NUM_DIAS);
                 break;
               }
           }
           if (cont3 > 0) {
             cont3 = 0;
             break;
             }

           printf ("\nMatrícula não encontrada. Por gentileza, insira uma matrícula válida\n");
          }

          printf ("\nHoras cadastradas com sucesso\n");

          while (1) {
            printf ("\nDeseja cadastrar horas de mais algum funcionário?\nDigite S para Sim\nDigite N para Não\n\n");
            scanf (" %c",&saida3);
            if (saida3 != 'S' && saida3 != 'N') {
              printf ("\nComando desconhecido\n");            
            }
            else {break;} 
          }
          
        } while (saida3 == 'S');  
        break;

    case 4:
        while (1) {

          if (numF == 0) {
            printf ("\nNão há funcionários cadastrados\n");
            break;
          }
          printf ("\nRELATÓRIOS\n\nDigite 1 para: Lista de funcionários\nDigite 2 para: Lista de funcionários adimplentes\nDigite 3 para: Lista de funcionarios inadimplentes\nDigite 4 para: Lista e remoção de funcionários demitidos\nDigite 0 para: Retornar para o MENU\n\n");

          scanf ("%i",&chaveRelatorio);

          switch (chaveRelatorio) {
            case 1:
                for (x = 0; x < numF; ++x) {
                  for (k = x; k < numF; ++k) {
                    if (matricula[x] > matricula[k]){
                      guardaMatri = matricula[x];
                      matricula[x] = matricula[k];
                      matricula[k] = guardaMatri;
                      guardaHora = horasTrabalhadas[x];
                      horasTrabalhadas[x] = horasTrabalhadas[k];
                      horasTrabalhadas[k] = guardaHora;
                      guardaDia = diasTrabalhados[x];
                      diasTrabalhados[x] = diasTrabalhados [k];
                      diasTrabalhados[k] = guardaDia;
                    }
                  }
                }
                printf ("\nFuncionários ativos:\n\n");
                for (x = 0; x < numF; ++x) {
                  printf ("Matrícula %i\n", matricula[x]);
                }
                break;

            case 2:
                for (x = 0; x < numF; ++x) {
                  for (k = x; k < numF; ++k) {
                    if (horasTrabalhadas[x] > horasTrabalhadas[k]){
                      guardaMatri = matricula[x];
                      matricula[x] = matricula[k];
                      matricula[k] = guardaMatri;
                      guardaHora = horasTrabalhadas[x];
                      horasTrabalhadas[x] = horasTrabalhadas[k];
                      horasTrabalhadas[k] = guardaHora;
                      guardaDia = diasTrabalhados[x];
                      diasTrabalhados[x] = diasTrabalhados [k];
                      diasTrabalhados[k] = guardaDia;
                    }
                  }
                }
                printf ("\nFuncionários adimplentes:\n");
                for (x = 0; x < numF; ++x) {
                  if (horasTrabalhadas[x] >= QTD_HORAS) {
                    printf ("\nMatrícula: %i\nMédia de horas de trabalhado: %.2f\nFrequência: %i de %i dias\n", matricula[x], horasTrabalhadas[x], diasTrabalhados[x], NUM_DIAS);
                  }
                }
                break;

            case 3:
                for (x = 0; x < numF; ++x) {
                  for (k = x; k < numF; ++k) {
                    if (horasTrabalhadas[x] > horasTrabalhadas[k]){
                      guardaMatri = matricula[x];
                      matricula[x] = matricula[k];
                      matricula[k] = guardaMatri;
                      guardaHora = horasTrabalhadas[x];
                      horasTrabalhadas[x] = horasTrabalhadas[k];
                      horasTrabalhadas[k] = guardaHora;
                      guardaDia = diasTrabalhados[x];
                      diasTrabalhados[x] = diasTrabalhados [k];
                      diasTrabalhados[k] = guardaDia;
                    }
                  }
                }
                printf ("\nFuncionários inadimplentes:\n");
                for (x = 0; x < numF; ++x) {
                  if (horasTrabalhadas[x] < QTD_HORAS && ((float)((horasTrabalhadas[x] * 100)) / (float)(QTD_HORAS)) >= 70) {
                    printf ("\nMatrícula: %i\nMédia de horas de trabalhado: %.2f\nFrequência: %i de %i dias\n", matricula[x], horasTrabalhadas[x], diasTrabalhados[x], NUM_DIAS);
                  }
                }
                break;

            case 4:
                for (x = 0; x < numF; ++x) {
                  for (k = x; k < numF; ++k) {
                    if (horasTrabalhadas[x] > horasTrabalhadas[k]){
                      guardaMatri = matricula[x];
                      matricula[x] = matricula[k];
                      matricula[k] = guardaMatri;
                      guardaHora = horasTrabalhadas[x];
                      horasTrabalhadas[x] = horasTrabalhadas[k];
                      horasTrabalhadas[k] = guardaHora;
                      guardaDia = diasTrabalhados[x];
                      diasTrabalhados[x] = diasTrabalhados [k];
                      diasTrabalhados[k] = guardaDia;
                    }
                  }
                }
                printf ("\nFuncionários demitidos:\n");
                for (x = 0; x < numF; ++x) {
                  if ( ((float)((horasTrabalhadas[x] * 100)) / (float)(QTD_HORAS)) < 70) {
                    guardaDemitidos[w] = matricula[x];
                    ++w;
                    printf ("\nMatrícula: %i\nMédia de horas de trabalhado: %.2f\nFrequência: %i de %i dias\n", matricula[x], horasTrabalhadas[x], diasTrabalhados[x], NUM_DIAS);
                  }
                }
                for (k = 0; k < w; ++k) {
                 demitidos[numD] = guardaDemitidos[k]; 
                 for (x = 0; x < numF; ++x) {
                  if (demitidos[numD] == matricula[x]) {
                   while (x < numF) {
                     if (x == (numF - 1)) {
                       matricula[x] = 0;
                     }
                     matricula[x] = matricula[x + 1];
                     horasTrabalhadas[x] = horasTrabalhadas[x + 1];
                     diasTrabalhados[x] = diasTrabalhados[x + 1];
                     ++x;
                   }
                   numF = numF - 1;
                   ++numD;
                   if (numD == NUM_FUNC_MAT_UNICA) {
                    numD = 0;
                   }
                  }
                 }
                }
                w = 0;
                break;

            case 0: 
                ++retornaMenu;
                break;

            default:
                printf ("\nDígito inválido. Por gentileza, insira um dígito válido\n"); 
                break;            
          }

          if (retornaMenu > 0) {
            retornaMenu = 0;
            break;
          }
        }
        break;

    case 0:
        printf ("\nSessão encerrada\n");
        return 0;   
    default:
        printf ("\nDígito inválido. Por gentileza, insira um dígito válido\n"); 
        break;
  }
 }
}
