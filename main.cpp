#include <iostream>
using namespace std;




// Structura pentru nodul unei liste ordonate

struct numar {
    int v; // Valoarea din listă
    numar *urm; // Legătura către următorul element din listă
};





// Funcția pentru crearea unei liste ordonate

numar *creare_ordonata() {
    numar *L, *c, *p, *prec;
    int n, x, OK;

    cout << "Capat lista x = ";
    cin >> x;

    L = new numar;      //Primul element
    L->v = x;
    L->urm = NULL;

    n = 1;
    OK = 1;

    while (OK != 0) {
        cout << "x = ";
        cin >> x;

        c = new numar;
        c->v = x;

        if (x <= (L->v))
        {
            c->urm = L;                 // Adaugarea la inceputul listei ( c se adauga inaintea lui L )
            L = c;

        } else {

            // Cautarea locului in care c trebuie adaugat in lista

            /* Cautarea lui p in lista L astfel incat (p->v) <= x ( valoarea stocată în membrul v al obiectului
            la care pointează pointerul p este mai mică sau egală cu valoarea lui x ) si
            ( p->urm->v ) ( valoarea stocată în membrul v al nodului următor al nodului la care pointează pointerul p într-o listă simplu înlănțuită) */

            // Inserarea lui c intre p si p->urm

            prec = L;
            p = L->urm;

            while (p != NULL) {

                if ((p->v) <= x) {
                    prec = p;
                    p = p->urm;

                } else {             // Adaugarea in interiorul listei

                    // (p->v) => x
                    // c este intre prec si p

                    c->urm = p;
                    prec->urm = c;
                    break;
                }
            }

            if (p == NULL) {              // Adaugarea la sfarsitul listei

                /* Daca a terminat while cu p == NULL, inseamna ca
                prc = ultimul element din lista si atunci c se adauga
                dupa ultimul element din lista*/

                c->urm = NULL;
                prec->urm = c;
            }
        }

        cout << "Continuam cu adaugarea in lista ordonata [1/0]?";
        cin >> OK;
    }

    return L;
}



// Funcția pentru afișarea listei

void parcurgere_lista(numar *cap)
{
    numar *c;            // Declarația unui pointer către un nod al listei



    if (cap == NULL)      // Verificare daca lista e vida

        cout<<"Lista este vida!"<<endl;
    else
    {
        c=cap;           // Inițializarea pointerului c cu adresa primului nod al listei


        while (c != NULL)
        {
            cout<<c->v<<" ";     // Afișarea valorii din nodul curent
            c=c->urm;            // Deplasarea la nodul următor în listă
        }
    }
}




// Funcția pentru interclasarea a două liste ordonate

numar *interclasare(numar *L1, numar *L2) {
    numar *L, *p1, *p2, *u, *c;
    L = new numar;           // Initializare lista vida


    if((L1 -> v) < (L2 -> v)) {

        L -> v = L1 -> v;
        L -> urm = NULL;
        p1 = L1 -> urm;
        p2 = L2;

    }                                   /* Compararea valorilor primelor elemente din cele două liste (L1 și L2)
                                           pentru a determina care dintre ele este mai mică.*/
                                        // Crearea primului nod al listei rezultate L cu valoarea minimă dintre cele două.
    else {

        L -> v = L2 -> v;
        L -> urm = NULL;
        p1 = L1;
        p2 = L2 -> urm;

    }

    u = L;




    while(p1 != NULL && p2 != NULL) {

        if((p1 -> v) < (p2 -> v)) {

            c = new numar;
            c -> v = p1 -> v;
            c -> urm = NULL;
            u -> urm = c;
            u = c;
            p1 = p1 -> urm;

        }                                  // Parcurgerea ambelor liste (L1 și L2) și compararea valorile nodurilor curente p1 și p2.
                                          // Adaugarea în lista rezultata nodul cu valoarea minimă dintre cele două.
        else {

            c = new numar;
            c -> v = p2 -> v;
            c -> urm = NULL;
            u -> urm = c;
            u = c;
            p2 = p2 -> urm;

        }

    }



    if(p1 != NULL) {

        while(p1 != NULL) {

            c = new numar;
            c -> v = p1 -> v;
            c -> urm = NULL;
            u -> urm = c;
            u = c;
            p1 = p1 -> urm;

        }

    }                            /* Adaugarea elementelor care au ramas din L1 sau L2 în cazul
                                  în care una dintre liste are mai multe elemente decât cealaltă.*/



        while(p2 != NULL) {

            c = new numar;
            c -> v = p2 -> v;
            c -> urm = NULL;
            u -> urm = c;
            u = c;
            p2 = p2 -> urm;



    }

    return L;
}





// Funcția pentru interclasarea a n liste ordonate

numar *interclasare_n_liste(numar *liste[], int n)
{
    if (n <= 0) {                // Verificare dacă numărul de liste n este mai mic sau egal cu zero.
        return NULL;
    }

    numar *rezultat = liste[0];   //Inițializare a unui pointer rezultat cu adresa primei liste din vectorul liste[].

    for (int i = 1; i < n; ++i) {
        rezultat = interclasare(rezultat, liste[i]);   /* Parcurge celelalte liste din vector, de la a doua la ultima,
                                                        și le interclasează succesiv cu rezultatul parțial stocat în rezultat.*/
    }

    return rezultat;
}



int main() {

    cout << "Interclasarea a n liste de numere intregi ordonate" << endl;


    // Introducerea listelor ordonate

    int numar_liste;
    cout << "Introdu numarul de liste: ";
    cin >> numar_liste;

    if (numar_liste <= 0) {
        cout << "Numarul de liste trebuie sa fie pozitiv." << endl;
        return 1;
    }

    numar **liste = new numar*[numar_liste];  /*Alocare dinamica a unui vector de pointeri la structura numar, pentru a stoca listele introduse.
                                           ( este utilă atunci când dimensiunea vectorului nu este cunoscută la compilare și trebuie să fie specificată la runtime)*/

    for (int i = 0; i < numar_liste; ++i) {           /*Iterează prin fiecare listă și folosește funcția creare_ordonata()
                                                        pentru a crea lista și a o adăuga la vectorul liste.*/
        cout << "Lista ordonata " << i + 1 << ":\n";
        liste[i] = creare_ordonata();
        cout << endl;
    }



    // Interclasarea listelor

    numar *rezultat_interclasare = interclasare_n_liste(liste, numar_liste);



    // Afișarea rezultatului

    cout << "Lista rezultat dupa interclasare: ";
    parcurgere_lista(rezultat_interclasare);



    // Eliberarea memoriei

    for (int i = 0; i < numar_liste; ++i) {


        // Eliberarea memoriei pentru fiecare lista

        numar *curent = liste[i];         //Inițializare a unui pointer curent cu adresa începutului listei curente liste[i].

        while (curent != nullptr) {          // Parcurgere a listei curente atâta timp cât există elemente în listă.

            numar *urmator = curent->urm;   /*Salvează adresa următorului element din listă pentru a evita
                                              pierderea acestei informații în urma ștergerii nodului curent.*/
            delete curent;
            curent = urmator;
        }
    }

    delete[] liste;     // Eliberarea memoriei alocate pentru vectorul de pointeri la structura numar.

    return 0;
}
