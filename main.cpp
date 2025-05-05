#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define fisier "produse.txt"
#define RED    "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[38;5;153m"
#define PINK "\033[38;5;205m"
#define RESET   "\033[0m"


void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

typedef struct {
    char nume[50];
    char tara[50];
    float pret;
    int cantitate;
} Produs;

void adauga_produs() {
    int opt;
    do {
        clear_screen();
        printf("------ADAUGA UN PRODUS------\n");

        FILE *f = fopen(fisier, "a");
        Produs p;

        printf("Introduceti numele produsului (0 pentru Back): ");
        scanf(" %[^\n]", p.nume);
        if (strcmp(p.nume, "0") == 0) {
            fclose(f);
            return;
        }

        printf("Introduceti tara din care provine produsul: ");
        scanf(" %[^\n]", p.tara);
        printf("Introduceti pretul produsului: ");
        scanf("%f", &p.pret);
        printf("Introduceti cantitatea produsului: ");
        scanf("%d", &p.cantitate);

        fprintf(f, "%s %s %.2f %d\n", p.nume, p.tara, p.pret, p.cantitate);
        fclose(f);

        printf("Produsul a fost adaugat.\n");
        printf("1. Adauga alt produs\n2. Inapoi la meniul principal\nAlege: ");
        scanf("%d", &opt);
    } while (opt == 1);
}

void afisare_produse() {
    int opt;
    do {
        clear_screen();
        printf("------PRODUSELE DISPONIBILE IN STOC------\n");
        FILE *f = fopen(fisier , "r");
        if (f == NULL) {
            printf("Nu sunt produse in stoc\n");
        } else {
            Produs p;
            while (fscanf(f, "%s %s %f %d",p.nume,p.tara,&p.pret,&p.cantitate)==4)
                printf("Nume: "PINK"%s"RESET" | Tara: "BLUE"%s "RESET"| Pret: "GREEN"%.2f"RESET" | Cantitate: "YELLOW"%d\n"RESET,p.nume,p.tara,p.pret,p.cantitate);
            fclose(f);
        }
        printf("\n1. Inapoi la meniul principal\nAlege: ");
        scanf("%d", &opt);
    } while (opt != 1);
}

void cautarea_produselor() {
    int opt;
    do {
        clear_screen();
        printf("------INFORMATII DESPRE PRODUSUL CAUTAT------\n");
        FILE *f = fopen(fisier, "r");
        if (f == NULL) {
            printf("Nu sunt produse in stoc.\n");
            return;
        }

        char numele_produsului_cautat[50];
        printf("Introduceti numele produsului (0 pentru Back): ");
        scanf(" %[^\n]", numele_produsului_cautat);
        if (strcmp(numele_produsului_cautat, "0") == 0) {
            fclose(f);
            return;
        }

        int gasit = 0;
        Produs p;
        while (fscanf(f, "%s %s %f %d",p.nume,p.tara,&p.pret,&p.cantitate)==4) {
            if (strcmp(p.nume, numele_produsului_cautat) == 0) {
                printf("\nProdus: "PINK "%s"RESET" | Tara: "BLUE"%s"RESET" | Pret: "GREEN"%.2f"RESET" | Cantitate: "YELLOW"%d\n"RESET,p.nume,p.tara,p.pret,p.cantitate);
                gasit = 1;
                break;
            }
        }
        if (!gasit) {
            printf("Produsul nu a fost gasit.\n");
        }

        fclose(f);
        printf("\n1. Cauta alt produs\n2. Inapoi la meniul principal\nAlege: ");
        scanf("%d", &opt);
    } while (opt == 1);
}

void modifica_produs() {
    int opt;
    do {
        clear_screen();
        printf("------MODIFICAREA PRODUSELOR------\n");

        FILE *f = fopen(fisier, "r");
        if (f == NULL) {
            printf("Nu sunt produse in stoc.\n");
            return;
        }

        Produs produse[100];
        int numarator = 0;
        while (fscanf(f, "%s %s %f %d", produse[numarator].nume, produse[numarator].tara, &produse[numarator].pret, &produse[numarator].cantitate) == 4) {
            numarator++;
        }
        fclose(f);

        char nume_de_modificat[50];
        printf("Introduceti numele produsului de modificat (0 pentru Back): ");
        scanf(" %[^\n]", nume_de_modificat);
        if (strcmp(nume_de_modificat, "0") == 0) return;

        int gasit = 0;
        for (int i = 0; i < numarator; i++) {
            if (strcmp(produse[i].nume, nume_de_modificat) == 0) {
                gasit = 1;
                printf("Produs gasit! Introduceti noile informatii.\n");

                printf("Noul nume: ");
                scanf(" %[^\n]", produse[i].nume);

                printf("Noua tara: ");
                scanf(" %[^\n]", produse[i].tara);

                printf("Noul pret: ");
                scanf("%f", &produse[i].pret);

                printf("Noua cantitate: ");
                scanf("%d", &produse[i].cantitate);
                break;
            }
        }

        if (!gasit) {
            printf("Produsul nu a fost gasit.\n");
        } else {
            f = fopen(fisier, "w");
            for (int i = 0; i < numarator; i++) {
                fprintf(f, "%s %s %.2f %d\n", produse[i].nume, produse[i].tara, produse[i].pret, produse[i].cantitate);
            }
            fclose(f);
            printf("Produs modificat cu succes!\n");
        }

        printf("\n1. Modifica alt produs\n2. Inapoi la meniul principal\nAlege: ");
        scanf("%d", &opt);
    } while (opt == 1);
}

