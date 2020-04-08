#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>

#define R 2
#define V 1
#define C 0

#define ELSE 0
#define THEN 1


#define PADRAO "\033[0m"
#define VERMELHO "\033[0;31m"
#define VERDE "\033[0;32m"
#define AMARELO "\033[0;33m"
#define AZUL "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CIANO "\033[0;36m"
#define COR(CODIGO) SAI(CODIGO)

#define ABRE do{
#define FECHA }while(0)
#define FOR(NOME,LIM) for(char NOME = 0; NOME < LIM; NOME++)
#define LADOS for(int k=0; k<2; k++)

#define STDOUT stdout
#define SAI(ARGS...) fprintf(STDOUT,ARGS)
#define SAI_DEF(PONTEIRO,ARGS...) fSAI(SAIDA,ARGS)
#define SAI_COR(CODIGO,ARGS...) ABRE COR(CODIGO);SAI(ARGS);COR(PADRAO); FECHA
#define PULA SAI("\n")

void exit_program(char *s)
{
    PULA;PULA;PULA;PULA;PULA;PULA;
    SAI("\nERRO");
    if(s != NULL)
        SAI("\t%s",s);
    exit(EXIT_FAILURE);
}

FILE* abre(char *file, char *mode)
{
    FILE *fp;
    fp = fopen(file,mode);
    if(fp == NULL)
        exit_program("NAO CONSEGIU ABRIR ARQUIVO");

    setbuf(fp,NULL);
    return fp;
}

void abre_saidas()
{
    setbuf(stdout,NULL);
}

#define DEBUGANDO 0
#define SEGURANDO 0

#define DEBUG_CONSISTENCIA      1
#define DEBUG_CONECTA           0
#define DEBUG_DESCONECTA        0
#define DEBUG_TRANSFERE         0
#define DEBUG_LIBERA_ARVORE     0
#define DEBUG_ENLISTA_ARVORE    0
#define DEBUG_BUSCA_AMPLITUDE   0
#define DEBUG_BUSCA_ESTRUTURA   1
#define DEBUG_REDUZ_LISTA       0
#define DEBUG_REDUZ_QDD         1
#define DEBUG_PRODUTO_TENSORIAL 0

#define COND_DEBUG(CODIGO) if(DEBUGANDO == 2 || ((DEBUGANDO == 1) && (CODIGO)))
#define DEBUG(CODIGO,ARGS...) COND_DEBUG(CODIGO)SAI(ARGS)
#define SEGURA if(SEGURANDO)getchar()

typedef double numero;

struct lista_body
{
    struct no *n;
    struct lista_body *lb;
};

struct lista_head
{
    struct lista_body  lb;
    struct lista_head *lh;
};

struct label
{
    int cl, ni;
};

struct estrutura
{
    struct no *el, *th;
};

struct amplitude
{
    numero re, im;
};

struct no
{
    struct lista_head lh;
    struct label lab;
};

struct no_estrutura
{
    struct no n;
    struct estrutura e;
};

struct no_amplitude
{
    struct no n;
    struct amplitude a;
};

struct QDD
{
    struct no *n;
    struct lista_body *lb;
    char   N;
};

struct apply
{
    struct apply *a1, *a2, *a;
    struct no    *n1, *n2, *n;
};



typedef struct label label;
typedef struct estrutura estrutura;
typedef struct amplitude amplitude;
typedef struct no no;
typedef struct no_estrutura no_estrutura;
typedef struct no_amplitude no_amplitude;
typedef struct lista_body lista_body;
typedef struct lista_head lista_head;
typedef struct QDD QDD;
typedef struct apply apply;

typedef unsigned long long Long;

#define BODY(PONTEIRO)      ((lista_body*)(PONTEIRO))
#define HEAD(PONTEIRO)      ((lista_head*)(PONTEIRO))
#define NO(PONTEIRO)        ((no*)(PONTEIRO))
#define LABEL(PONTEIRO)     ((label*)(HEAD(PONTEIRO)+1))
#define NLABEL(PONTEIRO)    (LABEL(BODY(PONTEIRO)->n))
#define NEST(PONTEIRO)      ((no_estrutura*)(PONTEIRO))
#define NAMP(PONTEIRO)      ((no_amplitude*)(PONTEIRO))
#define EST(PONTEIRO)       ((estrutura*)(NO(PONTEIRO)+1))
#define AMP(PONTEIRO)       ((amplitude*)(NO(PONTEIRO)+1))
#define VEST(PONTEIRO)      ((no**)EST(PONTEIRO))
#define VAPPLY(PONTEIRO)    ((apply**)(PONTEIRO))

#define LADO(NO,NO1)               (VEST(NO)[0] != NO1)
#define ACCESS(PONTEIRO)    LABEL(PONTEIRO)->ni][LABEL(PONTEIRO)->cl

#define COMPARE_LABEL(LABEL_1, OPERANDO, LABEL_2)       (*((long*)LABEL_1) OPERANDO *((long*)LABEL_2))
#define SUBTRACT_POINTER(POINTER_1, POINTER_2)          (((void*)POINTER_1) - ((void*)POINTER_2))
#define COPY_STRUCT(PONTEIRO_1, PONTEIRO_2, ESTRUTURA)  memcpy(PONTEIRO_1,PONTEIRO_2,sizeof(ESTRUTURA))
#define ZERA(PONTEIRO, SIZE) memset(PONTEIRO,0,SIZE*sizeof(PONTEIRO))



numero eps;

struct quantidades
{
    int NE, NA, LB, LH, A;
};

typedef struct quantidades quantidades;

quantidades I, I0;

lista_body *lb_zero, *LB[2][2];

int memoria_zerada()
{
    if(I.NE) return 0;
    if(I.NA) return 0;
    if(I.LB) return 0;
    if(I.LH) return 0;
    if(I.A ) return 0;
    return 1;
}

void set_Qbit(int N)
{
    eps = pow(2,-0.5*N)/300;
}

#define MEMORY_REPORT 1
#define LIBERA(FUNCTION, PONTEIRO) ABRE if(!MEMORY_REPORT) free(PONTEIRO); else FUNCTION(PONTEIRO); FECHA



no_estrutura* cria_no_estrutra(int classe, int nivel)
{
    no_estrutura *ne;
    ne = malloc(sizeof(no_estrutura));
    if(ne == NULL)
        exit_program("CRIA NO ESTRUTURA");

    if(MEMORY_REPORT)
    I.NE++;

    BODY(ne)->n   = NULL;
    BODY(ne)->lb  = NULL;
    HEAD(ne)->lh  = NULL;
    LABEL(ne)->ni = nivel;
    LABEL(ne)->cl = classe;
    EST(ne)->el   = NULL;
    EST(ne)->th   = NULL;

    return ne;
}

no_amplitude* cria_no_amplitude(numero re, numero im)
{
    no_amplitude *na;
    na = malloc(sizeof(no_amplitude));
    if(na == NULL)
        exit_program("CRIA NO AMPLITUDE");

    if(MEMORY_REPORT)
    I.NA++;

    BODY(na)->n  = NULL;
    BODY(na)->lb = NULL;
    HEAD(na)->lh = NULL;
    LABEL(na)->ni  = 0;
    LABEL(na)->cl = 0;
    AMP(na)->re = re;
    AMP(na)->im = im;

    return na;
}

no_estrutura* copia_no_estrutura(no_estrutura *ne_0)
{
    no_estrutura *ne_1;
    ne_1 = malloc(sizeof(no_amplitude));
    if(ne_1 == NULL)
        exit_program("COPIA NO ESTRUTURA");

    if(MEMORY_REPORT)
    I.NE++;

    BODY(ne_1)->n  = NULL;
    BODY(ne_1)->lb = NULL;
    HEAD(ne_1)->lh = NULL;
    COMPARE_LABEL(LABEL(ne_1),=,LABEL(ne_0));
    COPY_STRUCT(EST(ne_1),EST(ne_0),estrutura);

    return ne_1;
}

no_amplitude* copia_no_amplitude(no_amplitude *na_0)
{
    no_amplitude *na_1;
    na_1 = malloc(sizeof(no_amplitude));
    if(na_1 == NULL)
        exit_program("COPIA NO AMPLITUDE");

    if(MEMORY_REPORT)
    I.NA++;

    BODY(na_1)->n  = NULL;
    BODY(na_1)->lb = NULL;
    HEAD(na_1)->lh = NULL;
    LABEL(na_1)->ni = 0;
    LABEL(na_1)->cl = 0;
    COPY_STRUCT(AMP(na_1),AMP(na_0),amplitude);

    return na_1;
}



lista_body* cria_lista_body(no *n, lista_body *lb_next)
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program("CRIA LISTA BODY");

    if(MEMORY_REPORT)
    I.LB++;

    lb->n  = n;
    lb->lb = lb_next;

    return lb;
}

lista_body* cria_lista_body_vazio()
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program("CRIA LISTA BODY VAZIO");

    if(MEMORY_REPORT)
    I.LB++;

    lb->n  = NULL;
    lb->lb = NULL;

    return lb;
}

lista_body* cria_lista_body_pendurado()
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program("CRIA LISTA BODY PENDURADO");

    if(MEMORY_REPORT)
    I.LB++;

    return lb;
}

lista_body* cria_lista_body_copia(lista_body *lb_0)
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program("CRIA LISTA BODY COPIA");

    if(MEMORY_REPORT)
    I.LB++;

    COPY_STRUCT(lb,lb_0,lista_body);

    return lb;
}



lista_head* cria_lista_head(no *n, lista_head *lh_next)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD");

    if(MEMORY_REPORT)
    I.LH++;

    BODY(lh)->n  = n;
    BODY(lh)->lb = NULL;
    HEAD(lh)->lh = lh_next;

    return lh;
}

lista_head* cria_lista_head_vazio()
{
    lista_head *lh;
    lh = calloc(sizeof(lista_head),1);
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD VAZIO");

    if(MEMORY_REPORT)
    I.LH++;

    return lh;
}

lista_head* cria_lista_head_pendurado()
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD PENDURADO");

    if(MEMORY_REPORT)
    I.LH++;

    return lh;
}

lista_head* cria_lista_head_copia(lista_head *lh_0)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD COPIA");
    COPY_STRUCT(lh,lh_0,lista_head);

    if(MEMORY_REPORT)
    I.LH++;

    return lh;
}

lista_head* cria_lista_head_body(lista_body *lb, lista_head *lh_next)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD BODY");

    if(MEMORY_REPORT)
    I.LH++;

    COPY_STRUCT(lh,lb,lista_body);
    lh->lh = lh_next;
    return lh;
}



apply* cria_apply(no *n1, no *n2)
{
    apply *a;
    a = malloc(sizeof(apply));
    if(a == NULL)
        exit_program("CRIA APPLY");

    if(MEMORY_REPORT)
    I.A++;

    a->n  = NULL;
    a->a  = NULL;
    a->a1 = NULL;
    a->a2 = NULL;

    a->n1 = n1;
    a->n2 = n2;

    return a;
}

apply* cria_apply_vazio()
{
    apply *a;
    a = calloc(1,sizeof(apply));
    if(a == NULL)
        exit_program("CRIA APPLY VAZIO");

    if(MEMORY_REPORT)
    I.A++;

    return a;
}



