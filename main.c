#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <sys/time.h>

#define R 2
#define V 1
#define C 0

#define ELSE 0
#define THEN 1



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
    double re, im;
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



#define BODY(PONTEIRO)      ((lista_body*)PONTEIRO)
#define HEAD(PONTEIRO)      ((lista_head*)PONTEIRO)
#define NO(PONTEIRO)        ((no*)PONTEIRO)
#define LABEL(PONTEIRO)     ((label*)(HEAD(PONTEIRO)+1))
#define NLABEL(PONTEIRO)    (LABEL(BODY(PONTEIRO)->n))
#define NEST(PONTEIRO)      ((no_estrutura*)PONTEIRO)
#define NAMP(PONTEIRO)      ((no_amplitude*)PONTEIRO)
#define EST(PONTEIRO)       ((estrutura*)(NO(PONTEIRO)+1))
#define VEST(PONTEIRO)      ((no**)EST(PONTEIRO))
#define VAPPLY(PONTEIRO)    ((apply**)(PONTEIRO))
#define AMP(PONTEIRO)       ((amplitude*)(NO(PONTEIRO)+1))

#define LADO(NO, NO1)               (VEST(NO)[0] != NO1)
#define ACCESS(MATRIX, PONTEIRO)    MATRIX[LABEL(PONTEIRO)->ni][LABEL(PONTEIRO)->cl]

#define COMPARE_LABEL(LABEL_1, OPERANDO, LABEL_2)       (*((long*)LABEL_1) OPERANDO *((long*)LABEL_2))
#define SUBTRACT_POINTER(POINTER_1, POINTER_2)          (((void*)POINTER_1) - ((void*)POINTER_2))
#define COPY_STRUCT(PONTEIRO_1, PONTEIRO_2, ESTRUTURA)  (memcpy(PONTEIRO_1,PONTEIRO_2,sizeof(ESTRUTURA)))


double eps;
int iNE, iNA, iLB, iLH, iA;
lista_body *lb_zero, *LB[2][2];



void exit_program(char *s)
{
    printf("\n\n\nERRO");
    if(s != NULL)
        printf("\t%s",s);
    fflush(stdout);
    exit(123456);
}

void set_Qbit(int N)
{
    eps = pow(2,-0.5*N)/300;
}



no_estrutura* cria_no_estrutra(int classe, int nivel)
{
    no_estrutura *ne;
    ne = malloc(sizeof(no_estrutura));
    if(ne == NULL)
        exit_program("CRIA NO ESTRUTURA");
    iNE++;

    BODY(ne)->n   = NULL;
    BODY(ne)->lb  = NULL;
    HEAD(ne)->lh  = NULL;
    LABEL(ne)->ni = nivel;
    LABEL(ne)->cl = classe;
    EST(ne)->el   = NULL;
    EST(ne)->th   = NULL;

    return ne;
}

no_amplitude* cria_no_amplitude(double re, double im)
{
    no_amplitude *na;
    na = malloc(sizeof(no_amplitude));
    if(na == NULL)
        exit_program("CRIA NO AMPLITUDE");
    iNA++;

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
    iNE++;

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
    iNA++;

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
    iLB++;

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
    iLB++;

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
    iLB++;

    return lb;
}

lista_body* cria_lista_body_copia(lista_body *lb_0)
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program("CRIA LISTA BODY COPIA");
    iLB++;

    COPY_STRUCT(lb,lb_0,lista_body);

    return lb;
}



lista_head* cria_lista_head(no *n, lista_head *lh_next)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD");
    iLH++;

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
    iLH++;
    return lh;
}

lista_head* cria_lista_head_pendurado()
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD PENDURADO");
    iLH++;
    return lh;
}

lista_head* cria_lista_head_copia(lista_head *lh_0)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD COPIA");
    COPY_STRUCT(lh,lh_0,lista_head);
    iLH++;
    return lh;
}

lista_head* cria_lista_head_body(lista_body *lb)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program("CRIA LISTA HEAD BODY");
    iLH++;
    COPY_STRUCT(lh,lb,lista_body);
    lh->lh = NULL;
    return lh;
}



apply* cria_apply(no *n1, no *n2)
{
    apply *a;
    a = malloc(sizeof(apply));
    if(a == NULL)
        exit_program("CRIA APPLY");
    iA++;

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
    a = calloc(sizeof(apply),1);
    if(a == NULL)
        exit_program("CRIA APPLY VAZIO");

    iA++;
    return a;
}



void libera_lista_body_item(lista_body *lb)
{
    iLB--;
    free(lb);
}

void libera_lista_body_lista(lista_body *lb)
{
    lista_body *lb_aux;
    while(lb != NULL)
    {
        lb_aux = lb->lb;
        libera_lista_body_item(lb);
        lb = lb_aux;
    }
}

void libera_lista_head_item(lista_head *lh)
{
    iLH--;
    free(lh);
}

void libera_lista_head_estrutura(lista_head *lh)
{
    while(lh != NULL)
    {
        lista_head *lh_aux;
        lh_aux = lh;
        lh     = lh->lh;


        libera_lista_body_lista(BODY(lh_aux)->lb);
        libera_lista_head_item(lh_aux);
    }
}



void libera_no_estrutura(no *n)
{
    iNE--;
    free(n);
}

void libera_no_amplitude(no *n)
{
    iNA--;
    free(n);
}

void libera_no(no *n)
{
    if(LABEL(n)->ni == 0)
        iNA--;
    else
        iNE--;
    free(n);
}



void libera_apply_item(apply *a)
{
    free(a);
    iA--;
}

void libera_apply_lista(apply *a)
{
    apply *a_aux;
    while(a != NULL)
    {
        a_aux = a->a;
        libera_apply_item(a);
        a = a_aux;
    }
}



void inicia_estruturas()
{
    lb_zero = cria_lista_body_vazio();

    LB[0][0] = cria_lista_body_vazio();
    LB[0][1] = cria_lista_body_vazio();
    LB[1][0] = cria_lista_body_vazio();
    LB[1][1] = cria_lista_body_vazio();
}

void finaliza_estruturas()
{
    libera_lista_body_item(lb_zero);

    libera_lista_body_item(LB[0][0]);
    libera_lista_body_item(LB[0][1]);
    libera_lista_body_item(LB[1][0]);
    libera_lista_body_item(LB[1][1]);
}



void mostra_ponteiro(void *pointer)
{
    if (pointer == NULL)  printf("NULL");
    else                  printf("%011p", pointer);
}

void mostra_cabecalho(char *s, void *p)
{
    printf("\nEndereco (%s): ",s);mostra_ponteiro(p);
}

void mostra_label(label *lab)
{
    if(lab->ni == 0)
    {
        printf("AMPLITUDE");
        return;
    }

    switch(lab->cl)
    {
        case C:
        printf("C");
        break;

        case V:
        printf("V");
        break;

        case R:
        printf("R");
        break;
    }
    printf("%d",lab->ni);
}



