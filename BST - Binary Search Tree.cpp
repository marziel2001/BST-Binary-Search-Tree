#include <iostream>
using namespace std;

typedef struct Wezel
{
    unsigned int klucz;
    Wezel* lewy;
    Wezel* prawy;
} Wezel;
Wezel* StworzWezel(unsigned int klucz)
{
    Wezel* tempWezel = new Wezel;
    tempWezel->klucz = klucz;
    tempWezel->lewy = nullptr;
    tempWezel->prawy = nullptr;
    return tempWezel;
}
Wezel* Szukaj(Wezel* korzen, unsigned int klucz)
{
    if (korzen == nullptr) return nullptr;
    else if (korzen->klucz == klucz) return korzen;
    else if (klucz > korzen->klucz) return Szukaj(korzen->prawy, klucz);
    else return Szukaj(korzen->lewy, klucz);
}
void DodajDoDrzewa(Wezel*& korzen, unsigned int klucz)
{
    Wezel* tempWezel = korzen;
    Wezel* poprzedni = nullptr;

    while (tempWezel != nullptr)
    {
        if (klucz <= tempWezel->klucz)
        {
            poprzedni = tempWezel;
            tempWezel = tempWezel->lewy;
        }
        else
        {
            poprzedni = tempWezel;
            tempWezel = tempWezel->prawy;
        }
    }

    tempWezel = StworzWezel(klucz);

    if (poprzedni != nullptr)
    {
        if (klucz > poprzedni->klucz)
        {
            poprzedni->prawy = tempWezel;
        }
        else
        {
            poprzedni->lewy = tempWezel;
        }
    }
    else
    {
        korzen = tempWezel;
    }
}
unsigned int WezMinimum(Wezel* korzen)
{
    if (korzen->lewy != nullptr) return WezMinimum(korzen->lewy);
    else return korzen->klucz;
}
unsigned int WezMaksimum(Wezel* korzen)
{
    if (korzen->prawy != nullptr) return WezMaksimum(korzen->prawy);
    else return korzen->klucz;
}
Wezel* UsunWezel(Wezel* wezel, unsigned int klucz)
{
    if (wezel == nullptr) return wezel;

    if (klucz > wezel->klucz) wezel->prawy = UsunWezel(wezel->prawy, klucz);
    else if (klucz < wezel->klucz) wezel->lewy = UsunWezel(wezel->lewy, klucz);
    else // usuwanie
    {
        // 1. wezel nie ma dzieci - lisc
        // odpinamy referencje i zwalniamy pamiec
        if (wezel->lewy == nullptr && wezel->prawy == nullptr)
        {
            delete wezel;
            wezel = nullptr;
        }
        else if (wezel->lewy == nullptr)
            // 2. wezel ma jedno dziecko // prawe
            // podpinamy dziecko z zawartoscia w miejsce starego elementu i usuwamy stary element
        {
            Wezel* temp = wezel;
            wezel = wezel->prawy;
            delete temp;
        }
        else if (wezel->prawy == nullptr)
            // 2. wezel ma jedno dziecko // lewe
            // podpinamy dziecko z zawartoscia w miejsce starego elementu i usuwamy stary element
        {
            Wezel* temp = wezel;
            wezel = wezel->lewy;
            delete temp;
        }
        else // 3. mamy oboje dzieci w usuwanym elemencie
        {
            int min = WezMinimum(wezel->prawy);
            wezel->klucz = min;
            wezel->prawy = UsunWezel(wezel->prawy, wezel->klucz);
        }
    }
    return wezel;
}
int main()
{
    char input = ' ';
    unsigned int klucz;
    Wezel* drzewo = nullptr;

    while (1)
    {
        cin >> input;
        if (input == '+')
        {
            cin >> klucz;
            DodajDoDrzewa(drzewo, klucz);
        }
        else if (input == '-')
        {
            cin >> klucz;
            if (Szukaj(drzewo, klucz) != nullptr)
            {
                drzewo = UsunWezel(drzewo, klucz);
            }
        }
        else if (input == '?')
        {
            cin >> klucz;
            if (Szukaj(drzewo, klucz) == nullptr) cout << 0 << "\n";
            else cout << 1 << "\n";
        }
        else if (input == 'm')
        {
            cout << WezMinimum(drzewo) << "\n";
        }
        else if (input == 'M')
        {
            cout << WezMaksimum(drzewo) << "\n";
        }
        else if (input == 'q')
        {
            break;
        }
    }
    while (drzewo != nullptr)
    {
        drzewo = UsunWezel(drzewo, drzewo->klucz);
    }
}