void libera_lista_body_item(lista_body *lb)
{
    if(!MEMORY_REPORT)
        exit_program("ESSA FUNCAO NAO DEVE SER CHAMADA NESSE MODO");

    if (I.LB == 0)
        exit_program("LIBERA LISTA BODY ITEM");
    I.LB--;

    free(lb);
}

void libera_lista_head_item(lista_head *lh)
{
    if(!MEMORY_REPORT)
        exit_program("ESSA FUNCAO NAO DEVE SER CHAMADA NESSE MODO");

    I.LH--;
    free(lh);
}



void libera_lista_body_lista(lista_body *lb)
{
    lista_body *lb_aux;
    while(lb != NULL)
    {
        lb_aux = lb->lb;
        LIBERA(libera_lista_body_item,lb);
        lb = lb_aux;
    }
}

void libera_lista_head_lista(lista_head *lh)
{
    while(lh != NULL)
    {
        lista_head *lh_aux;
        lh_aux = lh;
        lh     = lh->lh;


        libera_lista_body_lista(BODY(lh_aux)->lb);
        LIBERA(libera_lista_head_item,lh_aux);
    }
}



void libera_no_estrutura(no *n)
{
    if(!MEMORY_REPORT)
        exit_program("ESSA FUNCAO NAO DEVE SER CHAMADA NESSE MODO");

    I.NE--;
    free(n);
}

void libera_no_amplitude(no *n)
{
    if(!MEMORY_REPORT)
        exit_program("ESSA FUNCAO NAO DEVE SER CHAMADA NESSE MODO");

    I.NA--;
    free(n);
}

void libera_no(no *n)
{
    if(!MEMORY_REPORT)
        exit_program("ESSA FUNCAO NAO DEVE SER CHAMADA NESSE MODO");

    if(LABEL(n)->ni == 0)
        I.NA--;
    else
        I.NE--;
    free(n);
}



void libera_apply_item(apply *a)
{
    if(!MEMORY_REPORT)
        exit_program("ESSA FUNCAO NAO DEVE SER CHAMADA NESSE MODO");

    I.A--;
    free(a);
}

void libera_apply_lista(apply *a)
{
    apply *a_aux;
    while(a != NULL)
    {
        a_aux = a->a;
        LIBERA(libera_apply_item,a);
        a = a_aux;
    }
}



void mostra_quantidades(quantidades i)
{
    SAI("\n\nQUANTIDADES");
    SAI("\nI.LB : %d",i.LB);
    SAI("\nI.LH : %d",i.LH);
    SAI("\nI.NE : %d",i.NE);
    SAI("\nI.NA : %d",i.NA);
    SAI("\nI.A  : %d",i.A);
    SAI("\n");
}

void inicia_estruturas()
{
    lb_zero = cria_lista_body_vazio();

    LB[0][0] = cria_lista_body_vazio();
    LB[0][1] = cria_lista_body_vazio();
    LB[1][0] = cria_lista_body_vazio();
    LB[1][1] = cria_lista_body_vazio();

    I.LB = 0;
}

void finaliza_estruturas()
{
    I.LB = 5;

    LIBERA(libera_lista_body_item,lb_zero);

    LIBERA(libera_lista_body_item,LB[0][0]);
    LIBERA(libera_lista_body_item,LB[0][1]);
    LIBERA(libera_lista_body_item,LB[1][0]);
    LIBERA(libera_lista_body_item,LB[1][1]);
}



void mostra_ponteiro(void *pointer)
{
    if (pointer == NULL)  SAI("NULL");
    else                  SAI("%011p", pointer);
}

int mostra_cabecalho(char *s, void *p)
{
    SAI("\nEndereco (%s): ",s);mostra_ponteiro(p);
    return p == NULL;
}

void mostra_label(label *lab, int completa)
{
    if(lab->ni == 0)
    {
        SAI("AMPLITUDE");
        return;
    }

    switch(lab->cl)
    {
        case C:
        SAI("C");
        break;

        case V:
        SAI("V");
        break;

        case R:
        SAI("R");
        break;

        default:
        SAI(" MERDA %d ",lab->cl);
    }
    SAI("%d",lab->ni);
    if(completa)
        SAI("\t\t");
}



#define FOR_CONTA for(i=0; lb != NULL; i++, lb = lb->lb)

void mostra_lista_body_item(lista_body *lb)
{
    if(mostra_cabecalho("LISTA BODY",lb))
        return;

    SAI("\nNo: ");mostra_ponteiro(lb->n);
    SAI("\nlb: ");mostra_ponteiro(lb->lb);
    SAI("\n");
}

void mostra_lista_body_ponteiros(lista_body *lb)
{
    int i;
    FOR_CONTA
    {
        SAI("\n\tLista %3d : ",i);mostra_ponteiro(lb);
    }
}

void mostra_lista_body_lista(lista_body *lb)
{
    int i;
    FOR_CONTA
    {
        SAI("\n\tNo %3d: ",i);mostra_ponteiro(lb->n);
    }
}



#define IF_ZERO(NOME) if(NOME < eps)if(NOME > -eps)

void mostra_estrutura(estrutura *est)
{
    mostra_ponteiro(est->el);SAI("\t\t");mostra_ponteiro(est->th);
}

void mostra_amplitude(amplitude *amp)
{
    if(amp == NULL)
        return;

    SAI("% .4e",amp->re);
    IF_ZERO(amp->im)
        return;
    SAI(" % .4e",amp->im);
}

void mostra_dados(no *n)
{
    if(LABEL(n)->ni == 0) mostra_amplitude(AMP(n));
    else                  mostra_estrutura(EST(n));
}


#define SIMPLES   0
#define COMPACTO  1
#define COMPLETO  2
#define EXTENDIDO 3

void mostra_no(no *n, int codigo);

Long conta_itens_lista_body(lista_body *lb)
{
    Long i;
    FOR_CONTA;
    return i;
}

void mostra_lista_body_amplitudes(lista_body *lb)
{
    int i;
    FOR_CONTA
    {
        SAI("\n\tNo %2d: ",i);
        if(lb->n == NULL)
            printf(" NULL");
        else
            mostra_amplitude(AMP(lb->n));
    }
}

void mostra_lista_body(lista_body *lb, int codigo)
{
    if(lb == NULL)
    {
        SAI("\nLista nula");
        return;
    }

    switch (codigo)
    {
        case SIMPLES:
        SAI("\nLabel: ");mostra_label(NLABEL(lb),1);SAI("\ttot: %4d",conta_itens_lista_body(lb));
        break;

        case COMPACTO:
        case COMPLETO:
        SAI("\nLABEL: ");mostra_label(NLABEL(lb),1);
        int i;
        FOR_CONTA
        {
            SAI("\n\tNo %3d: ",i);mostra_ponteiro(lb->n);
            if(codigo == COMPLETO)
            {
                SAI("\t\t\t\t");mostra_dados(lb->n);
            }
        }
        break;

        case EXTENDIDO:
        for(; lb->lb != NULL; lb = lb->lb)
        {
            mostra_no(lb->n,EXTENDIDO);
            SAI("\n------------------------------------------");
        }
        mostra_no(lb->n,EXTENDIDO);
        break;
    }
}



void mostra_lista_head_item(lista_head *lh)
{
    if(mostra_cabecalho("LISTA HEAD",lh))
        return;

    SAI("\nNo: ");mostra_ponteiro(BODY(lh)->n);
    SAI("\nlb: ");mostra_ponteiro(BODY(lh)->lb);
    SAI("\nlh: ");mostra_ponteiro(lh->lh);

}

void mostra_lista_head_lista(lista_head *lh)
{
   for(; lh != NULL; lh = lh->lh)
    {
        SAI("\n");
        mostra_lista_head_item(lh);
    }
}

void mostra_lista_head(lista_head *lh, int codigo)
{
    for(; lh->lh != NULL; lh = lh->lh)
    {
        mostra_lista_body(BODY(lh),codigo);
        SAI("\n---------------------");
        for(int i=1; i<codigo; i++) SAI("---------------------");
    }
    mostra_lista_body(BODY(lh),codigo);

    if(codigo == SIMPLES)
    {
        SAI("\nAMPLITUDES");
        mostra_lista_body_amplitudes(BODY(lh));
    }
}



void mostra_antecessores(no *n)
{
    if(BODY(n)->n == NULL)
    {
        SAI("\nSem antecessores");
    }
    else
    {
        SAI("\nAntecessores: ");
        SAI("\n---------------------");
        mostra_lista_head(HEAD(n),COMPACTO);
        SAI("\n---------------------");
    }
}

void mostra_no_estrutura(no_estrutura *ne, int codigo)
{
    if(mostra_cabecalho("NO ESTRUTURA",ne))
        return;

    if(codigo == EXTENDIDO) mostra_antecessores(ne);

    SAI("\nLabel: ");mostra_label(LABEL(ne),0);
    SAI("\nSucessores: el: ");mostra_ponteiro(EST(ne)->el);SAI("\tth: ");mostra_ponteiro(EST(ne)->th);
    SAI("\n");
}

void mostra_no_amplitude(no_amplitude *na, int codigo)
{
    if(mostra_cabecalho("NO AMPLITUDE",na))
        return;

    if(codigo == EXTENDIDO)mostra_antecessores(na);

    SAI("\nAmplitude: ");mostra_amplitude(AMP(na));
    SAI("\n");
}



void mostra_no_base(no *n)
{
    if(mostra_cabecalho("NO",n))
        return;

    SAI("\nLabel: ");mostra_label(LABEL(n),0);
}

void mostra_no(no *n, int codigo)
{
    if(LABEL(n)->ni == 0) mostra_no_amplitude(n,codigo);
    else                  mostra_no_estrutura(n,codigo);
}



lista_head* enlista_arvore(no *n)
{
    COND_DEBUG(DEBUG_ENLISTA_ARVORE)
    {
        SAI("\nEntrando enlista arvore");
        SAI("\nNo inicial");
        mostra_no(n,EXTENDIDO);
    }

    int N, i, j;
    N = 1 + LABEL(n)->ni;
    lista_head *LH[N][3];
    ZERA(LH,1);

    lista_head *lh_0;
    lh_0 = cria_lista_head(n,NULL);
    LH[ACCESS(n)] = lh_0;

    lista_head *lh, *lh_1;
    lista_body *lb, *lb_1;
    lh = lh_0;
    for(i=N-1; i> 0; i--)
    for(j=2  ; j>=0; j--)
    {
        if(LH[i][j] == NULL)
            continue;

        lh->lh = LH[i][j];
        lh     = lh->lh;

        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            no **N;
            N = VEST(lb->n);
            LADOS
            {
                n = N[k];

                COND_DEBUG(DEBUG_ENLISTA_ARVORE)
                {
                    SAI("\nTentando enlistar");
                    mostra_no(n,EXTENDIDO);
                }
                if(BODY(n)->n != lb->n)
                {
                    DEBUG(DEBUG_ENLISTA_ARVORE,"\nPulou");
                    continue;
                }

                DEBUG(DEBUG_ENLISTA_ARVORE,"\nConseguiu");

                lh_1 = LH[ACCESS(n)];
                if(lh_1 == NULL) LH[ACCESS(n)] = cria_lista_head(n,NULL);
                else             BODY(lh_1)->lb = cria_lista_body(n,BODY(lh_1)->lb);
            }
        }
    }

    lh->lh     = LH[0][0];
    lh->lh->lh = NULL;

    DEBUG(DEBUG_ENLISTA_ARVORE,"\nSaindo enlista arvore");
    return lh_0;
}