void mostra_lista_body_item(lista_body *lb)
{
    mostra_cabecalho("LISTA BODY",lb);
    if(lb == NULL)
        return;

    printf("\nNo: ");mostra_ponteiro(lb->n);
    printf("\nlb: ");mostra_ponteiro(lb->lb);
    printf("\n");
}

void mostra_lista_body_ponteiros(lista_body *lb)
{
    int i;
    for(i=0; lb != NULL; i++, lb = lb->lb)
    {
        printf("\n\tLista %3d : ",i);mostra_ponteiro(lb);
    }
}

void mostra_lista_body_lista(lista_body *lb)
{
    lista_body *lb_aux;
    int i;
    for(i=0, lb_aux = lb; lb_aux != NULL; i++, lb_aux = lb_aux->lb)
    {
        printf("\n\tNo %3d: ",i);mostra_ponteiro(lb_aux->n);
    }
}



void mostra_estrutura(estrutura *est)
{
    ;mostra_ponteiro(est->el);printf("\t\t");mostra_ponteiro(est->th);
}

void mostra_amplitude(amplitude *amp)
{
    if(amp == NULL)
        return;

    printf("% .4e",amp->re);
    if(amp->im <  eps)
        if(amp->im > -eps)
            return;
    printf(" % .4e",amp->im);
}

void mostra_dados(no *n)
{
    if(LABEL(n)->ni == 0)
        mostra_amplitude(AMP(n));
    else
        mostra_estrutura(EST(n));
}



int conta_itens_lista_body(lista_body *lb)
{
    int i;
    for(i=0; lb != NULL; i++, lb = lb->lb);
    return i;
}

void mostra_lista_body_amplitudes(lista_body *lb)
{
    int i;
    for(i=0; lb != NULL; i++, lb = lb->lb)
    {
        printf("\n\tNo %2d: ",i);
        mostra_amplitude(AMP(lb->n));
    }
}

void mostra_lista_body_estrutura_compacto(lista_body *lb)
{
    int i;
    printf("\nLABEL: ");mostra_label(NLABEL(lb));
    for(i=0; lb != NULL; i++, lb = lb->lb)
    {
        printf("\n\tNo %3d: ",i);mostra_ponteiro(lb->n);
    }
}

void mostra_lista_body_estrutura_compacto_dados(lista_body *lb)
{
    int i;
    printf("\nLABEL: ");mostra_label(NLABEL(lb));
    for(i=0; lb != NULL; i++, lb = lb->lb)
    {
        printf("\n\tNo %3d: ",i);mostra_ponteiro(lb->n);printf("\t\t\t\t");mostra_dados(lb->n);
    }
}



void mostra_lista_head_item(lista_head *lh)
{
    mostra_cabecalho("LISTA HEAD",lh);
    if(lh == NULL)
        return;

    printf("\nNo: ");mostra_ponteiro(BODY(lh)->n);
    printf("\nlb: ");mostra_ponteiro(BODY(lh)->lb);
    printf("\nlh: ");mostra_ponteiro(lh->lh);

}

void mostra_lista_head_lista(lista_head *lh)
{
    while(lh != NULL)
    {
        printf("\n");
        mostra_lista_head_item(lh);
        lh = lh->lh;
    }
}

void mostra_lista_head_estrutura_simples(lista_head *lh)
{
    for(; lh->lh != NULL; lh = lh->lh)
    {
        printf("\nLabel: ");mostra_label(NLABEL(lh));printf("\ttot: %d",conta_itens_lista_body(BODY(lh)));
        printf("\n---------------------");
    }
    printf("\nAMPLITUDES");mostra_lista_body_amplitudes(BODY(lh));
}

void mostra_lista_head_estrutura_compacto(lista_head *lh)
{
    for(; lh != NULL; lh = lh->lh)
    {
        lista_body *lb;
        mostra_lista_body_estrutura_compacto(BODY(lh));
        printf("\n---------------------");
    }
}

void mostra_lista_head_estrutura_compacto_dados(lista_head *lh)
{
    for(; lh != NULL; lh = lh->lh)
    {
        mostra_lista_body_estrutura_compacto_dados(BODY(lh));
        printf("\n---------------------------------------------------------------");
    }
}



void mostra_no_estrutura(no_estrutura *ne)
{
    mostra_cabecalho("NO ESTRUTURA",ne);
    if(ne == NULL)
        return;

    if(BODY(ne)->n == NULL)
    {
        printf("\nSem antecessores");
    }
    else
    {
        printf("\nAntecessores: ");
        mostra_lista_head_estrutura_compacto(HEAD(ne));
    }

    printf("\nLabel: ");mostra_label(LABEL(ne));
    printf("\nSucessores: el: ");mostra_ponteiro(EST(ne)->el);printf("\tth: ");mostra_ponteiro(EST(ne)->th);
    printf("\n");
}

void mostra_no_estrutura_compacto(no_estrutura *ne)
{
    mostra_cabecalho("NO ESTRUTURA",ne);
    if(ne == NULL)
        return;

    printf("\nSucessores: el: ");mostra_estrutura(EST(ne));
    printf("\n");
}



void mostra_no_amplitude(no_amplitude *na)
{
    mostra_cabecalho("NO AMPLITUDE",na);
    if(na == NULL)
        return;

    if(BODY(na)->n == NULL)
    {
        printf("\nSem antecessores");
    }
    else
    {
        printf("\nAntecessores: ");
        mostra_lista_head_estrutura_compacto(HEAD(na));
    }

    printf("\nAmplitude: ");mostra_amplitude(AMP(na));
    printf("\n");
}

void mostra_no_amplitude_compacto(no_amplitude *na)
{
    mostra_cabecalho("NO AMPLITUDE",na);
    if(na == NULL)
        return;

    printf("\nAmplitude: ");mostra_amplitude(AMP(na));
    printf("\n");
}



void mostra_no_base(no *n)
{
    mostra_cabecalho("NO",n);
    if(n == NULL)
        return;

    printf("\nLabel: ");mostra_label(LABEL(n));
}

void mostra_no_compacto(no *n)
{
    if(LABEL(n)->ni == 0)
        mostra_no_amplitude_compacto(n);
    else
        mostra_no_estrutura_compacto(n);
}

void mostra_no(no *n)
{
    if(LABEL(n)->ni == 0)
        mostra_no_amplitude(NAMP(n));
    else
        mostra_no_estrutura(NEST(n));
}



void mostra_lista_body_estrutura_completa(lista_body *lb)
{
    for(; lb->lb != NULL; lb = lb->lb)
    {
        mostra_no(lb->n);
        printf("\n------------------------------------------");
    }
    mostra_no(lb->n);
}

void mostra_lista_head_estrutura_completo(lista_head *lh)
{
    for(; lh != NULL; lh = lh->lh)
    {
        lista_body *lb;
        mostra_lista_body_estrutura_completa(BODY(lh));
        printf("\n---------------------------------------------------------------");
    }
}



