#include "my_functions.h"

enum menu {
            Insert = '1', 
            Queue = '2', 
            Stack = '3',
            Two_Stacks = '4',
            Map = '5',
            Print_Vector = '6',
            Exit = '7'
          };

int main() {
    char input;
    vector<int> v_numbers {4, 5, 6, 7, 8};

    while (true) {
        cout << "1: Ievadīt skaitļus\n";
        cout << "2: Rinda\n";
        cout << "3. Steks\n";
        cout << "4. Divi steki (Rinda)\n";
        cout << "5. Map\n";
        cout << "6. Izvada skaitļu virkni\n";
        cout << "7. Beigt darbību\n";

        cin >> input;

        switch (input) {
            case Insert:
                addNum(v_numbers);
                cout << endl;
                continue;
            case Queue:
                queuePrint(v_numbers);
                cout << endl;
                continue;
            case Stack:
                stackPrint(v_numbers);
                cout << endl;
                continue;
            case Two_Stacks:
                twoStackPrint(v_numbers);
                cout << endl;
                continue;
            case Map:
                /*Ieliek vectora skaitļus Map struktūrā. Tad katrs skaitlis
                tiek izprintēts kopā ar savu pozīciju, kā key-value pair */
                
                mapPrint(v_numbers);
                cout << endl;
                continue;
            case Print_Vector:
                printVector(v_numbers);
                cout << endl;
                continue;
            case Exit:
                break;
            default:
                cout << "Nepraeiza opcija, mēģini vēlreiz" << endl;
                continue;
        }
        break;
    }
    return 0;
}