void mostra_arvore(no *n, int codigo)
{
    lista_head *lh;
    lh = enlista_arvore(n);
    mostra_lista_head(lh,codigo);
    libera_lista_head_lista(lh);
}

void mostra_QDD(QDD Q, int codigo)
{
    SAI("\nQDD");
    SAI("\nN: %d",Q.N);
    SAI("\n");
    mostra_arvore(Q.n,codigo);
    SAI("\n");
}



void mostra_apply(apply *a)
{
    if(mostra_cabecalho("APPLY",a))
        return;

    SAI("\nNos: ");
    SAI("\n\tn1: ");mostra_ponteiro(a->n1);
    SAI("\n\tn2: ");mostra_ponteiro(a->n2);
    SAI("\n\tn : ");mostra_ponteiro(a->n);
    SAI("\nApplys: ");
    SAI("\n\ta1: ");mostra_ponteiro(a->a1);
    SAI("\n\ta2: ");mostra_ponteiro(a->a2);
    SAI("\n\ta : ");mostra_ponteiro(a->a);
    SAI("\n");
}



void teste_consistencia(lista_head *lh);

void inclui_no(lista_head *lh, no *n)
{
    if(BODY(lh)->n == NULL)
    {
        BODY(lh)->n = n;
        return;
    }

    label *lab;
    lab = LABEL(n);

    if(COMPARE_LABEL(lab,==,NLABEL(lh)))
    {
        BODY(lh)->lb = cria_lista_body(n,BODY(lh)->lb);
        return;
    }

    if(COMPARE_LABEL(lab,<,NLABEL(lh)))
    {
        lista_head *lh_aux;
        lh_aux = cria_lista_head_copia(lh);

        BODY(lh)->n  = n;
        BODY(lh)->lb = NULL;
        HEAD(lh)->lh = lh_aux;
        return;
    }

    for(; lh->lh != NULL; lh = lh->lh)
        if(COMPARE_LABEL(lab, <, NLABEL(lh->lh)))
            break;

    if(COMPARE_LABEL(lab,!=,NLABEL(lh)))
    {
        lh->lh = cria_lista_head(n,lh->lh);
        return;
    }

    BODY(lh)->lb = cria_lista_body(n,BODY(lh)->lb);
}

void exclui_no(lista_head *lh, no *n, lista_body *lb_pista)
{
    COND_DEBUG(DEBUG_DESCONECTA)
    {
        SAI("\nEntrando exclui no");
        mostra_lista_head_item(lh);
        teste_consistencia(lh);
    }

    if(lb_pista == NULL)
    {
        DEBUG(DEBUG_DESCONECTA,"\nSem pista");

        if(n == BODY(lh)->n)
        {
            DEBUG(DEBUG_DESCONECTA,"\nEsta na primeira posicao");

            if(BODY(lh)->lb != NULL)
            {
                DEBUG(DEBUG_DESCONECTA,"\nTem nos acima");

                lista_body *lb;
                lb = BODY(lh)->lb;
                COPY_STRUCT(lh,lb,lista_body);
                libera_lista_body_item(lb);
                return;
            }

            if(lh->lh != NULL)
            {
                DEBUG(DEBUG_DESCONECTA,"\nTem nos do lado");

                lista_head *lh_aux;
                lh_aux = lh->lh;
                COPY_STRUCT(lh,lh_aux,lista_head);
                libera_lista_head_item(lh_aux);
                return;
            }

            DEBUG(DEBUG_DESCONECTA,"\nNão tem mais nenhum");

            BODY(lh)->n = NULL;
            return;
        }

        DEBUG(DEBUG_DESCONECTA,"\nNao esta no primeiro");
        COND_DEBUG(DEBUG_DESCONECTA)
        {
            mostra_no(n,COMPACTO);
            PULA;
            mostra_lista_head_item(lh);
        }

        label *lab;
        lab = LABEL(n);
        if(COMPARE_LABEL(lab,==,NLABEL(lh)))
        {
            DEBUG(DEBUG_DESCONECTA,"\nEsta no primeiro lh");

            lista_body *lb, *lb_next;
            for(lb = BODY(lh), lb_next = lb->lb; n != lb_next->n; lb = lb_next, lb_next = lb->lb);
            lb->lb = lb_next->lb;
            libera_lista_body_item(lb_next);
            return;
        }

        DEBUG(DEBUG_DESCONECTA,"\nBuscando lh");

        lista_head *lh_next;
        for(lh_next = lh->lh; COMPARE_LABEL(lab, !=, NLABEL(lh_next)); lh = lh_next, lh_next = lh->lh);

        if(n == BODY(lh_next)->n)
        {
            DEBUG(DEBUG_DESCONECTA,"\nEsta no primeiro do lh");

            if(BODY(lh_next)->lb != NULL)
            {
                DEBUG(DEBUG_DESCONECTA,"\nTem acima");

                lista_body *lb;
                lb = BODY(lh_next)->lb;
                COPY_STRUCT(lh_next,lb,lista_body);
                libera_lista_body_item(lb);
                return;
            }

            DEBUG(DEBUG_DESCONECTA,"\nTem do lado");

            lh->lh = lh_next->lh;
            libera_lista_head_item(lh_next);
            return;
        }

        DEBUG(DEBUG_DESCONECTA,"\nAchou lh");

        lb_pista = BODY(lh_next);
    }

    DEBUG(DEBUG_DESCONECTA,"\nBuscando lb");

    lista_body *lb, *lb_next;
    for(lb = lb_pista, lb_next = lb->lb; n != lb_next->n; lb = lb_next, lb_next = lb->lb);
    lb->lb = lb_next->lb;
    libera_lista_body_item(lb_next);

    DEBUG(DEBUG_DESCONECTA,"\nSaindo exclui no");
}



void conecta_UM(no *n1, no *n2, char lado)
{
    DEBUG(DEBUG_CONECTA, "\nConectando nos");
    VEST(n1)[lado] = n2;
    inclui_no(HEAD(n2),n1);
}

void conecta_DOIS(no *n, no *nel, no *nth)
{
    conecta_UM(n,nel,ELSE);
    conecta_UM(n,nth,THEN);
}

void desconecta_UM(no *n1, no *n2)
{
    DEBUG(DEBUG_DESCONECTA,"\nDesconecta um");
    COND_DEBUG(DEBUG_DESCONECTA)
    {
        SAI("\nN1");
        mostra_no(n1,COMPLETO);

        SAI("\nN2");
        mostra_no(n2,EXTENDIDO);
        PULA;
        mostra_lista_head_item(n2);

    }
    if(VEST(n1)[LADO(n1,n2)] != n2) exit_program("OPORRA");
    teste_consistencia(n2);

    DEBUG(DEBUG_DESCONECTA,"\nSoltando n1");

    VEST(n1)[LADO(n1,n2)] = NULL;

    DEBUG(DEBUG_DESCONECTA,"\nLados\t%p\t%p",EST(n1)->el,EST(n1)->th);

    exclui_no(HEAD(n2),n1,NULL);
}

void desconecta_UM_pista(no *n1, no *n2, lista_head *lh_pista, lista_body *lb_pista)
{
    VEST(n1)[LADO(n2,n1)] = NULL;
    if(lh_pista == NULL)
        lh_pista = HEAD(n2);
    exclui_no(lh_pista,n1,lb_pista);
}

void desconecta_DOIS(no *n)
{
    DEBUG(DEBUG_DESCONECTA,"\nDesconectando dois\tn: %p",n);
    desconecta_UM(n,EST(n)->el);
    desconecta_UM(n,EST(n)->th);
}

void transfere_conexoes(no *n1, no *n2)
{
    if(n1 == NULL) exit_program("TRANSFERE CONEXOES | N1 E NULL");
    if(n2 == NULL) exit_program("TRANSFERE CONEXOES | N2 E NULL");
    if(n1 == n2)   exit_program("TRANSFERE CONEXOES | N1 2 N2 SAO IGUAS");

    DEBUG(DEBUG_TRANSFERE,"\nInicio Transfere");

    if(BODY(n2)->n == NULL)
    {
        DEBUG(DEBUG_TRANSFERE,"\nSai n2 vazio");

        LIBERA(libera_no,n2);
        return;
    }

    if(BODY(n1)->n == NULL)
    {
        DEBUG(DEBUG_TRANSFERE,"\nSai n1 vazio");

        COPY_STRUCT(n1,n2,lista_head);

        lista_head *lh;
        lista_body *lb;
        for(lh = HEAD(n1); lh != NULL; lh = lh->lh)
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            no *n;
            n = lb->n;
            if(EST(n)->el == n2) EST(n)->el = n1;
            if(EST(n)->th == n2) EST(n)->th = n1;
        }

        LIBERA(libera_no,n2);
        return;
    }

    DEBUG(DEBUG_TRANSFERE,"\nDesconectando todos de n2");
    for(lista_head *lh = HEAD(n2); lh != NULL; lh = lh->lh)
    {
        lista_body *lb;
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            no *n;
            n = lb->n;
            if(EST(n)->el == n2) EST(n)->el = n1;
            if(EST(n)->th == n2) EST(n)->th = n1;
        }
    }
    DEBUG(DEBUG_TRANSFERE,"\nDesconectou");

    if(COMPARE_LABEL(NLABEL(n2), <, NLABEL(n1)))
    {
        DEBUG(DEBUG_TRANSFERE,"\nTrocando");

        lista_head lh;
        COPY_STRUCT(&lh, n1,lista_head);
        COPY_STRUCT( n1, n2,lista_head);
        COPY_STRUCT( n2,&lh,lista_head);
    }

    DEBUG(DEBUG_TRANSFERE,"\nBuscando posicao para inserir n2");
    lista_head *lh, *lh_1, *lh_2;
    label *lab;
    lab = NLABEL(n2);
    for(lh = HEAD(n1), lh_1 = lh->lh; lh_1 != NULL; lh = lh_1, lh_1 = lh->lh)
        if(COMPARE_LABEL(lab,<, NLABEL(lh_1)))
            break;

    DEBUG(DEBUG_TRANSFERE,"\nInserindo n2");
    lh_2 = HEAD(n2)->lh;
    if(COMPARE_LABEL(lab,==,NLABEL(lh)))
    {
        lista_body *lb;
        for(lb = BODY(n2); lb->lb != NULL; lb = lb->lb);
        lb->lb = BODY(lh)->lb;
        BODY(lh)->lb = cria_lista_body_copia(BODY(n2));
    }
    else
    {
        lh->lh = cria_lista_head_copia(HEAD(n2));
        lh = lh->lh;
    }
    LIBERA(libera_no,n2);

    while(lh_1 != NULL & lh_2 != NULL)
    {
        if(COMPARE_LABEL(NLABEL(lh_1), <, NLABEL(lh_2)))
        {
            lh->lh = lh_1;
            lh     = lh->lh;
            lh_1   = lh_1->lh;
            continue;
        }

        lh->lh = lh_2;
        lh     = lh->lh;
        lh_2   = lh_2->lh;

        if(COMPARE_LABEL(NLABEL(lh_1), ==, NLABEL(lh)))
        {
            lista_body *lb, *lb_next;
            for(lb = BODY(lh), lb_next = lb->lb; lb_next != NULL; lb = lb_next, lb_next = lb->lb);
            lb->lb = cria_lista_body_copia(BODY(lh_1));

            lista_head *lh_aux;
            lh_aux = lh_1;
            lh_1   = lh_1->lh;
            LIBERA(libera_lista_head_item,lh_aux);

            continue;
        }
    }

    if(lh_1 != NULL)
        lh->lh = lh_1;
    else if(lh_2 != NULL)
        lh->lh = lh_2;

    DEBUG(DEBUG_TRANSFERE,"\nSAINDO TRANSFERENCIA");
}



