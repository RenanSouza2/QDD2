#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    char   N;
    struct lista_body *lb;
};

struct apply
{
    struct no    *n, *n1, *n2;
    struct apply *a, *a1, *a2;
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



#define BODY(PONTEIRO)((lista_body*)PONTEIRO)
#define HEAD(PONTEIRO)((lista_head*)PONTEIRO)
#define NO(PONTEIRO)((no*)PONTEIRO)
#define LABEL(PONTEIRO)((label*)(HEAD(PONTEIRO)+1))
#define NLABEL(PONTEIRO)(LABEL(BODY(PONTEIRO)->n))
#define NEST(PONTEIRO)((no_estrutura*)PONTEIRO)
#define NAMP(PONTEIRO)((no_amplitude*)PONTEIRO)
#define EST(PONTEIRO)((estrutura*)(NO(PONTEIRO)+1))
#define AMP(PONTEIRO)((amplitude*)(NO(PONTEIRO)+1))
#define COMPARE_LABEL(LABEL_1, OPERANDO, LABEL_2) (*((long*)LABEL_1) OPERANDO *((long*)LABEL_2))
#define SUBTRACT_POINTER(POINTER_1, POINTER_2) (((void*)POINTER_1) - ((void*)POINTER_2))
#define COMPARE_STRUCT(PONTEIRO_1, PONTEIRO_2, ESTRUTURA)(memcmp(PONTEIRO_1, PONTEIRO_2, sizeof(ESTRUTURA))==0)
#define COPY_STRUCT(PONTEIRO_1, PONTEIRO_2, ESTRUTURA)(memcpy(PONTEIRO_1,PONTEIRO_2,sizeof(ESTRUTURA)))



int iNE = 0, iNA = 0, iLB = 0, iLH = 0;
lista_body *lb_zero;

void exit_program()
{
    exit(123456);
}



no_estrutura* cria_no_estrutra(int classe, int nivel)
{
    no_estrutura *ne;
    ne = malloc(sizeof(no_estrutura));
    if(ne == NULL)
        exit_program();
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
        exit_program();
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



lista_body* cria_lista_body(no *n, lista_body *lb_next)
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program();
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
        exit_program();
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
        exit_program();
    iLB++;

    return lb;
}

lista_body* cria_lista_body_copia(lista_body *lb_0)
{
    lista_body *lb;
    lb = malloc(sizeof(lista_body));
    if(lb == NULL)
        exit_program();
    iLB++;

    COPY_STRUCT(lb,lb_0,lista_body);

    return lb;
}



lista_head* cria_lista_head(no *n, lista_head *lh_next)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program();
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
        exit_program();
    iLH++;
    return lh;
}

lista_head* cria_lista_head_pendurado()
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program();
    iLH++;
    return lh;
}

lista_head* cria_lista_head_copia(lista_head *lh_0)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program();
    COPY_STRUCT(lh,lh_0,lista_head);
    iLH++;
    return lh;
}

lista_head* cria_lista_head_body(lista_body *lb)
{
    lista_head *lh;
    lh = malloc(sizeof(lista_head));
    if(lh == NULL)
        exit_program();
    iLH++;
    COPY_STRUCT(lh,lb,lista_body);
    lh->lh = NULL;
    return lh;
}



