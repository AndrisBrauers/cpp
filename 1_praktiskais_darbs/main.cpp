#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
    string text = "Programmas ir jaraksta cilvekiem, kas tas lasis!";
    string toDelete;
    char input;
    int count = 0;
    int max = 0;
    bool match = true;

    for(;;){
        cout << "1: Ievadīt jaunu tekstu (parastie burti) \n";
        cout << "2: Pasaka vai ievadītā teksta garums ir pāra vai nepāra skaitlis\n";
        cout << "3. Izvada summu no 1..n (kur n = teksta garums) \n";
        cout << "4. Atrod faktoriāli n (kur n = teksta garums) \n";
        cout << "5. Izvada virkni no otrā gala (reversā) \n";
        cout << "6. Beigt darbību \n";
        cout << "7. Izvada garāko vādu uz ekrāna\n";
        cout << "8. Katra vārda pēdējo burtu pārvērš par lielo\n";
        cout << "9. Izdzēš no virknes ievadīto vārdu\n";

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
        case '7':
            for(int i = 0; i < text.length(); i++){
                if(text[i] == ' '){
                    if(count > max){
                        max = count;
                    }
                    count = 0;
                } else {
                    cout << text[i];
                    count++;
                }
            }
            if(count > max){
                        max = count;
                        count = 0;
                    }
            count = 0;
            for(int i = 0; i < text.length(); i++){
                if(text[i] == ' '){
                    if(count == max){
                        for(int j = max; j > 0; j--){
                            cout << text[i - j];
                        }
                        cout << endl;
                    }
                    count = 0;
                } else {
                    count++;
                }
            }
            continue;
        case '8':
            for(int i = 0; i < text.length(); i++){
                if(text[i] == ' '){
                    if(int(text[i - 1] > 96 && int(text[i - 1] < 123))){
                        text[i - 1] = char(int(text[i - 1]) - 32);
                    }
                }
            }
            cout << text << endl;
            continue;
        case '9':
            cin >> toDelete;
            while(text.find(toDelete) != string::npos){
                text.replace(text.find(toDelete),toDelete.length(),"");
            }
            
            cout << text << endl;

        default:
            cout << "Nepraeiza opcija, mēģini vēlreiz" << endl;
            continue;
        }
        break;
    }
    return 0;
}