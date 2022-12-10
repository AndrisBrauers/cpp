#include <iostream>
#include <string>
using namespace std;

int main(){
    string text = "Programmas ir jaraksta cilvekiem, kas tas lasis!";
    char input;
    for(;;){
        cout << "1: Ievadīt jaunu tekstu (parastie burti) \n";
        cout << "2: Pasaka vai ievadītā teksta garums ir pāra vai nepāra skaitlis\n";
        cout << "3. Izvada summu no 1..n (kur n = teksta garums) \n";
        cout << "4. Atrod faktoriāli n (kur n = teksta garums) \n";
        cout << "5. Izvada virkni no otrā gala (reversā) \n";
        cout << "6. Beigt darbību \n";

        cin >> input;

        int sum = 0;
        unsigned long long fact = 1;

        switch (input)
        {
        case '1':
            cin.ignore();
            getline(cin, text);
            continue;
        case '2':
            cout << ((text.length() % 2 == 0) ? "Pāra" : "Nepāra") << endl;
            continue;
        case '3':
            for(int i = 1; i < text.length() + 1; i++){
                sum += i;
            }
            cout << "Summa: " << sum << endl;
            continue;
        case '4':
            for(int i = 1; i < text.length() + 1; i++){
                fact *= i;
            }
            cout << "Factoriālis: " << fact << endl;
            continue;
        case '5':
            for(int i = text.length(); i >= 0; i--){
                cout << text[i];
            }
            cout << endl;
            continue;
        case '6':
            break;
        default:
            cout << "Nepraeiza opcija, mēģini vēlreiz" << endl;
            continue;
        }
        break;
    }
    return 0;
}