void libera_arvore(no *n)
{
    COND_DEBUG(DEBUG_LIBERA_ARVORE)
    {
        SAI("\nEntrando libera arvore\t\t");
        mostra_ponteiro(n);
        SAI("\t\t\tLABEL: ");
        mostra_label(LABEL(n),0);

        mostra_arvore(n,COMPLETO);
        SAI("\nMOSTROU");
    }

    if(BODY(n)->n != NULL)
    {
        DEBUG(DEBUG_LIBERA_ARVORE,"\nIncapaz de liberar");
        return;
    }

    if(LABEL(n)->ni > 0)
    {

        no *N[2];
        DEBUG(DEBUG_LIBERA_ARVORE,"\nCopiando sucessores");
        COPY_STRUCT(N,VEST(n),estrutura);
        COND_DEBUG(DEBUG_LIBERA_ARVORE)
        {
            LADOS
            {
                SAI("\tN[%d]: ",k);mostra_ponteiro(N[k]);
            }
        }

        DEBUG(DEBUG_LIBERA_ARVORE,"\nDesconectando sucessores");
        desconecta_DOIS(n);

        DEBUG(DEBUG_LIBERA_ARVORE,"\nLiberando sucessores");
        LADOS
        libera_arvore(N[k]);
    }
    libera_no(n);

    DEBUG(DEBUG_LIBERA_ARVORE,"\nSaindo libera arvore");
}

void libera_QDD(QDD Q)
{
    DEBUG(DEBUG_REDUZ_QDD,"\nLiberando Arvore");
    libera_arvore(Q.n);
    DEBUG(DEBUG_REDUZ_QDD,"\nLiberando lista");
    libera_lista_body_lista(Q.lb);
}



int compara_amplitude(amplitude *amp_1, amplitude *amp_2)
{
    numero re;
    re = amp_1->re - amp_2->re;
    IF_ZERO(re)
    {
        numero im;
        im = amp_1->im - amp_2->im;
        IF_ZERO(im)
            return 1;
    }
    return 0;
}

int compara_amplitude_zero(amplitude *amp)
{
    IF_ZERO(amp->re > -eps)
    IF_ZERO(amp->im > -eps)
        return 1;
    return 0;
}

void multiplica_amplitude_real(amplitude *amp, numero re)
{
    amp->re *= re;
    amp->im *= re;
}

void multiplica_amplitudes(amplitude *amp1, amplitude *amp2)
{
    amplitude amp;
    amp.re = amp1->re * amp2->re - amp1->im * amp2->im;
    amp.im = amp1->re * amp2->im + amp1->im * amp2->re;
    COPY_STRUCT(amp1,&amp,amplitude);
}

void multiplica_QDD_real(QDD Q, numero re)
{
    lista_body *lb;
    for(lb = Q.lb; lb != NULL; lb = lb->lb)
        multiplica_amplitude_real(AMP(lb->n),re);
}

void multiplica_QDD_amplitude(QDD Q, amplitude *amp)
{
    lista_body *lb;
    for(lb = Q.lb; lb != NULL; lb = lb->lb)
        multiplica_amplitudes(AMP(lb->n),amp);
}



amplitude subtracao(amplitude *amp1, amplitude *amp2)
{
    amplitude amp;
    amp.re = amp1->re-amp2->re;
    amp.im = amp1->im-amp2->im;
    return amp;
}

lista_body* copia_lista_body(lista_body *lb)
{
    if(lb == NULL)
        return NULL;

    lista_body *lb_out;
    lb_out = cria_lista_body(lb->n,NULL);

    lista_body *lb_1;
    for(lb_1 = lb_out, lb = lb->lb; lb != NULL; lb_1 = lb_1->lb, lb = lb->lb)
        lb_1->lb = cria_lista_body(lb->n,NULL);

    return lb_out;
}

lista_body* busca_amplitude(lista_body *lb, amplitude *amp, int *res, lista_body *lb_pista)
{
    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nEntrando busca amplitude");
    COND_DEBUG(DEBUG_BUSCA_AMPLITUDE)
    {
        SAI("\namp: ");mostra_amplitude(amp);
        SAI("\tpista: ");mostra_ponteiro(lb_pista);
        if(lb_pista != NULL)
        {
            mostra_lista_body_item(lb_pista);
            if(lb_pista->lb != NULL)
            {
                //mostra_lista_body_item(lb_pista->lb);

                SAI("\namp_pista: ");
                mostra_amplitude(AMP(lb_pista->lb->n));
            }
        }
    }

    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nCalculando limites");

    numero re1, re2;
    re1 = amp->re - eps;
    re2 = amp->re + eps;

    numero im1, im2;
    im1 = amp->im - eps;
    im2 = amp->im + eps;

    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nTalvez subtituindo");

    if(lb_pista     != NULL)
    if(lb_pista->lb != NULL)
    {
        DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nAinda tentando");

        if(AMP(lb_pista->lb->n)->re < re1)
        {
            DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nSubstituicao 1");

            lb = lb_pista;
        }
        else if(AMP(lb_pista->lb->n)->re < re2)
        if(AMP(lb_pista->lb->n)->im < im2)
        {
            DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nSubstituicao 2");

            lb = lb_pista;
        }
    }

    if(lb->lb == NULL)
    {
        DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nSaida 0");
        return lb;
    }


    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nPercorrendo pelos reais");

    for(; lb->lb != NULL; lb = lb->lb)
        if(AMP(lb->lb->n)->re > re1)
            break;

    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nParou");

    if(lb->lb == NULL)
        return lb;

    if(AMP(lb->lb->n)->re > re2)
    {
        DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nSaida 1");
        return lb;
    }

    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nPercorrendo pelos complexos");

    for(; lb->lb != NULL; lb = lb->lb)
    {
        if(AMP(lb->lb->n)->re < re2)
        if(AMP(lb->lb->n)->im < im1)
            continue;
        break;
    }

    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nParou");

    if(lb->lb != NULL)
    if(AMP(lb->lb->n)->re < re2)
    if(AMP(lb->lb->n)->im < im2)
        *res = 1;

    DEBUG(DEBUG_BUSCA_AMPLITUDE, "\nSaindo busca amplitude");
    return lb;
}

lista_body* busca_estrutura(lista_body *lb, no *n2, int lado, int *res, lista_body *lb_pista)
{
    COND_DEBUG(DEBUG_BUSCA_ESTRUTURA)
    {
        SAI("\nEntrando busca estrutura");
        SAI("\nlb: ");mostra_ponteiro(lb);SAI("\t\tn2: ");mostra_ponteiro(n2);
        SAI("\t\tlado: %d\t\tres: %d\t\tlb_pista: ",lado,*res);mostra_ponteiro(lb_pista);
    }

    DEBUG(DEBUG_BUSCA_ESTRUTURA,"\nAvaliando pista");
    if(lb_pista     != NULL)
    if(lb_pista->lb != NULL)
    if(n2 <= VEST(lb_pista->lb->n)[lado])
    {
        DEBUG(DEBUG_BUSCA_ESTRUTURA,"\nPista aceita");
        lb = lb_pista;
    }


    DEBUG(DEBUG_BUSCA_ESTRUTURA,"\nPercorrendo lista");
    for(; lb->lb != NULL; lb = lb->lb)
        if(n2 <= VEST(lb->lb->n)[lado])
            break;

    DEBUG(DEBUG_BUSCA_ESTRUTURA,"\nAvaliando posicao");
    if(lb->lb != NULL)
    if(n2 == VEST(lb->lb->n)[lado])
    {
        DEBUG(DEBUG_BUSCA_ESTRUTURA,"\nPosicao aceita");
        *res = 1;
    }

    DEBUG(DEBUG_BUSCA_ESTRUTURA,"\nSaindo busca estrutura");
    return lb;
}

#define INTERNO_REDUZ_LISTA 1

lista_body* reduz_lista_amplitude(lista_body *lb_0)
{
    COND_DEBUG(DEBUG_REDUZ_LISTA)
    {
        SAI("\nEntrando reduz lista amplitude");
        SAI("\nLista body entrada");
        mostra_lista_body_item(lb_0);
    }

    lista_body *lb = lb_0->lb;
    if(lb->lb == NULL)
        return NULL;

    DEBUG(DEBUG_REDUZ_LISTA,"\nZerando array");

    lista_body **LB_c;
    LB_c = LB[0];
    LB_c[0]->lb = NULL;
    LB_c[1]->lb = NULL;

    DEBUG(DEBUG_REDUZ_LISTA,"\nEntrando loop");

    lista_body *lb_pista[2] = {NULL,NULL};
    Long quant = 0, tot, tam = 1e5;
    COND_DEBUG(DEBUG_REDUZ_LISTA)
    {
        SAI("\nLista body para loop");
        mostra_lista_body_item(lb);
    }

    COND_DEBUG(DEBUG_REDUZ_QDD) tot = conta_itens_lista_body(lb);
    DEBUG(DEBUG_REDUZ_LISTA,"\nEntrando loop");

    while(lb != NULL)
    {
        DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\nNovo lb : ");
        COND_DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA)mostra_amplitude(AMP(lb->n));
        COND_DEBUG(DEBUG_REDUZ_QDD)
        {
            quant++;
            if(quant%tam == 0)
                SAI("\nQuant : %4llu / %4llu\ttam: %llu", quant / tam, tot / tam, tam);
        }

        lista_body *lb_c;
        lb_c = lb;
        lb   = lb->lb;

        lista_body *lb_2;
        int res = 0;
        lb_2 = lb_pista[1] = busca_amplitude(LB_c[1], AMP(lb_c->n), &res, lb_pista[1]);

        if(res)
        {
            DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\tAchou na Segunda lista");
            if(!compara_amplitude(AMP(lb_2->lb->n),AMP(lb_c->n)))
                exit_program("TOMANOCU CACETA ESSA MERDA");

            amplitude amp = subtracao(AMP(lb_2->lb->n),AMP(lb_c->n));
            COND_DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA)
            {
                SAI("\nAmplitude: ");mostra_amplitude(&amp);SAI("\t\t% .4e",eps);
                mostra_no_amplitude(lb_2->lb->n,COMPLETO);
                mostra_no_amplitude(lb_c->n,COMPLETO);
            }
            transfere_conexoes(lb_2->lb->n,lb_c->n);
            libera_lista_body_item(lb_c);
            continue;
        }

        lista_body *lb_1;
        lb_1 = lb_pista[0] = busca_amplitude(LB_c[0], AMP(lb_c->n), &res, lb_pista[0]);
        if(res)
        {
            DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\tAchou na Primeira lista");

            transfere_conexoes(lb_1->lb->n,lb_c->n);
            LIBERA(libera_lista_body_item,lb_c);
            lb_c     = lb_1->lb;
            lb_1->lb = lb_c->lb;

            lb_c->lb = lb_2->lb;
            lb_2->lb = lb_c;
            continue;
        }
        DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\tNao achou em nenhuna");

        lb_c->lb = lb_1->lb;
        lb_1->lb = lb_c;
    }

    DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\nBuscando Final");
    DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\nlb: %p\tlb->lb: %p",LB_c[0],LB_c[0]->lb);

    for(lb = LB_c[0]; lb->lb != NULL; lb = lb->lb) DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\nlb: %p\tlb->lb: %p",lb,lb->lb);

    DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\nlb: %p\tlb->lb: %p",lb,lb->lb);
    DEBUG(DEBUG_REDUZ_LISTA && INTERNO_REDUZ_LISTA, "\nLigando listas");

    lb->lb = LB_c[1]->lb;

    DEBUG(DEBUG_REDUZ_LISTA,"\nSaindo reduz lista;");
    lb_0->lb = LB_c[0]->lb;
    return copia_lista_body(LB_c[1]->lb);
}