void mostra_apply(apply *a)
{
    mostra_cabecalho("APPLY",a);
    if(a == NULL)
        return;

    printf("\nNos: ");
    printf("\n\tn1: ");mostra_ponteiro(a->n1);
    printf("\n\tn2: ");mostra_ponteiro(a->n2);
    printf("\n\tn : ");mostra_ponteiro(a->n);
    printf("\nApplys: ");
    printf("\n\ta1: ");mostra_ponteiro(a->a1);
    printf("\n\ta2: ");mostra_ponteiro(a->a2);
    printf("\n\ta : ");mostra_ponteiro(a->a);
    printf("\n");
}



void mostra_quantidades()
{
    printf("\niLB: %d",iLB);
    printf("\niLH: %d",iLH);
    printf("\niNE: %d",iNE);
    printf("\niNA: %d",iNA);
    printf("\niA : %d",iA);
    printf("\n");
}



lista_head* enlista_arvore(no *n)
{
/*
printf("\nDentro enlistando");
fflush(stdout);
*/
    int N, i, j;
    N = 1 + LABEL(n)->ni;
    lista_head *LH[N][3];
    for(i=0; i<N; i++)
    for(j=0; j<3; j++)
        LH[i][j] = NULL;
/*
printf("\nzerado");
fflush(stdout);
*/
    lista_head *lh_0;
    lh_0 = cria_lista_head(n,NULL);
    ACCESS(LH,n) = lh_0;

    lista_head *lh, *lh_1;
    lista_body *lb, *lb_1;
    int k;
    lh = lh_0;
    for(i=N-1; i> 0; i--)
    for(j=2  ; j>=0; j--)
    {
        if(LH[i][j] == NULL)
            continue;
/*
printf("\nNova cordenada: %2d %2d",i,j);
fflush(stdout);
*/
        lh->lh = LH[i][j];
        lh     = lh->lh;

        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            no **N;
            N = VEST(lb->n);
            for(k=0; k<2; k++)
            {
                n = N[k];
                lh_1 = ACCESS(LH,n);

                if(BODY(n)->n != lb->n)
                    continue;

                if(lh_1 == NULL)
                {
                    ACCESS(LH,n) = cria_lista_head(n,NULL);
                    continue;
                }
                BODY(lh_1)->lb = cria_lista_body(n,BODY(lh_1)->lb);
            }
        }
    }

    lh->lh     = LH[0][0];
    lh->lh->lh = NULL;

    return lh_0;
}



void mostra_arvore_base(no *n, void(*mostra_lista_head_estrutura)(no*))
{
    lista_head *lh;
    lh = enlista_arvore(n);
    mostra_lista_head_estrutura(lh);
    libera_lista_head_estrutura(lh);
}

void mostra_arvore_simples(no *n)
{
    mostra_arvore_base(n, mostra_lista_head_estrutura_simples);
}

void mostra_arvore_compacto(no *n)
{
    mostra_arvore_base(n,mostra_lista_head_estrutura_compacto_dados);
}

void mostra_arvore_completo(no *n)
{
    mostra_arvore_base(n, mostra_lista_head_estrutura_completo);
}



void mostra_QDD_base(QDD Q, void(*mostra_arvore)(no*))
{
    printf("\nQDD");
    printf("\nN: %d",Q.N);
    printf("\n");
    mostra_arvore(Q.n);
    printf("\n");
}

void mostra_QDD_simples(QDD Q)
{
    mostra_QDD_base(Q,mostra_arvore_simples);
}

void mostra_QDD_compacto(QDD Q)
{
    mostra_QDD_base(Q,mostra_arvore_compacto);
}

void mostra_QDD_completo(QDD Q)
{
    mostra_QDD_base(Q,mostra_arvore_completo);
}



void inclui_no(lista_head *lh, no *n)
{
    if(BODY(lh)->n == NULL)
    {
        BODY(lh)->n = n;
        return;
    }

    label *lab;
    lab = LABEL(n);

    if(COMPARE_LABEL(lab, ==,NLABEL(lh)))
    {
        BODY(lh)->lb = cria_lista_body(n,BODY(lh)->lb);
        return;
    }

    if(COMPARE_LABEL(lab, <, NLABEL(lh)))
    {
        lista_head *lh_aux;
        lh_aux = cria_lista_head_copia(lh);

        BODY(lh)->n  = n;
        BODY(lh)->lb = NULL;
        HEAD(lh)->lh = lh_aux;
        return;
    }

    lista_head *lh_aux;
    for(lh_aux = lh->lh; lh_aux != NULL; lh = lh_aux, lh_aux = lh->lh)
        if(COMPARE_LABEL(lab, <, NLABEL(lh_aux)))
            break;

    if(COMPARE_LABEL(lab,!=,NLABEL(lh)))
    {
        lh->lh = cria_lista_head(n,lh_aux);
        return;
    }

    BODY(lh)->lb = cria_lista_body(n,BODY(lh)->lb);
}

void exclui_no(lista_head *lh, no *n, lista_body *lb_pista)
{
    if(lb_pista == NULL)
    {
        if(n == BODY(lh)->n)
        {
            if(BODY(lh)->lb != NULL)
            {
                lista_body *lb;
                lb = BODY(lh)->lb;
                COPY_STRUCT(lh,lb,lista_body);
                libera_lista_body_item(lb);
                return;
            }

            if(lh->lh != NULL)
            {
                lista_head *lh_aux;
                lh_aux = lh->lh;
                COPY_STRUCT(lh,lh_aux,lista_head);
                libera_lista_head_item(lh_aux);
                return;
            }

            BODY(lh)->n = NULL;
            return;
        }

        label *lab;
        lab = LABEL(n);
        if(COMPARE_LABEL(lab, ==, NLABEL(lh)))
        {
            lista_body *lb, *lb_next;
            for(lb = BODY(lh), lb_next = lb->lb; n != lb_next->n; lb = lb_next, lb_next = lb->lb);
            lb->lb = lb_next->lb;
            libera_lista_body_item(lb_next);
            return;
        }

        lista_head *lh_next;
        for(lh_next = lh->lh; COMPARE_LABEL(lab, !=, NLABEL(lh_next)); lh = lh_next, lh_next = lh->lh);

        if(n == BODY(lh_next)->n)
        {
            if(BODY(lh_next)->lb != NULL)
            {
                lista_body *lb;
                lb = BODY(lh_next)->lb;
                COPY_STRUCT(lh_next,lb,lista_body);
                libera_lista_body_item(lb);
                return;
            }

            lh->lh = lh_next->lh;
            libera_lista_head_item(lh_next);
            return;
        }
        lb_pista = BODY(lh_next);
    }

    lista_body *lb, *lb_next;
    for(lb = lb_pista, lb_next = lb->lb; n != lb_next->n; lb = lb_next, lb_next = lb->lb);
    lb->lb = lb_next->lb;
    libera_lista_body_item(lb_next);
}



void conecta_UM(no *n1, no *n2, char lado)
{
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
    VEST(n1)[LADO(n1,n2)] = NULL;
    exclui_no(HEAD(n2),n1,NULL);
}