apply* cria_apply(no *n1, no *n2)
{

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



void inicia_estruturas()
{
    lb_zero = cria_lista_body_vazio();
}

void finaliza_estruturas()
{
    libera_lista_body_item(lb_zero);
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
    lista_head *lh_aux;
    for(lh_aux = lh; lh_aux != NULL; lh_aux = lh_aux->lh)
    {
        printf("\n---------------------");
        printf("\nLabel: ");mostra_label(NLABEL(lh_aux));
        mostra_lista_body_lista(BODY(lh_aux));
    }
    printf("\n---------------------");
}


void mostra_estrutura(estrutura *est)
{
    mostra_ponteiro(est->el);printf("\tth: ");mostra_ponteiro(est->th);
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
        mostra_lista_head_estrutura_simples(HEAD(ne));
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


void mostra_amplitude(amplitude *amp)
{
    if(amp == NULL)
        return;

    printf("% .4e % .4e",amp->re,amp->im);
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
        mostra_lista_head_estrutura_simples(HEAD(na));
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
    {
        mostra_no_amplitude(NAMP(n));
        return;
    }

    mostra_no_estrutura(NEST(n));
}


void mostra_lista_body_amplitudes(lista_body *lb)
{
    lista_body *lb_aux;
    int i;
    for(i=0, lb_aux = lb; lb_aux != NULL; i++, lb_aux = lb_aux->lb)
    {
        printf("\n\tNo %2d: ",i);
        mostra_amplitude(AMP(lb_aux->n));
    }
}

void mostra_lista_body_estrutura_completa(lista_body *lb)
{
    for(; lb != NULL; lb = lb->lb)
        mostra_no(lb->n);
}

void mostra_lista_head_estrutura_compacto(lista_head *lh)
{
    for(; lh != NULL; lh = lh->lh)
    {
        lista_body *lb;
        printf("\n---------------------------------------------------------------");
        printf("\nLABEL: ");mostra_label(NLABEL(lh));
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
            mostra_no_compacto(lb->n);
    }
    printf("\n---------------------------------------------------------------");
}

void mostra_lista_head_estrutura_completo(lista_head *lh)
{
    for(; lh != NULL; lh = lh->lh)
    {
        lista_body *lb;
        printf("\n---------------------------------------------------------------");
        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
            mostra_no(lb->n);
    }
    printf("\n---------------------------------------------------------------");
}



void mostra_quantidades()
{
    printf("\niLB: %d",iLB);
    printf("\niLH: %d",iLH);
    printf("\niNE: %d",iNE);
    printf("\niNA: %d",iNA);
    printf("\n");
}



lista_head* enlista_arvore(no *n)
{
    lista_head *lh;
    lh = cria_lista_head(n,NULL);

    lista_head *lh_1;
    lista_body *lb_1;
    for(lh_1 = lh; NLABEL(lh_1)->ni != 0; lh_1 = lh_1->lh)
        for(lb_1 = BODY(lh_1); lb_1 != NULL;  lb_1 = lb_1->lb)
        {
            no **n_filhos;
            n_filhos = EST(lb_1->n);
            for(int i=0; i<2; i++)
            {
                lista_head *lh_2;
                n = n_filhos[i];
                for(lh_2 = lh_1; lh_2->lh != NULL; lh_2 = lh_2->lh)
                    if(COMPARE_LABEL(LABEL(n),>,NLABEL(lh_2->lh)))
                        break;

                if(COMPARE_LABEL(LABEL(n),!=,NLABEL(lh_2)))
                {
                    lh_2->lh = cria_lista_head(n,lh_2->lh);
                    continue;
                }

                lista_body *lb_2;
                for(lb_2 = BODY(lh_2); lb_2 != NULL; lb_2 = lb_2->lb)
                    if(n == lb_2->n)
                        break;

                if(lb_2 != NULL)
                    continue;

                BODY(lh_2)->lb = cria_lista_body(n,BODY(lh_2)->lb);
            }
        }
    return lh;
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
    mostra_arvore_base(n,mostra_lista_head_estrutura_simples);
}

void mostra_arvore_compacto(no *n)
{
    mostra_arvore_base(n,mostra_lista_head_estrutura_compacto);
}

void mostra_arvore_completo(no *n)
{
    mostra_arvore_base(n, mostra_lista_head_estrutura_completo);
}


void mostra_QDD_base(QDD Q, void(*mostra_arvore)(no*))
{
    printf("QDD");
    printf("\nN: %d",Q.N);
    printf("\n");
    mostra_arvore(Q.n);
    printf("\n");
    printf("\nAmplitudes");
    mostra_lista_body_amplitudes(Q.lb);
}

void mostra_QDD_siples(QDD Q)
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
    ((no**)EST(n1))[lado] = n2;
    inclui_no(HEAD(n2),n1);
}

void conecta_DOIS(no *n, no *nel, no *nth)
{
    conecta_UM(n,nel,ELSE);
    conecta_UM(n,nth,THEN);
}

void desconecta_UM(no *n1, no *n2)
{
    if(EST(n1)->el == n2)
        EST(n1)->el = NULL;
    else
        EST(n1)->th = NULL;

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
    if(BODY(n2)->n == NULL)
    {
        libera_no(n2);
        return;
    }

    if(BODY(n1)->n == NULL)
    {
        COPY_STRUCT(n1,n2,lista_head);
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
            if(EST(n)->el == n2)
                EST(n)->el = n1;
            if(EST(n)->th == n2)
                EST(n)->th = n1;
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
    if(COMPARE_LABEL(lab, ==, NLABEL(lh)))
    {
        lista_body *lb, *lb_next;
        for(lb = BODY(lh), lb_next = lb->lb; lb_next != NULL; lb = lb_next, lb_next = lb->lb);
        lb->lb = cria_lista_body_copia(BODY(n2));
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
            lh->lh = lh_1;
            lh     = lh->lh;
            for(lb = BODY(lh), lb_next = lb->lb; lb_next != NULL; lb = lb_next, lb_next = lb->lb);
            lb->lb = cria_lista_body_copia(BODY(lh_2));

            lista_head *lh_aux;
            lh_aux = lh_2;

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



double eps;

void set_Qbit(int N)
{
    eps = pow(2,-0.5*N)/300;
}

int compara_amplitude(amplitude *amp_1, amplitude *amp_2)
{
    /*printf("\nAmplitudes comparadas\t");
    mostra_amplitude(amp_1);
    printf("\t");
    mostra_amplitude(amp_2);*/

    double re;
    re = amp_1->re - amp_2->re;
    if(re > -eps)
    if(re <  eps)
    {
        double im;
        im = amp_1->im - amp_2->im;
        if(im > -eps)
        if(im <  eps)
        {
            //printf("\t1");
            return 1;
        }
    }
    //printf("\t0");
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



lista_body* reduz_lista_amplitude(lista_body *lb)
{
    if(lb->lb == NULL)
        return NULL;

    lista_body *lb_2, *lb_out;
    lb_out = lb_zero;
    lb_out->lb = NULL;

    for(; lb != NULL; lb = lb->lb)
    {
        no *n1;
        n1 = lb->n;
        for(lb_2 = lb; lb_2->lb != NULL; lb_2 = lb_2->lb)
            if(compara_amplitude(AMP(n1),AMP(lb->lb->n)))
                break;

        if(lb_2->lb == NULL)
            continue;

        lb_out->lb = cria_lista_body(n1,NULL);
        lb_out = lb_out->lb;

        lista_body *lb_aux;
        for(; lb_2->lb != NULL; lb_2 = lb_aux)
        {
            lb_aux = lb_2->lb;

            no *n2;
            n2 = lb_aux->n;
            if(!compara_amplitude(AMP(n1),AMP(n2)))
                continue;

            transfere_conexoes(n1,n2);

            lb_2->lb = lb_aux->lb;
            libera_lista_body_item(lb_aux);
            lb_aux = lb_2;
        }
    }

    return lb_zero->lb;
}

int conta_itens_lista_body(lista_body *lb)
{
    int i;
    for(i=0; lb != NULL; i++, lb = lb->lb);
    return i;
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
        /*** Regra 1 ***/

        lista_head *lh_n;
        lista_body *lb_n_1, *lb_n_2;
        no  *n, *n1, *n2;

        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            n  = lb->n;
            n1 = BODY(n)->n;
            while(n1 != NULL)
            {
               if(EST(n1)->el != EST(n1)->th)
                   break;

                desconecta_DOIS(n1);
                transfere_conexoes(n,n1);

                n1 = BODY(n)->n;
            }

           if(n1 == NULL)
           {
               Q->n = n1;
               libera_lista_head_item(lh);
               return;
           }

           for(lb_n_1 = BODY(n); lb_n_1->lb != NULL; lb_n_1 = lb_n_2)
           {
               lb_n_2 = lb_n_1->lb;
               n1     = lb_n_2->n;

               if(EST(n1)->el != EST(n1)->th)
                   continue;

               desconecta_UM_pista(n1,n,NULL,lb_n_1);
               desconecta_UM_pista(n1,n,NULL,lb_n_1);
               transfere_conexoes(n,n1);

               lb_n_2 = lb_n_1;
           }

           for(lh_n = HEAD(n); lh_n->lh != NULL; lh_n = lh_n->lh)
           {
               n1 = BODY(lh_n->lh)->n;
               while(lh_n->lh != NULL)
               {
                   if(EST(n1)->el != EST(n1)->th)
                       break;

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

                   desconecta_UM_pista(n1,n,NULL,lb_n_1);
                   desconecta_UM_pista(n1,n,NULL,lb_n_1);
                   transfere_conexoes(n,n1);
                   lb_n_2 = lb_n_1;
               }
           }
        }

        /*** Regra 2 ***/

        for(lb = BODY(lh); lb != NULL; lb = lb->lb)
        {
            n = lb->n;
            for(lh_n   = HEAD(n)   ; lh_n   != NULL; lh_n   = lh_n->lh)
            for(lb_n_1 = BODY(lh_n); lb_n_1 != NULL; lb_n_1 = lb_n_1->lb)
            {
                n1 = lb_n_1->n;
                for(lb_n_2 = lb_n_1; lb_n_2->lb != NULL; lb_n_2 = lb_n_2->lb)
                    if(COMPARE_STRUCT(EST(n1),EST(lb_n_2->lb->n),estrutura))
                        break;

                if(lb_n_2->lb == NULL)
                    continue;

                inclui_no(lh,n1);

                lista_body *lb_aux;
                for(; lb_n_2->lb != NULL; lb_n_2 = lb_aux)
                {
                    lb_aux = lb_n_2->lb;
                    n2     = lb_aux->n;

                    if(!COMPARE_STRUCT(EST(n1),EST(n2),estrutura))
                        continue;

                    if(n == EST(n2)->el)
                    {
                        desconecta_UM_pista(n2,n,NULL,lb_n_2);
                        desconecta_UM(n2,EST(n2)->th);
                    }
                    else
                    {
                        desconecta_UM(n2,EST(n2)->el);
                        desconecta_UM_pista(n2,n,NULL,lb_n_2);
                    }
                    transfere_conexoes(n1,n2);
                    lb_aux = lb_n_2;
                }
            }
        }

        lh_n = lh;
        lh   = lh->lh;

        libera_lista_body_lista(BODY(lh_n)->lb);
        libera_lista_head_item(lh_n);
    }
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
        n[i][j] = cria_no_estrutra(V,4-i);

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

no* copia_arvore(no *n, int N)
{
    lista_head *lh;
    lh = enlista_arvore(n);


}

QDD copia_QDD(QDD Q);

QDD produto_tensorial(QDD Q1, QDD Q2);



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
    n1 = cria_no_amplitude(1,2);
    n2 = cria_no_amplitude(2,1);

    int res;

    printf("\n\n");
    antes = clock();
    for(int i=0; i< tam; i++)
    {
        printf("\t%2d",i);
        fflush(stdout);
        for(int j=0; j<lim; j++)
        {
            /*** FUNCAO AQUI CACETA ***/


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


            /*** FUNCAO AQUI CACETA ***/
        }
    }
    depois = clock();
    tempo = depois - antes;
    printf("\nTempo: %d",tempo);
    tempo2 -= tempo;

    printf("%d",res);

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\nResuktado final");
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
    printf("\n%d",res);
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
}


QDD le_matriz(char *arquivo)
{
    char c[50];
    c[0] = '\0';
    sprintf(c,"%s.QDD",arquivo);
    printf("\nNOME: %s",c);

}


int main()
{
    inicia_estruturas();
    set_Qbit(20);
    /******************************/

    QDD Q;
    Q = H_2();

    printf("\n\n");


    reduz_QDD(&Q);

    printf("\n\n\n\n\n\n\n");
    mostra_QDD_completo(Q);
    libera_QDD(Q);

    /******************************/
    finaliza_estruturas();
    printf("\n\n\nDeu certo\n");
    mostra_quantidades();
}