void reduz_QDD(QDD *Q)
{
    DEBUG(DEBUG_REDUZ_QDD,"\nEntrando reducao");

    DEBUG(DEBUG_REDUZ_QDD,"\nReduzindo lista amplitude");
    COND_DEBUG(DEBUG_REDUZ_QDD)
    {
        Long quant = conta_itens_lista_body(Q->lb);
        SAI("\nQuantidade : %lu",quant);
        mostra_QDD(*Q,COMPLETO);
        mostra_lista_body_item(BODY(Q));
    }
    lista_body *lb;
    lb = reduz_lista_amplitude(BODY(Q));
    DEBUG(DEBUG_REDUZ_QDD,"\nSaiu Reducao lista amplitude");
    COND_DEBUG(DEBUG_REDUZ_QDD)
    {
        Long quant = conta_itens_lista_body(lb);
        SAI("\nQuantidade mesclados : %lu",quant);
        mostra_QDD(*Q,EXTENDIDO);
        mostra_QDD(*Q,SIMPLES);
        SAI("\n------");
    }
    if(lb == NULL)
        return;

    lista_head *lh;
    lh = cria_lista_head_body(lb,NULL);
    libera_lista_body_item(lb);

    while(lh != NULL)
    {
        DEBUG(DEBUG_REDUZ_QDD,"\nNovo nivel: ");
        COND_DEBUG(DEBUG_REDUZ_QDD)mostra_label(NLABEL(lh),0);
        /*** Regra 1 ***/

        DEBUG(DEBUG_REDUZ_QDD,"\nRegra 1");
        lista_head *lh_n;
        no  *n, *n1, *n2;
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            DEBUG(DEBUG_REDUZ_QDD,"\nNovo no");
            COND_DEBUG(DEBUG_REDUZ_QDD)mostra_no(lb->n,EXTENDIDO);

            n  = lb->n;
            n1 = BODY(n)->n;
            while(n1 != NULL)
            {
                if(EST(n1)->el != EST(n1)->th)
                    break;

                DEBUG(DEBUG_REDUZ_QDD,"\nCaso 1");

                desconecta_DOIS(n1);
                transfere_conexoes(n,n1);
                n1 = BODY(n)->n;

                DEBUG(DEBUG_REDUZ_QDD,"\nParcial");
                COND_DEBUG(DEBUG_REDUZ_QDD)mostra_no(lb->n,EXTENDIDO);
            }

            if(n1 == NULL)
            {
                DEBUG(DEBUG_REDUZ_QDD,"\nSaindo pela culatra");

                Q->n = n1;
                libera_lista_head_item(lh);
                return;
            }

            lista_body *lb_n_1, *lb_n_2;
            for(lb_n_1 = BODY(n); lb_n_1->lb != NULL; lb_n_1 = lb_n_2)
            {
                lb_n_2 = lb_n_1->lb;
                n1     = lb_n_2->n;

                if(EST(n1)->el != EST(n1)->th)
                    continue;

                DEBUG(DEBUG_REDUZ_QDD,"\nCaso 2");

                desconecta_UM_pista(n1,n,NULL,lb_n_1);
                desconecta_UM_pista(n1,n,NULL,lb_n_1);
                transfere_conexoes(n,n1);

                lb_n_2 = lb_n_1;

                DEBUG(DEBUG_REDUZ_QDD,"\nParcial");
                COND_DEBUG(DEBUG_REDUZ_QDD)mostra_no(lb->n,EXTENDIDO);
            }

            for(lh_n = HEAD(n); lh_n->lh != NULL; lh_n = lh_n->lh)
            {
                n1 = BODY(lh_n->lh)->n;
                while(EST(n1)->el == EST(n1)->th)
                {
                    DEBUG(DEBUG_REDUZ_QDD,"\nCaso 3");

                    desconecta_UM_pista(n1,n,lh_n,NULL);
                    desconecta_UM_pista(n1,n,lh_n,NULL);
                    n1 = BODY(lh_n->lh)->n;
                }

                for(lb_n_1 = BODY(lh_n->lh); lb_n_1->lb != NULL; lb_n_1 = lb_n_2)
                {
                    lb_n_2 = lb_n_1->lb;
                    n1 = lb_n_2->n;
                    if(EST(n1)->el != EST(n1)->th)
                        continue;

                    DEBUG(DEBUG_REDUZ_QDD,"\nCaso 4");

                    desconecta_UM_pista(n1,n,NULL,lb_n_1);
                    desconecta_UM_pista(n1,n,NULL,lb_n_1);
                    transfere_conexoes(n,n1);
                    lb_n_2 = lb_n_1;
                }
            }

            DEBUG(DEBUG_REDUZ_QDD,"\nResultado");
            COND_DEBUG(DEBUG_REDUZ_QDD)mostra_no(lb->n,EXTENDIDO);
        }

        DEBUG(DEBUG_REDUZ_QDD,"\nQDD parcial 1");
        COND_DEBUG(DEBUG_REDUZ_QDD) mostra_QDD(*Q,COMPLETO);

        /*** Regra 2 ***/

        DEBUG(DEBUG_REDUZ_QDD,"\nRegra 2");
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            n = lb->n;
            DEBUG(DEBUG_REDUZ_QDD,"\nNovo no");
            COND_DEBUG(DEBUG_REDUZ_QDD)mostra_no(lb->n,EXTENDIDO);

            for(lh_n = HEAD(n); lh_n != NULL; lh_n = lh_n->lh)
            {
                DEBUG(DEBUG_REDUZ_QDD,"\nNovo nivel ");
                COND_DEBUG(DEBUG_REDUZ_QDD)mostra_label(NLABEL(lh_n),0);

                if(BODY(lh_n)->lb == NULL)
                {
                    DEBUG(DEBUG_REDUZ_QDD,"\tpulando");
                    continue;
                }


                DEBUG(DEBUG_REDUZ_QDD,"\tvasculhando");
                DEBUG(DEBUG_REDUZ_QDD,"\nPreparando auxuliares");
                lista_body *lb_aux;
                lista_body *LB_pista[2][2] = {{NULL,NULL},{NULL,NULL}};
                LB[0][0]->lb = NULL;
                LB[0][1]->lb = NULL;
                LB[1][0]->lb = NULL;
                LB[1][1]->lb = NULL;

                COPY_STRUCT(lb_zero,lh_n,lista_body);
                COND_DEBUG(DEBUG_REDUZ_QDD)
                {
                    SAI("\nLista a ser vasculhada");
                    mostra_lista_body(lb_zero,COMPLETO);
                    SAI("\nMostrou");
                }
                while(lb_zero != NULL)
                {
                    DEBUG(DEBUG_REDUZ_QDD,"\nNovo loop");

                    lb_aux  = lb_zero;
                    lb_zero = lb_zero->lb;
                    n1 = lb_aux->n;

                    COND_DEBUG(DEBUG_REDUZ_QDD)
                    {
                        SAI("\nLista restante");
                        mostra_lista_body(lb_zero,COMPLETO);
                        PULA;
                        SAI("\nItem avaliado");
                        mostra_lista_body_item(lb_aux);
                    }

                    int lado;
                    lado = !LADO(n1,n);
                    n2   =  VEST(n1)[lado];

                    DEBUG(DEBUG_REDUZ_QDD,"\nLado: %d",lado);



                    DEBUG(DEBUG_REDUZ_QDD,"\nBuscando segunda lista");
                    lista_body *lb_1, *lb_2;
                    int res = 0;
                    lb_2 = LB_pista[lado][1] = busca_estrutura(LB[lado][1],n2,lado,&res,LB_pista[lado][1]);
                    DEBUG(DEBUG_REDUZ_QDD,"\nTerminou busca");
                    if(res)
                    {
                        COND_DEBUG(DEBUG_REDUZ_QDD)
                        {
                            SAI("\nAchou");
                            SAI("\nn1");
                            mostra_no(n1,COMPLETO);
                            SAI("\nn2\t");mostra_ponteiro(lb_2->lb->n);
                            mostra_no(lb_2->lb->n,COMPLETO);
                        }

                        DEBUG(DEBUG_REDUZ_QDD,"\nLiberando lista");

                        libera_lista_body_item(lb_aux);

                        DEBUG(DEBUG_REDUZ_QDD,"\nDesconectando n2");

                        desconecta_UM(n1,n2);

                        DEBUG(DEBUG_REDUZ_QDD,"\nTransferindo conexoes");

                        transfere_conexoes(lb_2->lb->n,n1);

                        DEBUG(DEBUG_REDUZ_QDD,"\nTerminou");

                        DEBUG(DEBUG_REDUZ_QDD,"\nlb_zero: ");
                        COND_DEBUG(DEBUG_REDUZ_QDD)mostra_ponteiro(lb_zero);
                        continue;
                    }

                    DEBUG(DEBUG_REDUZ_QDD,"\nBuscando primeira lista");
                    lb_1 = LB_pista[lado][0] = busca_estrutura(LB[lado][0],n2,lado,&res,LB_pista[lado][0]);
                    DEBUG(DEBUG_REDUZ_QDD,"\nTerminou busca");
                    if(res)
                    {
                        libera_lista_body_item(lb_aux);

                        lb_aux   = lb_1->lb;
                        lb_1->lb = lb_aux->lb;

                        lb_aux->lb = lb_2->lb;
                        lb_2->lb   = lb_aux;

                        desconecta_UM(n1,n2);
                        transfere_conexoes(lb_aux->n,n1);
                        continue;
                    }

                    lb_aux->lb = lb_1->lb;
                    lb_1->lb   = lb_aux;
                }

DEBUG(DEBUG_REDUZ_QDD,"\nSaiu loop");

DEBUG(DEBUG_REDUZ_QDD,"\nConectando listas");

COND_DEBUG(DEBUG_REDUZ_QDD)
{
SAI("\nLISTA 00");
mostra_lista_body(LB[0][0]->lb,COMPLETO);
PULA;
SAI("\nLISTA 01");
mostra_lista_body(LB[0][1]->lb,COMPLETO);
PULA;
SAI("\nLISTA 10");
mostra_lista_body(LB[1][0]->lb,COMPLETO);
PULA;
SAI("\nLISTA 11");
mostra_lista_body(LB[1][1]->lb,COMPLETO);
PULA;
}

                for(lb_aux = LB[0][1]; lb_aux->lb != NULL; lb_aux = lb_aux->lb);
                lb_aux->lb = LB[1][1]->lb;
                if(LB[0][1]->lb != NULL)
                {

COND_DEBUG(DEBUG_REDUZ_QDD)
{
    SAI("\nAdicionando lista nova");
    mostra_lista_body(LB[0][1]->lb,COMPLETO);
    SAI("\nMostrou");
}

                    label *lab;
                    lab = NLABEL(LB[0][1]->lb);

DEBUG(DEBUG_REDUZ_QDD,"\nBuscando lh");

                    lista_head *lh_aux;
                    for(lh_aux = lh; lh_aux->lh != NULL; lh_aux = lh_aux->lh)
                        if(COMPARE_LABEL(lab,<,NLABEL(lh_aux->lh)))
                            break;

DEBUG(DEBUG_REDUZ_QDD,"\nTerminou");

                    if(COMPARE_LABEL(lab,==,NLABEL(lh_aux)))
                    {

DEBUG(DEBUG_REDUZ_QDD,"\nAchou lh");

                        lista_body *lb_aux_2;
                        lb_aux = copia_lista_body(LB[0][1]->lb);
                        for(lb_aux_2 = lb_aux; lb_aux_2->lb != NULL; lb_aux_2 = lb_aux_2->lb);
                        lb_aux_2->lb = BODY(lh_aux)->lb;
                        BODY(lh_aux)->lb = lb_aux;
                    }
                    else
                    {

DEBUG(DEBUG_REDUZ_QDD,"\nCriando lh novo");

                        lh_aux->lh = cria_lista_head_body(LB[0][1]->lb,lh_aux->lh);
                        lh_aux = lh_aux->lh;
                        BODY(lh_aux)->lb = copia_lista_body(BODY(lh_aux)->lb);

DEBUG(DEBUG_REDUZ_QDD,"\nFoi");

                    }
                }

COND_DEBUG(DEBUG_REDUZ_QDD)
{
    SAI("\nLista CARALHO NESSA MERDA");
    mostra_lista_body(LB[0][1]->lb,COMPLETO);

    SAI("\nAdicionou lista");
    SAI("\nFoi");
    SAI("\nLista parcial 1");mostra_lista_body(LB[0][0]->lb,COMPLETO);
}

                for(lb_aux     = LB[0][0]    ; lb_aux->lb != NULL; lb_aux = lb_aux->lb);

DEBUG(DEBUG_REDUZ_QDD,"\nCompletou parte 1");
COND_DEBUG(DEBUG_REDUZ_QDD){SAI("\nLista parcial 2");mostra_lista_body(LB[0][0]->lb,COMPLETO);}

                for(lb_aux->lb = LB[1][0]->lb; lb_aux->lb != NULL; lb_aux = lb_aux->lb);

COND_DEBUG(DEBUG_REDUZ_QDD){SAI("\nLista parcial 3");mostra_lista_body(LB[0][0]->lb,COMPLETO);}
DEBUG(DEBUG_REDUZ_QDD,"\nCompletou parte 2");

                lb_aux->lb  = LB[0][1]->lb;

COND_DEBUG(DEBUG_REDUZ_QDD){SAI("\nLista parcial 4");mostra_lista_body(LB[0][0]->lb,COMPLETO);}

                DEBUG(DEBUG_REDUZ_QDD,"\nFinalizou conexao");
                COND_DEBUG(DEBUG_REDUZ_QDD)
                {
                    SAI("\nLista final");
                    mostra_lista_body(LB[0][0]->lb,COMPLETO);
                }

                lb_zero = LB[0][0]->lb;

                DEBUG(DEBUG_REDUZ_QDD,"\nRecuperou lb_zero");

                COPY_STRUCT(lh_n,lb_zero,lista_body);

                DEBUG(DEBUG_REDUZ_QDD,"\nEncerrou lh");
            }

            DEBUG(DEBUG_REDUZ_QDD,"\nResultado");
            COND_DEBUG(DEBUG_REDUZ_QDD)mostra_no(lb->n,EXTENDIDO);
        }

        DEBUG(DEBUG_REDUZ_QDD,"\nQDD parcial 2");
        COND_DEBUG(DEBUG_REDUZ_QDD) mostra_QDD(*Q,COMPLETO);

        lh_n = lh;
        lh   = lh->lh;

        libera_lista_body_lista(BODY(lh_n)->lb);
        libera_lista_head_item(lh_n);
    }
    DEBUG(DEBUG_REDUZ_QDD,"\nQDD final");
    COND_DEBUG(DEBUG_REDUZ_QDD) mostra_QDD(*Q,SIMPLES);
    DEBUG(DEBUG_REDUZ_QDD,"\n-----");
    COND_DEBUG(DEBUG_REDUZ_QDD) mostra_lista_body_amplitudes(Q->lb);
    DEBUG(DEBUG_REDUZ_QDD,"\nSaindo reduz QDD");
}