void desconecta_UM_pista(no *n1, no *n2, lista_head *lh_pista, lista_body *lb_pista)
{
    if(EST(n1)->el == n2)
        EST(n1)->el = NULL;
    else
        EST(n1)->th = NULL;

    if(lh_pista == NULL)
        lh_pista = HEAD(n2);
    exclui_no(lh_pista,n1,lb_pista);
}

void desconecta_DOIS(no *n)
{
    desconecta_UM(n,EST(n)->el);
    desconecta_UM(n,EST(n)->th);
}

void transfere_conexoes(no *n1, no *n2)
{
    if(n1 == NULL) exit_program("TRANSFERE CONEXOES | N1 E NULL");
    if(n2 == NULL) exit_program("TRANSFERE CONEXOES | N2 E NULL");
    if(n1 == n2) exit_program("TRANSFERE CONEXOES | N1 2 N2 SAO IGUAS");

    if(BODY(n2)->n == NULL)
    {
        libera_no(n2);
        return;
    }

    if(BODY(n1)->n == NULL)
    {
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

        libera_no(n2);
        return;
    }

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

    if(COMPARE_LABEL(NLABEL(n2), <, NLABEL(n1)))
    {
        lista_head lh;
        COPY_STRUCT(&lh, n1,lista_head);
        COPY_STRUCT( n1, n2,lista_head);
        COPY_STRUCT( n2,&lh,lista_head);
    }

    lista_head *lh, *lh_1, *lh_2;
    label *lab;
    lab = NLABEL(n2);
    for(lh = HEAD(n1), lh_1 = lh->lh; lh_1 != NULL; lh = lh_1, lh_1 = lh->lh)
        if(COMPARE_LABEL(lab, <, NLABEL(lh_1)))
            break;

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
    libera_no(n2);

    while(lh_1 != NULL & lh_2 != NULL)
    {
        if(COMPARE_LABEL(NLABEL(lh_1), <, NLABEL(lh_2)))
        {
            lh->lh = lh_1;

            lh   = lh->lh;
            lh_1 = lh_1->lh;

            continue;
        }
        if(COMPARE_LABEL(NLABEL(lh_1), ==, NLABEL(lh_2)))
        {
            lista_body *lb, *lb_next;
            lh->lh = lh_2;
            lh     = lh->lh;
            for(lb = BODY(lh), lb_next = lb->lb; lb_next != NULL; lb = lb_next, lb_next = lb->lb);
            lb->lb = cria_lista_body_copia(BODY(lh_1));

            lista_head *lh_aux;
            lh_aux = lh_1;

            lh_1 = lh_1->lh;
            lh_2 = lh_2->lh;
            libera_lista_head_item(lh_aux);

            continue;
        }
        if(COMPARE_LABEL(NLABEL(lh_1), >, NLABEL(lh_2)))
        {
            lh->lh = lh_2;

            lh   = lh->lh;
            lh_2 = lh_2->lh;

            continue;
        }
    }

    if(lh_1 != NULL)
        lh->lh = lh_1;
    else if(lh_2 != NULL)
        lh->lh = lh_2;
}



void libera_arvore(no *n)
{
    if(BODY(n)->n != NULL)
        return;

    if(LABEL(n)->ni > 0)
    {

        no *N[2];
        COPY_STRUCT(N,EST(n),estrutura);

        desconecta_DOIS(n);

        libera_arvore(N[0]);
        libera_arvore(N[1]);
    }
    libera_no(n);
}

void libera_QDD(QDD Q)
{
    libera_arvore(Q.n);
    libera_lista_body_lista(Q.lb);
}



int compara_amplitude(amplitude *amp_1, amplitude *amp_2)
{
    double re;
    re = amp_1->re - amp_2->re;
    if(re > -eps)
    if(re <  eps)
    {
        double im;
        im = amp_1->im - amp_2->im;
        if(im > -eps)
        if(im <  eps)
            return 1;
    }
    return 0;
}

int compara_amplitude_zero(amplitude *amp)
{
    double re;
    re = amp->re;
    if(re > -eps)
    if(re <  eps)
    {
        double im;
        im = amp->im;
        if(im > -eps)
        if(im <  eps)
            return 1;
    }
    return 0;
}

void multiplica_amplitudes(amplitude *amp1, amplitude *amp2)
{
    amplitude amp;
    amp.re = amp1->re * amp2->re - amp1->im * amp2->im;
    amp.im = amp1->re * amp2->im + amp1->im * amp2->re;
    COPY_STRUCT(amp1,&amp,amplitude);
}