void sterge_produs() {
    int opt;
    do {
        clear_screen();
        printf("------STERGE PRODUS------\n");

        FILE *f = fopen(fisier, "r");
        if (f == NULL) {
            printf("Nu sunt produse in stoc.\n");
            return;
        }

        Produs produse[100];
        int numarator = 0;
        while (fscanf(f, "%s %s %f %d", produse[numarator].nume, produse[numarator].tara,&produse[numarator].pret, &produse[numarator].cantitate) == 4) {
            numarator++;
        }
        fclose(f);

        char numele_produsului_sters[50];
        printf("Introduceti numele produsului de sters (0 pentru Back): ");
        scanf(" %[^\n]", numele_produsului_sters);
        if (strcmp(numele_produsului_sters, "0") == 0) return;

        int gasit = 0;
        f = fopen(fisier, "w");
        for (int i = 0; i < numarator; i++) {
            if (strcmp(produse[i].nume, numele_produsului_sters) != 0) {
                fprintf(f, "%s %s %.2f %d\n", produse[i].nume, produse[i].tara, produse[i].pret, produse[i].cantitate);
            } else {
                gasit = 1;
            }
        }
        fclose(f);

        if (gasit) {
            printf("Produsul a fost sters cu succes.\n");
        } else {
            printf("Produsul nu a fost gasit.\n");
        }

        printf("\n1. Sterge alt produs\n2. Inapoi la meniul principal\nAlege: ");
        scanf("%d", &opt);
    } while (opt == 1);
}

void cumparare_produs() {
    int opt;
    do {
        clear_screen();
        printf("------CUMPARARE PRODUS------\n");

        FILE *f = fopen(fisier, "r");
        if (f == NULL) {
            printf("Nu sunt produse in stoc.\n");
            return;
        }

        Produs produse[100];
        int numarator = 0;
        while (fscanf(f, "%s %s %f %d", produse[numarator].nume, produse[numarator].tara, &produse[numarator].pret, &produse[numarator].cantitate) == 4) {
            numarator++;
        }
        fclose(f);

        char numele_produsului[50];
        int cantitate_dorita;

        printf("Introduceti numele produsului (0 pentru Back): ");
        scanf(" %[^\n]", numele_produsului);
        if (strcmp(numele_produsului, "0") == 0) return;

        printf("Introduceti cantitatea dorita: ");
        scanf("%d", &cantitate_dorita);

        int gasit = 0;
        for (int i = 0; i < numarator; i++) {
            if (strcmp(produse[i].nume, numele_produsului) == 0) {
                if (produse[i].cantitate >= cantitate_dorita) {
                    produse[i].cantitate -= cantitate_dorita;
                    printf("Achizitie reusita!\n");
                } else {
                    printf("Stoc insuficient.\n");
                }
                gasit = 1;
                break;
            }
        }

        if (!gasit) {
            printf("Produsul nu a fost gasit.\n");
        }

        f = fopen(fisier, "w");
        for (int i = 0; i < numarator; i++) {
            fprintf(f, "%s %s %.2f %d\n", produse[i].nume, produse[i].tara, produse[i].pret, produse[i].cantitate);
        }
        fclose(f);

        printf("\n1. Cumpara alt produs\n2. Inapoi la meniul principal\nAlege: ");
        scanf("%d", &opt);
    } while (opt == 1);
}

void meniu_principal_aplicatie() {
    int optiune = -1;
    while (optiune != 0) {
        clear_screen();
        printf("------MENIUL PRINCIPAL------\n");
        printf("0. Iesire\n");
        printf("1. Adauga produs\n");
        printf("2. Afiseaza produse\n");
        printf("3. Cauta produs\n");
        printf("4. Modifica produs\n");
        printf("5. Sterge produs\n");
        printf("6. Cumpara produs\n");
        printf("Alege optiunea: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 0: printf("Iesire din aplicatie.\n"); break;
            case 1: adauga_produs(); break;
            case 2: afisare_produse(); break;
            case 3: cautarea_produselor(); break;
            case 4: modifica_produs(); break;
            case 5: sterge_produs(); break;
            case 6: cumparare_produs(); break;
            default: printf("Optiune invalida. Incearca din nou.\n");
        }
    }
}

int main() {
    meniu_principal_aplicatie();
    return 0;
}