void libera_matriz(int height, int length, apply *A[height][length])
{
    int i, j;
    for(i=0; i<height; i++)
    for(j=0; j<length; j++)
    if(A[i][j] != NULL)
        libera_apply_lista(A[i][j]);
}

void encaixa_arvore(no *n, apply *A[LABEL(n)->ni+1][3])
{
    apply *a;
    a = cria_apply(n,NULL);
    A[ACCESS(n)] = a;

    int i, j, k;
    for(i=LABEL(n)->ni; i> 0; i--)
    for(j=2; j>=0; j--)
    for(a = A[i][j]; a != NULL; a = a->a)
    {
        no **N;
        N = EST(a->n1);
        for(k=0; k<2; k++)
        {
            apply *a_1;
            n = N[k];
            if(BODY(n)->n != a->n1)
                continue;

            a_1 = cria_apply(n,NULL);
            VAPPLY(a)[k] = a_1;

            a_1->a = A[ACCESS(n)];
            A[ACCESS(n)] = a_1;

            apply *a_2;
            lista_body *lb;
            for(lb = BODY(n)->lb ; lb != NULL; lb = lb->lb)
            {
                for(a_2 = A[ACCESS(lb->n)]; a_2->n1 != n   ; a_2 = a_2->a);
                VAPPLY(a_2)[LADO(lb->n,n)] = a_1;
            }

            lista_head *lh;
            for(lh = HEAD(n)->lh; lh != NULL; lh = lh->lh)
            for(lb = BODY(lh)   ; lb != NULL; lb = lb->lb)
            {
                for(a_2 = A[ACCESS(lb->n)]; a_2->n1 != n   ; a_2 = a_2->a);
                VAPPLY(a_2)[LADO(lb->n,n)] = a_1;
            }
        }
    }
}

no* monta_arvore(int height, int length, apply *A[height][length])
{
    apply *a;
    no *n;
    for(a = A[0][0]; a != NULL; a = a->a)
        a->n2 = n = copia_no_amplitude(a->n1);

    int i, j;
    no *n1, *n2;
    for(i=1; i<height; i++)
    for(j=0; j<length; j++)
    for(a = A[i][j]; a != NULL; a = a->a)
    {
        n  = a->n2 = copia_no_estrutura(a->n1);
        n1 = a->a1->n2;
        n2 = a->a2->n2;
        conecta_DOIS(n,n1,n2);
    }
    return n;
}

QDD monta_QDD(int height, int length, apply *A[height][length])
{
    QDD Q;
    lista_body *lb;
    apply *a;
    Q.n = monta_arvore(height,length,A);
    for(lb = NULL, a = A[0][0]; a != NULL; a = a->a)
        lb = cria_lista_body(a->n2,lb);
    Q.lb = lb;
    return Q;
}

no* copia_arvore(no *n)
{
    int height = LABEL(n)->ni + 1;
    apply *A[height][3];
    ZERA(A,1);
    encaixa_arvore(n,A);
    n = monta_arvore(height, 3, A);
    libera_matriz(height, 3, A);
    return n;
}

QDD copia_QDD(QDD Q0)
{
    int height;
    height = Q0.N+1;

    apply *A[height][3];
    ZERA(A,1);
    encaixa_arvore(Q0.n,A);

    QDD Q1;
    Q1 = monta_QDD(height,3,A);
    Q1.N = Q0.N;
    libera_matriz(height,3,A);

    return Q1;
}



QDD produto_tensorial(QDD Q1, QDD Q2)
{
    if(Q1.n == Q2.n)
        Q2 = copia_QDD(Q1);

    if(Q2.lb->lb == NULL)
    {
        if(compara_amplitude_zero(AMP(Q2.n)))
        {
            libera_QDD(Q1);
            return Q2;
        }

        multiplica_QDD_amplitude(Q1,AMP(Q2.n));
        libera_QDD(Q2);
        return Q1;
    }

    if(Q1.lb->lb  == NULL)
    {
        if(compara_amplitude_zero(AMP(Q1.n)))
        {
            libera_QDD(Q2);
            return Q1;
        }

        multiplica_QDD_amplitude(Q2,AMP(Q1.n));
        libera_QDD(Q1);
        return Q2;
    }

    int N, height;
    N = Q2.N;
    height = N + 1;
    Q1.N  += N;

    lista_head *lh;
    lista_body *lb;
    lh = enlista_arvore(Q1.n);

    while(lh->lh != NULL)
    {
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
            LABEL(lb->n)->ni += N;

        lista_head *lh_aux;
        lh_aux = lh;
        lh = lh->lh;
        libera_lista_body_lista(BODY(lh_aux)->lb);
        libera_lista_head_item(lh_aux);
    }
    libera_lista_body_lista(BODY(lh)->lb);
    libera_lista_head_item(lh);

    apply *A[height][3];
    ZERA(A,1);
    encaixa_arvore(Q2.n,A);

    lista_body *lb_c;
    lb_c   = Q1.lb;
    lb     = BODY(&Q1);
    lb->lb = NULL;

    Long cont = 0;
    while(lb_c != NULL)
    {
        DEBUG(DEBUG_PRODUTO_TENSORIAL,"\nNovo no : %llu/%d",cont++,Q1.N);

        if(compara_amplitude_zero(AMP(lb_c->n)))
        {
            DEBUG(DEBUG_PRODUTO_TENSORIAL,"\nPulando nulo");

            lb->lb = cria_lista_body(lb_c->n,NULL);
            lb = lb->lb;
            continue;
        }

        QDD Q;
        Q = monta_QDD(height,3,A);
        multiplica_QDD_amplitude(Q,AMP(lb_c->n));
        transfere_conexoes(Q.n,lb_c->n);
        for(lb->lb = Q.lb; lb->lb != NULL; lb = lb->lb);

        lista_body *lb_aux;
        lb_aux = lb_c;
        lb_c = lb_c->lb;
        libera_lista_body_item(lb_aux);
    }
    //reduz_QDD(&Q1);
    libera_QDD(Q2);
    libera_matriz(height,3,A);

    return Q1;
}



lista_body* enlista_dois(no *n1, no *n2, lista_body *lb_next)
{
    lista_body *lb;
    lb =   cria_lista_body(n2,lb_next);
    return cria_lista_body(n1,lb);
}

QDD um()
{
    QDD Q;
    Q.n  = cria_no_amplitude(1,0);
    Q.N  = 0;
    Q.lb = cria_lista_body(Q.n,NULL);
    return Q;
}