void multiplica_QDD_amplitude(QDD Q, amplitude *amp)
{
    lista_body *lb;
    for(lb = Q.lb; lb != NULL; lb = lb->lb)
        multiplica_amplitudes(AMP(lb->n),amp);
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

lista_body* copia_lista_body_head(lista_body *lb, lista_head *lh_next)
{
    lista_head *lh;
    lh = cria_lista_head_body(lb);
    BODY(lh)->lb = copia_lista_body(lb->lb);
    HEAD(lh)->lh = lh_next;

    return lh;
}

lista_body* reduz_lista_amplitude(lista_body *lb)
{
    if(lb->lb == NULL)
        return NULL;

    lista_body **LB_c;
    LB_c = LB[0];
    LB_c[0]->lb = NULL;
    LB_c[1]->lb = NULL;
/*
Long i, tam, tot;
printf("\nReduzindo lista");
i   = 0;
tam = 1024*1024;
tot = 256*tam;
*/
    COPY_STRUCT(lb_zero,lb,lista_body);
    while(lb_zero != NULL)
    {
/*
i++;
if(i%tam == 0)
{
printf("\nj: %3llu/%llu",i/tam,tot/tam);
fflush(stdout);
}
*/
        lista_body *lb_c;
        lb_c    = lb_zero;
        lb_zero = lb_zero->lb;

        double re1, re2;
        re1 = AMP(lb_c->n)->re - eps;
        re2 = AMP(lb_c->n)->re + eps;

        lista_body *lb_2;
        for(lb_2 = LB_c[1]; lb_2->lb != NULL; lb_2 = lb_2->lb)
            if(AMP(lb_2->lb->n)->re > re1)
                break;

        for(              ; lb_2->lb != NULL; lb_2 = lb_2->lb)
        {
            if(AMP(lb_2->lb->n)->re < re2)
            {
                double im;
                im = AMP(lb_2->lb->n)->im - AMP(lb_c->n)->im;
                if(im > -eps)
                if(im <  eps)
                    break;
            }

            if(AMP(lb_2->lb->n)->re > re2)
                break;
        }

        if(lb_2->lb != NULL)
        if(AMP(lb_2->lb->n)->re > re1)
        if(AMP(lb_2->lb->n)->re < re2)
        {
            transfere_conexoes(lb_2->lb->n,lb_c->n);
            libera_lista_body_item(lb_c);
            continue;
        }

        lista_body *lb_1;
        for(lb_1 = LB_c[0]; lb_1->lb != NULL; lb_1 = lb_1->lb)
            if(AMP(lb_1->lb->n)->re > re1)
                break;

        for(              ; lb_1->lb != NULL; lb_2 = lb_1->lb)
        {
            if(AMP(lb_1->lb->n)->re < re2)
            {
                double im;
                im = AMP(lb_1->lb->n)->im - AMP(lb_c->n)->im;
                if(im > -eps)
                if(im <  eps)
                    break;
            }

            if(AMP(lb_1->lb->n)->re > re2)
                break;
        }

        if(lb_1->lb != NULL)
        if(AMP(lb_1->lb->n)->re > re1)
        if(AMP(lb_1->lb->n)->re < re2)
        {
            transfere_conexoes(lb_1->lb->n,lb_c->n);
            libera_lista_body_item(lb_c);

            lb_c     = lb_1->lb;
            lb_1->lb = lb_c->lb;

            lb_c->lb = lb_2->lb;
            lb_2->lb = lb_c;

            continue;
        }

        lb_c->lb = lb_1->lb;
        lb_1->lb = lb_c;
    }

    lista_body *lb_out;
    for(lb_out = LB_c[0]; lb_out->lb != NULL; lb_out = lb_out->lb);
    lb_out->lb = LB_c[1]->lb;

    COPY_STRUCT(lb,LB_c[0]->lb,lista_body);
    lb_zero = LB_c[0]->lb;

    return copia_lista_body(lb_out->lb);
}

void reduz_QDD(QDD *Q)
{
    lista_body *lb;
    lb = reduz_lista_amplitude(Q->lb);
    if(lb == NULL)
        return;

    lista_head *lh;
    lh = cria_lista_head_body(lb);
    libera_lista_body_item(lb);

    while(lh != NULL)
    {
/*
printf("\nNovo label ");mostra_label(NLABEL(lh));
fflush(stdout);
*/
        /*** Regra 1 ***/

        lista_head *lh_n;
        no  *n, *n1, *n2;

        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            n  = lb->n;
/*
printf("\n");
printf("\nNovo no");
mostra_no_compacto(n);
fflush(stdout);
*/
            n1 = BODY(n)->n;
            while(n1 != NULL)
            {
                if(EST(n1)->el != EST(n1)->th)
                    break;

                desconecta_DOIS(n1);
                transfere_conexoes(n,n1);

                n1 = BODY(n)->n;
            }
/*
printf("\nFim estagio 1");
fflush(stdout);
*/
            if(n1 == NULL)
            {
                Q->n = n1;
                libera_lista_head_item(lh);
                return;
            }
/*
Long i, tam, tot;
i   = 0;
tam = 1024*1024;
tot = tam*32;
printf("\n");
printf("\nTot: %llu",tot);
*/
            lista_body *lb_n_1, *lb_n_2;
            for(lb_n_1 = BODY(n); lb_n_1->lb != NULL; lb_n_1 = lb_n_2)
            {
/*
i++;
if(i%tam == 0)
{
    printf("\nk: %2llu/%llu",i/tam,tot/tam);
    fflush(stdout);
}
*/

                lb_n_2 = lb_n_1->lb;
                n1     = lb_n_2->n;

                if(EST(n1)->el != EST(n1)->th)
                    continue;

                desconecta_UM_pista(n1,n,NULL,lb_n_1);
                desconecta_UM_pista(n1,n,NULL,lb_n_1);
                transfere_conexoes(n,n1);

                lb_n_2 = lb_n_1;
            }
/*
printf("\ni final: %llu",i);
fflush(stdout);
*/

            for(lh_n = HEAD(n); lh_n->lh != NULL; lh_n = lh_n->lh)
            {
/*
printf("\nNOVO label n "); mostra_label(NLABEL(lh_n->lh));
fflush(stdout);
*/
                n1 = BODY(lh_n->lh)->n;
                while(EST(n1)->el == EST(n1)->th)
                {
                    desconecta_UM_pista(n1,n,lh_n,NULL);
                    desconecta_UM_pista(n1,n,lh_n,NULL);
                    n1 = BODY(lh_n->lh)->n;
                }
/*
printf("\nFim estagio 2");
fflush(stdout);

i   = 0;
printf("\n");
printf("\nTot: %llu",tot);
*/
                for(lb_n_1 = BODY(lh_n->lh); lb_n_1->lb != NULL; lb_n_1 = lb_n_2)
                {
/*
i++;
if(i%tam == 0)
{
    printf("\nk: %2llu/%llu",i/tam,tot/tam);
    fflush(stdout);
}
*/
                    lb_n_2 = lb_n_1->lb;

                    n1 = lb_n_2->n;
                    if(EST(n1)->el != EST(n1)->th)
                        continue;

                    desconecta_UM_pista(n1,n,NULL,lb_n_1);
                    desconecta_UM_pista(n1,n,NULL,lb_n_1);
                    transfere_conexoes(n,n1);
                    lb_n_2 = lb_n_1;
                }
/*
printf("\ni final: %llu",i);
fflush(stdout);
*/
            }
        }
/*
printf("\n");
printf("\n Regra 2");
fflush(stdout);
*/
        /*** Regra 2 ***/

        while(1)
        {
            n = BODY(lh)->n;
            for(lh_n = HEAD(n); lh_n != NULL; lh_n = lh_n->lh)
            {
/*
printf("\nRegra 2 chega a outro label: ");mostra_label(NLABEL(lh_n));
fflush(stdout);
*/
                if(BODY(lh_n)->lb == NULL)
                    continue;

                LB[0][0]->lb = NULL;
                LB[0][1]->lb = NULL;
                LB[1][0]->lb = NULL;
                LB[1][1]->lb = NULL;

/*
Long i, tam, tot;
i   = 0;
tam = 1024*1024;
tot = tam*32;
printf("\n");
printf("\nTot: %llu",tot);
*/
                COPY_STRUCT(lb_zero,lh_n,lista_body);
                while(lb_zero != NULL)
                {
/*
i++;
if(i%tam == 0)
{
    printf("\nk: %2llu/%llu",i/tam,tot/tam);
    fflush(stdout);
}
*/
                    lb      = lb_zero;
                    n1      = lb->n;
                    lb_zero = lb_zero->lb;

                    int lado;
                    lado  = !LADO(n1,n);
                    n2    =  VEST(n1)[lado];

                    lista_body *lb_1, *lb_2;
                    for(lb_2 = LB[lado][1]; lb_2->lb != NULL; lb_2 = lb_2->lb)
                        if(n2 < VEST(lb_2->lb->n)[lado])
                            break;

                    if(lb_2->n != NULL)
                    if(n2 == VEST(lb_2->n)[lado])
                    {
                        libera_lista_body_item(lb);
                        desconecta_UM(n1,n2);
                        transfere_conexoes(lb_2->n,n1);
                        continue;
                    }

                    for(lb_1 = LB[lado][0]; lb_1->lb != NULL; lb_1 = lb_1->lb)
                        if(n2 <= VEST(lb_1->lb->n)[lado])
                            break;


                    if(lb_1->lb != NULL)
                    if(n2 == VEST(lb_1->lb->n)[lado])
                    {
                        libera_lista_body_item(lb);

                        lb       = lb_1->lb;
                        lb_1->lb = lb->lb;

                        lb->lb   = lb_2->lb;
                        lb_2->lb = lb;

                        desconecta_UM(n1,n2);
                        transfere_conexoes(lb->n,n1);

                        continue;
                    }

                    lb->lb   = lb_1->lb;
                    lb_1->lb = lb;
                }
/*
printf("\nTerminou a separacao, montando");
fflush(stdout);
*/
                for(lb = LB[0][1]; lb->lb != NULL; lb = lb->lb);
                lb->lb = LB[1][1]->lb;
                if(LB[0][1]->lb != NULL)
                {
                    label *lab;
                    lab = NLABEL(LB[0][1]->lb);

                    lista_head *lh_aux;
                    for(lh_aux = lh; lh_aux->lh != NULL; lh_aux = lh_aux->lh)
                        if(COMPARE_LABEL(lab,<,NLABEL(lh_aux->lh)))
                            break;

                    lista_body *lb_aux;
                    if(COMPARE_LABEL(lab,==,NLABEL(lh_aux)))
                    {
                        lb = copia_lista_body(LB[0][1]->lb);
                        for(lb_aux = lb; lb_aux->lb != NULL; lb_aux = lb_aux->lb);
                        lb_aux->lb = BODY(lh_aux)->lb;
                        BODY(lh_aux)->lb = lb;
                    }
                    else
                    {
                        lh_aux->lh = copia_lista_body_head(LB[0][1]->lb,lh_aux->lh);
                    }
                }

                for(lb     = LB[0][0]    ; lb->lb != NULL; lb = lb->lb);
                for(lb->lb = LB[1][0]->lb; lb->lb != NULL; lb = lb->lb);
                lb->lb     = LB[0][1]->lb;
                lb_zero    = LB[0][0]->lb;
                COPY_STRUCT(lh_n,lb_zero,lista_body);
            }

            lb    =  BODY(lh)->lb;
            if(lb == NULL)
                break;

            COPY_STRUCT(lh,lb,lista_body);
            libera_lista_body_item(lb);
        }

        lh_n = lh;
        lh   = lh->lh;
        libera_lista_head_item(lh_n);
    }
}



