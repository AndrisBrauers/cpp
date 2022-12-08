#include <iostream>
#include <string>
using namespace std;

int main(){
    string text = "Programmas ir jaraksta cilvekiem, kas tas lasis!";
    char input;
    for(;;){
        cin >> input;
        
        if (input == '1') {
            cin.ignore();
            getline(cin, text);
        }
        else if (input == '2') {
            cout << ((text.length() % 2 == 0) ? "Pāra" : "Nepāra") << endl;
        }
        else if (input == '3') {
            int sum = 0;
            for(int i = 1; i < text.length() + 1; i++){
                sum += i;
            }
            cout << "Summa: " << sum << endl;
        }
        else if (input == '4') {
            int fact = 1;
            for(int i = 1; i < text.length() + 1; i++){
                fact *= i;
            }
            cout << "Factoriālis: " << fact << endl;
        }
        else if (input == '5') {
            for(int i = text.length(); i >= 0; i--){
                cout << text[i];
            }
            cout << endl;
        }
        else if (input == '6') {
            break;
        }
        else {
            cout << "Nepraeiza opcija, mēģini vēlreiz" << endl;
        }
        
    }
    return 0;
}