QDD H()
{
    numero amp = pow(2,-0.5);


    no *n1, *n2, *n3, *n4;
    n1 = cria_no_amplitude( amp,0);
    n2 = cria_no_amplitude( amp,0);
    n3 = cria_no_amplitude( amp,0);
    n4 = cria_no_amplitude(-amp,0);

    no *n5, *n6;
    n5 = cria_no_estrutra(C,1);
    n6 = cria_no_estrutra(C,1);

    conecta_DOIS(n5,n1,n2);
    conecta_DOIS(n6,n3,n4);

    no *n;
    n = cria_no_estrutra(R,1);
    conecta_DOIS(n,n5,n6);

    lista_body *lb;
    lb = enlista_dois(n3,n4,NULL);
    lb = enlista_dois(n1,n2,lb);

    QDD Q;
    Q.n  = n;
    Q.N  = 1;
    Q.lb = lb;
    return Q;
}

QDD H_2()
{
    no *n[5][16];
    int i, j;
    int exp;
    for(i=0, exp = 1; i < 4; i++, exp *= 2)
    for(j=0; j<exp; j++)
        n[i][j] = cria_no_estrutra(2*(1-i%2),2-(i/2));

    numero re = 0.5;

    n[4][ 0] = cria_no_amplitude( re,0);
    n[4][ 1] = cria_no_amplitude( re,0);
    n[4][ 2] = cria_no_amplitude( re,0);
    n[4][ 3] = cria_no_amplitude(-re,0);
    n[4][ 4] = cria_no_amplitude( re,0);
    n[4][ 5] = cria_no_amplitude( re,0);
    n[4][ 6] = cria_no_amplitude( re,0);
    n[4][ 7] = cria_no_amplitude(-re,0);
    n[4][ 8] = cria_no_amplitude( re,0);
    n[4][ 9] = cria_no_amplitude( re,0);
    n[4][10] = cria_no_amplitude( re,0);
    n[4][11] = cria_no_amplitude(-re,0);
    n[4][12] = cria_no_amplitude(-re,0);
    n[4][13] = cria_no_amplitude(-re,0);
    n[4][14] = cria_no_amplitude(-re,0);
    n[4][15] = cria_no_amplitude( re,0);

    for(i=0, exp = 1; i < 4; i++, exp *= 2)
    for(j=0; j<exp; j++)
        conecta_DOIS(n[i][j],n[i+1][2*j],n[i+1][2*j+1]);

    lista_body *lb;
    j = 16;
    lb = NULL;
    for(j=15, lb = NULL; j>=0; j--)
        lb = cria_lista_body(n[4][j],lb);

    QDD Q;
    Q.n  = n[0][0];
    Q.N  = 2;
    Q.lb = lb;
    return Q;
}

QDD limite()
{
    no *n[5][16];
    int i, j;
    int exp;
    for(i=0, exp = 1; i < 4; i++, exp *= 2)
        for(j=0; j<exp; j++)
            n[i][j] = cria_no_estrutra(V,5-i);

    numero re = 0.5;

    for(j=0; j<16; j++)
        n[4][j] = cria_no_amplitude( re,0);

    for(i=0, exp = 1; i < 4; i++, exp *= 2)
        for(j=0; j<exp; j++)
            conecta_DOIS(n[i][j],n[i+1][2*j],n[i+1][2*j+1]);

    lista_body *lb;
    j = 16;
    lb = NULL;
    for(j=15, lb = NULL; j>=0; j--)
        lb = cria_lista_body(n[4][j],lb);

    QDD Q;
    Q.n  = n[0][0];
    Q.N  = 2;
    Q.lb = lb;
    return Q;
}



void teste_conexao()
{
    no *N;
    N = cria_no_amplitude(1,2);
    SAI("\n\n\n\n\nINICIO TESTE CONEXAO");
    mostra_no(N,EXTENDIDO);

    no *n[7];
    n[0] = cria_no_estrutra(V,1);
    n[1] = cria_no_estrutra(V,1);
    n[2] = cria_no_estrutra(C,1);
    n[3] = cria_no_estrutra(C,2);
    n[4] = cria_no_estrutra(C,2);
    n[5] = cria_no_estrutra(R,1);

    int i;
    for(i=0; i < 6; i++)
    {
        SAI("\n------------------------------------------------------------------------");
        SAI("\n\nNO %d", i);
        mostra_no(n[i],EXTENDIDO);
        conecta_UM(n[i], N, ELSE);
        SAI("\nDepois da conexao\n");
        mostra_no(n[i],EXTENDIDO);
        mostra_no(N,EXTENDIDO);
        mostra_quantidades(I);
    }

    for(i=0; i < 6; i++)
    {
        desconecta_UM(n[i], N);
        libera_no(n[i]);
    }
    libera_no(N);
    SAI("\nFIM TESTE CONEXAO");
    mostra_quantidades(I);

    if(!memoria_zerada()) exit_program("VAZAMENTO DE MEMORIA CONEXAO");
}

void teste_desconexao()
{
    SAI("\n\n\n\n\nINICIO TESTE DESCONEXAO");
    no *N, *n[9];
    N    = cria_no_amplitude(1,2);
    n[0] = cria_no_estrutra(C,1);
    n[1] = cria_no_estrutra(C,1);
    n[2] = cria_no_estrutra(R,1);
    n[3] = cria_no_estrutra(C,2);
    n[4] = cria_no_estrutra(C,2);
    n[5] = cria_no_estrutra(V,2);
    n[6] = cria_no_estrutra(V,1);
    n[7] = cria_no_estrutra(V,1);
    n[8] = cria_no_estrutra(V,2);

    int i;
    for(i=0; i<9; i++)
        conecta_UM(n[i],N,ELSE);


    SAI("\n------------------------------------------------------------------------");
    SAI("\nInicio\n");
    mostra_no(N,EXTENDIDO);

    for(i=0; i<9; i++)
    {
        SAI("\n------------------------------------------------------------------------");
        SAI("\n\nNO %d", i);
        mostra_no(n[i],EXTENDIDO);

        desconecta_UM(n[i], N);

        SAI("\nDepois da desconexao\n");
        mostra_no(n[i],EXTENDIDO);
        mostra_no(N,EXTENDIDO);
    }

    SAI("\n------------------------------------------------------------------------");
    SAI("\nFim");
    mostra_no(N,EXTENDIDO);

    for(i=0; i<9; i++)
        libera_no(n[i]);
    libera_no(N);
    SAI("\nFIM TESTE CONEXAO");

    if(!memoria_zerada()) exit_program("VAZAMENTO DE MEMORIA DESCONEXAO");
}

void teste_consistencia(lista_head *lh)
{
    DEBUG(DEBUG_CONSISTENCIA,"\nTestando consistencia");
    lista_body *lb;
    for(                 ; lh     != NULL; lh = lh->lh)
    {
        COND_DEBUG(DEBUG_CONSISTENCIA)
        {
            SAI("\nNovo lh\tLABEL: ");mostra_label(NLABEL(lh),0);
        }
        for(lb = BODY(lh)->lb; lb != NULL; lb = lb->lb)
        {
            COND_DEBUG(DEBUG_CONSISTENCIA)
            {
                SAI("\n\tNovo lb\tLABEL: ");mostra_label(NLABEL(lb),0);
            }
            if(COMPARE_LABEL(NLABEL(lh),!=,NLABEL(lb)))
            {
                mostra_lista_body(lh,EXTENDIDO);
                exit_program("CONSISTENCIA ERRADA");
            }
        }
    }
    DEBUG(DEBUG_CONSISTENCIA,"\nFinalizou consistencia");
}

void teste_transfere()
{
    SAI("\n\n\n\n\nINICIO TESTE TRANFERE");
    no *N1, *N2;
    N1 = cria_no_amplitude(1,0);
    N2 = cria_no_amplitude(2,0);

    no *n1[5];
    n1[0] = cria_no_estrutra(C,1);
    n1[1] = cria_no_estrutra(R,1);
    n1[2] = cria_no_estrutra(C,2);
    n1[3] = cria_no_estrutra(C,2);
    n1[4] = cria_no_estrutra(V,2);

    no *n2[7];
    n2[0] = cria_no_estrutra(C,1);
    n2[1] = cria_no_estrutra(C,1);
    n2[2] = cria_no_estrutra(V,1);
    n2[3] = cria_no_estrutra(R,1);
    n2[4] = cria_no_estrutra(C,2);
    n2[5] = cria_no_estrutra(C,2);
    n2[6] = cria_no_estrutra(R,2);

    /*** Teste 1 ***/
    SAI("\n\nTESTE 1 ");
    int i;
    for(i=0; i<5; i++)
        conecta_UM(n1[i],N1,ELSE);
    for(i=0; i<7; i++)
        conecta_UM(n2[i],N2,THEN);
    mostra_no(N1,EXTENDIDO);
    mostra_no(N2,EXTENDIDO);

    transfere_conexoes(N1,N2);
    SAI("\n\n\tDEPOIS");
    mostra_no(N1,EXTENDIDO);
    mostra_lista_head(N1,COMPLETO);
    teste_consistencia(N1);

    /*** Teste 2 ***/
    SAI("\n\n\n\n\nTESTE 2");
    N2 = cria_no_amplitude(2,0);

    while(BODY(N1)->n != NULL)
        desconecta_UM(BODY(N1)->n,N1);

    conecta_DOIS(n1[2],N1,N1);
    conecta_DOIS(n2[4],N2,N2);
    mostra_no(N1,EXTENDIDO);
    mostra_no(N2,EXTENDIDO);

    transfere_conexoes(N1,N2);
    SAI("\n\n\tDEPOIS");
    mostra_no(N1,EXTENDIDO);
    mostra_lista_head(N1,COMPLETO);
    teste_consistencia(N1);

    /*** Teste 3 ***/
    SAI("\n\n\n\n\nTESTE 3");
    N2 = cria_no_amplitude(2,0);

    while(BODY(N1)->n != NULL)
        desconecta_UM(BODY(N1)->n,N1);

    conecta_UM(n1[1],N1,ELSE);
    conecta_UM(n2[0],N2,THEN);
    mostra_no(N1,EXTENDIDO);
    mostra_no(N2,EXTENDIDO);

    transfere_conexoes(N1,N2);
    SAI("\n\n\tDEPOIS\n");
    mostra_no(N1,EXTENDIDO);
    mostra_lista_head(N1,COMPLETO);
    teste_consistencia(N1);

    while(BODY(N1)->n != NULL)
        desconecta_UM(BODY(N1)->n,N1);
    libera_no_amplitude(N1);
    for(i=0; i<5; i++)
        libera_no_estrutura(n1[i]);
    for(i=0; i<7; i++)
        libera_no_estrutura(n2[i]);

    mostra_quantidades(I);
    SAI("\nFIM TESTE TRANFERE");

    if(!memoria_zerada()) exit_program("VAZAMENTO DE MEMORIA TRANSFERE");
}