void limpa_matriz(int height, int length, apply *A[height][length])
{
    int i, j;
    for(i=0; i<height; i++)
        for(j=0; j<length; j++)
            A[i][j] = NULL;
}

void libera_matriz(int height, int length, apply *A[height][length])
{
    int i, j;
    for(i=0; i<height; i++)
    for(j=0; j<length; j++)
    if(A[i][j] != NULL)
        libera_apply_lista(A[i][j]);
}

void encaixa_arvore(no *n, int N, apply *A[N+1][3])
{
    apply *a;
    a = cria_apply(n,NULL);
    ACCESS(A,n) = a;

    int i, j, k;
    for(i=N; i> 0; i--)
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

            a_1->a = ACCESS(A,n);
            ACCESS(A,n) = a_1;

            apply *a_2;
            lista_body *lb;
            for(lb = BODY(n)->lb ; lb != NULL; lb = lb->lb)
            {
                for(a_2 = ACCESS(A,lb->n); a_2->n1 != n   ; a_2 = a_2->a);
                VAPPLY(a_2)[LADO(lb->n,n)] = a_1;
            }

            lista_head *lh;
            for(lh = HEAD(n)->lh; lh != NULL; lh = lh->lh)
            for(lb = BODY(lh)   ; lb != NULL; lb = lb->lb)
            {
                for(a_2 = ACCESS(A,lb->n); a_2->n1 != n   ; a_2 = a_2->a);
                VAPPLY(a_2)[LADO(lb->n,n)] = a_1;
            }
        }
    }
}

void encaixa_QDD(QDD Q, apply *A[Q.N+1][3])
{
    encaixa_arvore(Q.n,Q.N,A);
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
        a->n2 = n = copia_no_estrutura(a->n1);
        n1 = a->a1->n2;
        n2 = a->a2->n2;
        conecta_DOIS(n,n1,n2);
    }
    return n;
}

QDD monta_QDD(int height, int length, apply *A[height][length])
{
    QDD Q;
    Q.n  = monta_arvore(height,length,A);

    apply *a;
    lista_body *lb;
    a = A[0][0];
    lb = cria_lista_body(a->n2,NULL);
    for(a = a->a; a != NULL; a = a->a)
        lb = cria_lista_body(a->n2,lb);
    Q.lb = lb;
    return Q;
}




no* copia_arvore(no *n, int N)
{
    apply *A[N+1][3];
    limpa_matriz(N+1,3,A);
    encaixa_arvore(n,N,A);
    n = monta_arvore(N+1,3,A);
    libera_matriz(N+1,3,A);
    return n;
}

QDD copia_QDD(QDD Q0)
{
    int height;
    height = Q0.N+1;

    apply *A[height][3];
    limpa_matriz(height,3,A);
    encaixa_arvore(Q0.n,Q0.N,A);

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
/*
printf("\nEnlistando");
fflush(stdout);
*/
    lista_head *lh;
    lista_body *lb;
    lh = enlista_arvore(Q1.n);
/*
printf("\nMudando");
fflush(stdout);
*/
    while(lh->lh != NULL)
    {
       /*
printf("\nNovo label ");mostra_label(NLABEL(lh));
*/
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
    limpa_matriz(height,3,A);
    encaixa_QDD(Q2,A);

    lista_body *lb_c;
    lb_c   = Q1.lb;
    lb     = BODY(&Q1);
    lb->lb = NULL;
/*
Long i, tam, tot;
i=0;
tam = 1024*1024;
tot = 67108864;

printf("\nIndo");
fflush(stdout);
*/
    while(lb_c != NULL)
    {
/*
i++;
if(i%tam == 0)
{
    printf("\ni: %2llu/%2llu",i/tam,tot/tam);
    fflush(stdout);
}
*/
        if(compara_amplitude_zero(AMP(lb_c->n)))
        {
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

QDD H()
{
    double amp = pow(2,-0.5);


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

    double re = 0.5;

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

    double re = 0.5;

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
    printf("\nINICIO DE TUDO");
    mostra_no(N);

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
        printf("\n------------------------------------------------------------------------");
        printf("\n\nNO %d", i);
        mostra_no(n[i]);
        conecta_UM(n[i], N, ELSE);
        printf("\nDepois da conexao\n");
        mostra_no(n[i]);
        mostra_no(N);
    }

    for(i=0; i < 6; i++)
    {
        desconecta_UM(n[i], N);
        libera_no(n[i]);
    }
    libera_no(N);
}

void teste_desconexao()
{
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


    printf("\n------------------------------------------------------------------------");
    printf("\nInicio\n");
    mostra_no(N);

    for(i=0; i<9; i++)
    {
        printf("\n------------------------------------------------------------------------");
        printf("\n\nNO %d", i);
        mostra_no(n[i]);

        desconecta_UM(n[i], N);

        printf("\nDepois da desconexao\n");
        mostra_no(n[i]);
        mostra_no(N);
    }

    printf("\n------------------------------------------------------------------------");
    printf("\nFim");
    mostra_no(N);

    for(i=0; i<9; i++)
        libera_no(n[i]);
    libera_no(N);
}

void teste_transfere()
{
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
    printf("\n\nTESTE 1 ");
    int i;
    for(i=0; i<5; i++)
        conecta_UM(n1[i],N1,ELSE);
    for(i=0; i<7; i++)
        conecta_UM(n2[i],N2,THEN);
    mostra_no(N1);
    mostra_no(N2);

    transfere_conexoes(N1,N2);
    printf("\n\n\tDEPOIS");
    mostra_no(N1);
    mostra_lista_head_estrutura_completo(N1);

    /*** Teste 2 ***/
    printf("\n\n\n\n\nTESTE 2");
    N2 = cria_no_amplitude(2,0);

    while(BODY(N1)->n != NULL)
        desconecta_UM(BODY(N1)->n,N1);

    conecta_DOIS(n1[2],N1,N1);
    conecta_DOIS(n2[4],N2,N2);
    mostra_no(N1);
    mostra_no(N2);

    transfere_conexoes(N1,N2);
    printf("\n\n\tDEPOIS");
    mostra_no(N1);
    mostra_lista_head_estrutura_completo(N1);

    /*** Teste 3 ***/
    printf("\n\n\n\n\nTESTE 3");
    N2 = cria_no_amplitude(2,0);

    while(BODY(N1)->n != NULL)
        desconecta_UM(BODY(N1)->n,N1);

    conecta_UM(n1[1],N1,ELSE);
    conecta_UM(n2[0],N2,THEN);
    mostra_no(N1);
    mostra_no(N2);

    transfere_conexoes(N1,N2);
    printf("\n\n\tDEPOIS\n");
    mostra_no(N1);
    mostra_lista_head_estrutura_completo(N1);

    while(BODY(N1)->n != NULL)
        desconecta_UM(BODY(N1)->n,N1);
    libera_no_amplitude(N1);
    for(i=0; i<5; i++)
        libera_no_estrutura(n1[i]);
    for(i=0; i<7; i++)
        libera_no_estrutura(n2[i]);

    mostra_quantidades();
}

void teste_reducao_lista()
{
    Long N, tot;
    double amp;
    for(N = 1; N < 26; N++)
    {
        set_Qbit(N);
        tot   = pow(2, N);
        amp = pow(tot, -0.5);
        //amp = 1;

        printf("\n");
        printf("\n");
        printf("\nN   : %d",N);
        printf("\ntot : %d",tot);
        printf("\namp : %.3e",amp);

        lista_body *lb, *lb_aux;
        no *n;
        n  = cria_no_amplitude(amp,0);
        lb = cria_lista_body(n,NULL);

        Long i;
        double theta, theta_0;
        theta_0 = 1.0 / tot;
        lb_aux = lb;
        printf("\n");
        for(i=1; i < tot; i++)
        {
            theta = i * theta_0;
            n = cria_no_amplitude(amp*cos(theta),amp*sin(theta));

            lb_aux->lb = cria_lista_body(n,NULL);
            lb_aux = lb_aux->lb;
        }

        Long quant;
        quant = conta_itens_lista_body(lb);
        printf("\n");
        printf("\nQuantidade antes  : %d",quant);

        lb_aux = reduz_lista_amplitude(lb);
        if(lb_aux != NULL)
            quant = conta_itens_lista_body(lb);

        printf("\nQuantidade depois : %d",quant);
        fflush(stdout);

        libera_lista_body_lista(lb_aux);
        for(lb_aux = lb; lb_aux != NULL; lb_aux = lb_aux->lb)
            libera_no_amplitude(lb_aux->n);
        libera_lista_body_lista(lb);

        mostra_quantidades();
    }
}

void teste_todos()
{
    time_t antes, depois;
    antes = clock();
    teste_conexao();
    teste_desconexao();
    teste_transfere();
    teste_reducao_lista();
    depois = clock();
    depois = difftime(depois,antes);
    printf("\n\n\nTesmpo: %d", depois);
}



void template_time()
{
    time_t antes, depois;
    long int tempo;
    long long int tam = 50, lim = 1e9;

    no *n1, *n2;
    n1 = cria_no_estrutra(R,1);
    n2 = cria_no_estrutra(C,1);


    printf("\n\n");
    antes = clock();
    for(int i=0; i< tam; i++)
    {
        printf("\t%2d",i);
        fflush(stdout);
        for(int j=0; j<lim; j++)
        {
            /*** FUNCAO AQUI CACETA ***/

            COPY_STRUCT(LABEL(n2),LABEL(n1),label);
            COPY_STRUCT(LABEL(n2),LABEL(n1),label);

            /*** FUNCAO AQUI CACETA ***/
        }
    }
    depois = clock();
    tempo = depois - antes;
    printf("\nTempo: %d",tempo);
    long int tempo1 = tempo;

    printf("\n\n");
    antes = clock();
    for(int i=0; i< tam; i++)
    {
        printf("\t%2d",i);
        fflush(stdout);
        for(int j=0; j<lim; j++)
        {
            /*** FUNCAO AQUI CACETA ***/

            COPY_STRUCT(LABEL(n2),LABEL(n1),label);

            /*** FUNCAO AQUI CACETA ***/
        }
    }
    depois = clock();
    tempo = depois - antes;
    printf("\nTempo: %d",tempo);
    tempo1 -= tempo;



    printf("\n\n");
    antes = clock();
    for(int i=0; i< tam; i++)
    {
        printf("\t%2d",i);
        fflush(stdout);
        for(int j=0; j<lim; j++)
        {
            /*** FUNCAO AQUI CACETA ***/

            COMPARE_LABEL(LABEL(n2),=,LABEL(n1));
            COMPARE_LABEL(LABEL(n2),=,LABEL(n1));

            /*** FUNCAO AQUI CACETA ***/
        }
    }
    depois = clock();
    tempo = depois - antes;
    printf("\nTempo: %d",tempo);
    long int tempo2 = tempo;

    printf("\n\n");
    antes = clock();
    for(int i=0; i< tam; i++)
    {
        printf("\t%2d",i);
        fflush(stdout);
        for(int j=0; j<lim; j++)
        {
            /*** FUNCAO AQUI CACETA ***/

            COMPARE_LABEL(LABEL(n2),=,LABEL(n1));

            /*** FUNCAO AQUI CACETA ***/
        }
    }
    depois = clock();
    tempo = depois - antes;
    printf("\nTempo: %d",tempo);
    tempo2 -= tempo;


    printf("\n");
    printf("\n");
    printf("\n");
    printf("\nResultado final");
    printf("\n");
    printf("\nTempo1 : %d",tempo1);
    printf("\nTempo2 : %d",tempo2);
    printf("\n");
    printf("\nRatio  : %f",((double)tempo1)/tempo2);

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    mostra_no(n2);
}

void analise_estruturas()
{
    lista_body lb;
    printf("\n");
    printf("\n");
    printf("\n%d",sizeof(lista_body));
    printf("\n");
    printf("\nlb    : %2d",SUBTRACT_POINTER(&(lb),&(lb)));
    printf("\nlb.n  : %2d",SUBTRACT_POINTER(&(lb.n),&(lb)));
    printf("\nlb.lb : %2d",SUBTRACT_POINTER(&(lb.lb),&(lb)));

    lista_head lh;
    printf("\n");
    printf("\n");
    printf("\n%d",sizeof(lista_head));
    printf("\n");
    printf("\nlh    : %2d",SUBTRACT_POINTER(&(lh),&(lh)));
    printf("\nlh.lb : %2d",SUBTRACT_POINTER(&(lh.lb),&(lh)));
    printf("\nlh.lh : %2d",SUBTRACT_POINTER(&(lh.lh),&(lh)));

    no n;
    printf("\n");
    printf("\n");
    printf("\n%d", sizeof(no));
    printf("\n");
    printf("\nn        : %2d",SUBTRACT_POINTER(&(n),&(n)));
    printf("\nn.lh     : %2d",SUBTRACT_POINTER(&(n.lh),&(n)));
    printf("\nn.lab    : %2d",SUBTRACT_POINTER(&(n.lab),&(n)));
    printf("\nn.lab.cl : %2d",SUBTRACT_POINTER(&(n.lab.cl),&(n)));
    printf("\nn.lab.ni : %2d",SUBTRACT_POINTER(&(n.lab.ni),&(n)));

    no_estrutura ne;
    printf("\n");
    printf("\n");
    printf("\n%d",sizeof(no_estrutura));
    printf("\n");
    printf("\nne      : %2d",SUBTRACT_POINTER(&(ne),&(ne)));
    printf("\nne.n    : %2d",SUBTRACT_POINTER(&(ne.n),&(ne)));
    printf("\nne.e    : %2d",SUBTRACT_POINTER(&(ne.e),&(ne)));
    printf("\nne.e.el : %2d",SUBTRACT_POINTER(&(ne.e.el),&(ne)));
    printf("\nne.e.th : %2d",SUBTRACT_POINTER(&(ne.e.th),&(ne)));

    no_amplitude na;
    printf("\n");
    printf("\n");
    printf("\n%d",sizeof(no_amplitude));
    printf("\n");
    printf("\nna      : %2d",SUBTRACT_POINTER(&(na),&(na)));
    printf("\nna.n    : %2d",SUBTRACT_POINTER(&(na.n),&(na)));
    printf("\nna.a    : %2d",SUBTRACT_POINTER(&(na.a),&(na)));
    printf("\nna.a.re : %2d",SUBTRACT_POINTER(&(na.a.re),&(na)));
    printf("\nna.a.th : %2d",SUBTRACT_POINTER(&(na.a.im),&(na)));

    QDD Q;
    printf("\n");
    printf("\n");
    printf("\n%d",sizeof(QDD));
    printf("\n");
    printf("\nQ    : %2d",SUBTRACT_POINTER(&(Q),&(Q)));
    printf("\nQ.n  : %2d",SUBTRACT_POINTER(&(Q.n),&(Q)));
    printf("\nQ.lb : %2d",SUBTRACT_POINTER(&(Q.lb),&(Q)));
    printf("\nQ.N  : %2d",SUBTRACT_POINTER(&(Q.N),&(Q)));
}

QDD um()
{
    QDD Q;
    Q.n  = cria_no_amplitude(1,0);
    Q.N  = 0;
    Q.lb = cria_lista_body(Q.n,NULL);
    return Q;
}


no* QFT_recursivo(int N, int i, int j, int Q, int exp, double amp)
{
    if(N == 0)
    {
        double theta, si, co;
        theta = 2*M_PI*i*j/Q;
        si = sin(theta);
        co = cos(theta);
        return cria_no_amplitude(si,co);
    }

    no *n;
    n = cria_no_estrutra(R,N);

    no *n1, *n2;
    n1 = cria_no_estrutra(C,N);
    n2 = cria_no_estrutra(C,N);
    EST(n)->el = n1;
    EST(n)->th = n2;
    BODY(n1)->n = n;
    BODY(n2)->n = n;

    no *na, *nb, *nc, *nd;
    na = QFT_recursivo(N-1,i    ,j    ,Q,exp/2,amp);
    nb = QFT_recursivo(N-1,i    ,j+exp,Q,exp/2,amp);
    nc = QFT_recursivo(N-1,i+exp,j    ,Q,exp/2,amp);
    nd = QFT_recursivo(N-1,i+exp,j+exp,Q,exp/2,amp);
    EST(n1)->el = na;
    EST(n1)->th = nb;
    BODY(na)->n = n1;
    BODY(nb)->n = n1;
    EST(n2)->el = nc;
    EST(n2)->th = nd;
    BODY(nc)->n = n2;
    BODY(nd)->n = n2;

    return n;
}

QDD QFT(int N)
{
    int Q0, exp;
    Q0   = pow(2,N);
    exp = Q0/2;
    double amp;
    amp = pow(2,-0.5*N);
    no *n;
    n = QFT_recursivo(N,0,0,Q0,exp,amp);

    lista_head *lh;
    lh = enlista_arvore(n);
    while(lh->lh != NULL)
    {
        libera_lista_body_lista(BODY(lh)->lb);

        lista_head *lh_aux;
        lh_aux = lh->lh;
        libera_lista_head_item(lh);
        lh = lh_aux;
    }

    QDD Q;
    Q.n = n;
    Q.N = N;
    Q.lb = cria_lista_body_copia(lh);
    libera_lista_head_item(lh);
    return Q;
}

void varios_H(int MAX)
{
    int N, i;
    for(N = 1; N<=MAX; N++)
    {
        set_Qbit(N);
        printf("\nN: %2d",N);
        fflush(stdout);

        QDD Q, Q1;
        Q = H();
        for(i=1; i<N; i++)
        {
            Q1 = H();
            Q  = produto_tensorial(Q,Q1);

            //printf("\t%d/%d",i+1,N);
            //fflush(stdout);
        }

        time_t antes, depois;
        //printf("\nReduzindo");
        //fflush(stdout);
        antes = clock();
        reduz_QDD(&Q);
        depois = clock();
        printf("\ttempo: %7.3f",difftime(depois,antes)/CLOCKS_PER_SEC);
        fflush(stdout);
        //mostra_QDD_simples(Q);
        libera_QDD(Q);
    }
}



int main()
{
    inicia_estruturas();
    set_Qbit(20);
    /******************************/

    /*int N = 3;
    QDD Q;
    set_Qbit(N);
    Q = QFT(N);

    mostra_quantidades();
    reduz_QDD(&Q);
    mostra_quantidades();
    libera_QDD(Q);*/

    varios_H(14);

    /******************************/
    finaliza_estruturas();
    printf("\n\n\nDeu certo\n");
    mostra_quantidades();
}