void teste_busca_amplitude()
{
    no_amplitude *Nl[5];
    Nl[0] = cria_no_amplitude(-2, 0);
    Nl[1] = cria_no_amplitude( 0,-2);
    Nl[2] = cria_no_amplitude( 0, 0);
    Nl[3] = cria_no_amplitude( 0, 2);
    Nl[4] = cria_no_amplitude( 2, 0);

    no_amplitude *Nb[13];
    Nb[ 0] = cria_no_amplitude(-3, 0);
    Nb[ 1] = cria_no_amplitude(-2, 0);
    Nb[ 2] = cria_no_amplitude(-1, 0);
    Nb[ 3] = cria_no_amplitude( 0,-3);
    Nb[ 4] = cria_no_amplitude( 0,-2);
    Nb[ 5] = cria_no_amplitude( 0,-1);
    Nb[ 6] = cria_no_amplitude( 0, 0);
    Nb[ 7] = cria_no_amplitude( 0, 1);
    Nb[ 8] = cria_no_amplitude( 0, 2);
    Nb[ 9] = cria_no_amplitude( 0, 3);
    Nb[10] = cria_no_amplitude( 1, 0);
    Nb[11] = cria_no_amplitude( 2, 0);
    Nb[12] = cria_no_amplitude( 3, 0);

    lista_body *lb;
    int i;
    for(i=4, lb = NULL; i>=0; i--)
        lb = cria_lista_body(Nl[i],lb);
    lb = cria_lista_body(NULL,lb);

    lista_body *lb_aux;
    SAI("\nLb: %p",lb);
    for(lb_aux = lb->lb; lb_aux != NULL; lb_aux = lb_aux->lb)
    {
        SAI("\nLb: %p\t",lb_aux);mostra_amplitude(AMP(lb_aux->n));
    }

    PULA;
    lista_body *lb_aux_2;
    for(i=0; i<13; i++)
    {
        int res = 0, index;
        lb_aux = busca_amplitude(lb, AMP(Nb[i]), &res, NULL);
        lb_aux_2 = lb;
        for(index = 0; index < 6; index++)
        {
            if(lb_aux_2 == lb_aux)
                break;
            lb_aux_2 = lb_aux_2->lb;
        }

        SAI("\nTESTE 1 - %2d\tAchado: %p\t%d\tindex: %d",i,lb_aux,res,index);
    }

    PULA;
    lista_body *lb_aux_3;
    for(i=0, lb_aux_3 = lb; lb_aux_3->lb != NULL; i++, lb_aux_3 = lb_aux_3->lb)
    {
        int res = 0, index;
        lb_aux = busca_amplitude(lb, AMP(Nb[6]), &res, lb_aux_3);
        lb_aux_2 = lb;
        for(index = 0; index < 6; index++)
        {
            if(lb_aux_2 == lb_aux)
                break;
            lb_aux_2 = lb_aux_2->lb;
        }

        SAI("\nTESTE 2 - %2d\tAchado: %p\t%d\tindex: %d",i,lb_aux,res,index);
    }



    for(int i=0; i<5; i++)
        libera_no(Nl[i]);

    libera_lista_body_lista(lb);

    for(int i=0; i<13; i++)
        libera_no(Nb[i]);

    if(!memoria_zerada()) exit_program("VAZAMENTO DE MEMORIA BUSCA ITEM");
}

void teste_reducao_lista()
{
    SAI("\n\n\n\n\nINICIO TESTE REDUCAO LISTA");
    Long N, tot;
    numero amp;
    for(N = 1; N < 26; N++)
    {
        set_Qbit(N);
        tot = pow(  2,    N);
        amp = pow(tot, -0.5);
        //amp = 1;

        SAI("\n");
        SAI("\n");
        SAI("\nN   : %d",N);
        SAI("\ntot : %d",tot);
        SAI("\namp : %.3e",amp);

        lista_body *lb, *lb_aux;
        no *n;
        lb = cria_lista_body(NULL,NULL);

        Long i;
        numero theta, theta_0;
        theta_0 = 2*M_PI / tot;
        lb_aux = lb;
        SAI("\ntheta0 : %.4e",theta_0);
        SAI("\nthetaT : %.4e",theta_0*tot);
        SAI("\n");
        for(i=0; i < tot; i++)
        {
            theta = i * theta_0;
            n = cria_no_amplitude(amp*cos(theta),amp*sin(theta));

            lb_aux->lb = cria_lista_body(n,NULL);
            lb_aux = lb_aux->lb;
        }

        Long quant;
        quant = conta_itens_lista_body(lb->lb);
        SAI("\n");
        SAI("\nQuantidade antes  : %llu",quant);

        lb_aux = reduz_lista_amplitude(lb);

        if(lb_aux != NULL)
            quant = conta_itens_lista_body(lb->lb);

        SAI("\nQuantidade depois : %llu",quant);
        mostra_quantidades(I);

        libera_lista_body_lista(lb_aux);
        for(lb_aux = lb->lb; lb_aux != NULL; lb_aux = lb_aux->lb)
            libera_no_amplitude(lb_aux->n);
        libera_lista_body_lista(lb);

        mostra_quantidades(I);
        if(!memoria_zerada()) exit_program("VAZAMENTO DE MEMORIA REDUCAO LISTA");
    }
    SAI("\nFIM TESTE REDUCAO LISTA");

}

void teste_reducao_QDD(int MAX)
{
    SAI("\n\n\n\n\nINICIO TESTE REDUCAO QDD\n");
    int N;
    QDD Q0 = um();
    for(N = 1; N<=MAX; N++)
    {
        set_Qbit(N);
        SAI("\nN: %2d",N);

        QDD Q, Q1;
        DEBUG(DEBUG_REDUZ_QDD,"\nGerando H");
        Q1 = H();
        DEBUG(DEBUG_REDUZ_QDD,"\nProduto tensorial");
        Q0 = produto_tensorial(Q0,Q1);
        DEBUG(DEBUG_REDUZ_QDD,"\nCopiando");
        Q  = copia_QDD(Q0);
        time_t antes, depois;
        antes = clock();
        DEBUG(DEBUG_REDUZ_QDD,"\nReduzindo");
        reduz_QDD(&Q);
        depois = clock();
        DEBUG(DEBUG_REDUZ_QDD,"\n");
        SAI("\ttempo: %7.3f",difftime(depois,antes)/CLOCKS_PER_SEC);
        COND_DEBUG(DEBUG_REDUZ_QDD) SAI("\nQDD DEPOIS DA REDUCAO");
        COND_DEBUG(DEBUG_REDUZ_QDD) mostra_QDD(Q,EXTENDIDO);
        COND_DEBUG(DEBUG_REDUZ_QDD) mostra_QDD(Q,SIMPLES);
        DEBUG(DEBUG_REDUZ_QDD,"\nLiberando");
        libera_QDD(Q);
        DEBUG(DEBUG_REDUZ_QDD,"\nLIBEROU");
    }

    if(!memoria_zerada()) exit_program("VAZAMENTO DE MEMORIA REDUCAO QDD");

    SAI("\nFIM TESTE REDUCAO QDD");
}

void teste_todos()
{
    time_t antes, depois;
    antes = clock();

    teste_conexao();
    teste_desconexao();
    teste_transfere();
    teste_busca_amplitude();
    teste_reducao_lista();

    depois = clock();
    depois = difftime(depois,antes);
    SAI("\n\n\nTesmpo: %d", depois);
}



void analise_structs()
{
    lista_body lb;
    SAI("\n");
    SAI("\n");
    SAI("\n%d",sizeof(lista_body));
    SAI("\n");
    SAI("\nlb       : %2d",SUBTRACT_POINTER(&(lb),&(lb)));
    SAI("\nlb.n     : %2d",SUBTRACT_POINTER(&(lb.n),&(lb)));
    SAI("\nlb.lb    : %2d",SUBTRACT_POINTER(&(lb.lb),&(lb)));

    lista_head lh;
    SAI("\n");
    SAI("\n");
    SAI("\n%d",sizeof(lista_head));
    SAI("\n");
    SAI("\nlh       : %2d",SUBTRACT_POINTER(&(lh),&(lh)));
    SAI("\nlh.lb    : %2d",SUBTRACT_POINTER(&(lh.lb),&(lh)));
    SAI("\nlh.lh    : %2d",SUBTRACT_POINTER(&(lh.lh),&(lh)));

    no n;
    SAI("\n");
    SAI("\n");
    SAI("\n%d", sizeof(no));
    SAI("\n");
    SAI("\nn        : %2d",SUBTRACT_POINTER(&(n),&(n)));
    SAI("\nn.lh     : %2d",SUBTRACT_POINTER(&(n.lh),&(n)));
    SAI("\nn.lab    : %2d",SUBTRACT_POINTER(&(n.lab),&(n)));
    SAI("\nn.lab.cl : %2d",SUBTRACT_POINTER(&(n.lab.cl),&(n)));
    SAI("\nn.lab.ni : %2d",SUBTRACT_POINTER(&(n.lab.ni),&(n)));

    no_estrutura ne;
    SAI("\n");
    SAI("\n");
    SAI("\n%d",sizeof(no_estrutura));
    SAI("\n");
    SAI("\nne       : %2d",SUBTRACT_POINTER(&(ne),&(ne)));
    SAI("\nne.n     : %2d",SUBTRACT_POINTER(&(ne.n),&(ne)));
    SAI("\nne.e     : %2d",SUBTRACT_POINTER(&(ne.e),&(ne)));
    SAI("\nne.e.el  : %2d",SUBTRACT_POINTER(&(ne.e.el),&(ne)));
    SAI("\nne.e.th  : %2d",SUBTRACT_POINTER(&(ne.e.th),&(ne)));

    no_amplitude na;
    SAI("\n");
    SAI("\n");
    SAI("\n%d",sizeof(no_amplitude));
    SAI("\n");
    SAI("\nna       : %2d",SUBTRACT_POINTER(&(na),&(na)));
    SAI("\nna.n     : %2d",SUBTRACT_POINTER(&(na.n),&(na)));
    SAI("\nna.a     : %2d",SUBTRACT_POINTER(&(na.a),&(na)));
    SAI("\nna.a.re  : %2d",SUBTRACT_POINTER(&(na.a.re),&(na)));
    SAI("\nna.a.th  : %2d",SUBTRACT_POINTER(&(na.a.im),&(na)));

    QDD Q;
    SAI("\n");
    SAI("\n");
    SAI("\n%d",sizeof(QDD));
    SAI("\n");
    SAI("\nQ        : %2d",SUBTRACT_POINTER(&(Q),&(Q)));
    SAI("\nQ.n      : %2d",SUBTRACT_POINTER(&(Q.n),&(Q)));
    SAI("\nQ.lb     : %2d",SUBTRACT_POINTER(&(Q.lb),&(Q)));
    SAI("\nQ.N      : %2d",SUBTRACT_POINTER(&(Q.N),&(Q)));

    SAI("\n");
    SAI("\n");
}

void mostra_mostras()
{
    QDD Q;
    Q = produto_tensorial(produto_tensorial(H(),H()),produto_tensorial(H(),H()));
    for(int i = SIMPLES; i <= EXTENDIDO; i++)
        mostra_QDD(Q,i);
    libera_QDD(Q);
}


int main()
{
    abre_saidas();
    inicia_estruturas();
    set_Qbit(20);
    /******************************/

    //teste_todos();

    teste_reducao_QDD(10);


    /******************************/
    finaliza_estruturas();
    PULA;PULA;PULA;PULA;PULA;PULA;
    SAI("\nFINAL EXECUXCAO");
    mostra_quantidades(I);
    SAI("\nDeu certo\n");
}