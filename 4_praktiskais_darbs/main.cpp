// PS > g++ main.cpp; ./a.exe

// Izveidot C++ programmu, kura attaino noliktavas programmatūras funkcijas:
// Datu ievade (tiek papildināts produkts ar skaitu; ja nav tāda produkta, tad ievietots): X1
// Visu datu izvade (izvada visus produktus uz ekrāna): X1
// Produktu pārdošana (samazina attiecīgo skaitu; ja nav tāda vai nav ko pārdot - paziņo lietotājam): X2
// Izvada konkrēti datus par vienu produktu uz ekrāna (atrod pēc vārda): X2
// Izdrukāt uz ekrāna Top3 visvairāk iztirgotos produktus: X1
// Izdrukāt uz ekrāna Top3 vismazāk iztirgotos produktus: X2
// Izdrukāt uz ekrāna Top3 tos produktus par kuriem ir visvairāk nopelnīts: X2
// Izdrukāt uz ekrāna Top3 tos produktus par kuriem ir vismazāk nopelnīts: X1
// Izdrukāt uz ekrāna Top3 visdārgākos produktus: X1
// Izdrukāt uz ekrāna Top3 vislētākos produktus: X2
// Produkti satur sekojošu informāciju: (X1)
// Nosaukums
// Cena
// Pieejamais produktu skaits
// Pārdotais produktu skaits
// Jānorealizē arī atbilstošas izvēlnes, lai lietotājam ir ērti darboties ar programmu. X2
// Piezīme. Visas darbības tiek veiktas ar binārā failā ierakstītiem datiem (produkti).
// 1-3. Izveidot jaunu izvēlni: Random produkts
// Izvēloties šo izvēlni - programma lietotājam prasa ievadīt daudzumu. Pēc ievadītā daudzuma atrod tos produktus, kas ir pieejami (ja nav, tad paziņo lietotājam).
// No atrastiem produktiem piedāvā vienu lietotājam. Ja lietotājs nevēlas šo produktu, tad piedāvā nākamo. Ja lietotājs kādu izvēlas, tad - šo daudzumu pārdod lietotājam (attiecīgi samazina daudzuma skaitu un palielina pārdoto skaitu). Ja lietotājs neizvēlas nevienu, tad beigās paziņo, ka šāda daudzuma produkti nav pieejami

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <limits>

#define NAME_LENGTH 20

using namespace std;

enum eOptions
{
    Input,
    Output,
    Sell,
    Search,
    MostSold,
    LeastSold,
    MostEarned,
    LeastEarned,
    MostExpensive,
    MostCheap,
    MostAvailable,
    MostUnavailable,
    Random,
    Sum,
    Asorti,
    End
};

struct Product
{
    char name[NAME_LENGTH + 1];
    double price;
    int available;
    int sold;
};

class Storage
{
private:
    vector<Product> data;

    void printTop3Table()
    {
        cout << "|----------------------------------------------------------|" << endl;
        cout << "| # |" << setw(12) << "Name" << setw(8) << "|" << setw(8) << "Price" << setw(4) << "|" << setw(11) << "Available" << setw(3) << "|" << setw(6) << "Sold" << setw(3) << "|" << endl;
        cout << "|----------------------------------------------------------|" << endl;

        for (int i = 0; i < data.size() && i < 3; ++i)
        {
            cout << "| " << i + 1 << " | " << setw(18) << left << data[i].name << "| " << setw(10) << left << data[i].price << "| " << setw(12) << left << data[i].available << "| " << setw(7) << left << data[i].sold << "|" << right << endl;
        }

        cout << "|----------------------------------------------------------|" << endl;
    }

public:
    Storage()
    {
        ifstream fileIn;
        fileIn.open("storage.bin", ios::in | ios::binary);

        if (fileIn.is_open())
        {
            size_t size;
            fileIn.read((char *)&size, sizeof(size));

            data.resize(size);
            fileIn.read((char *)&data[0], size * sizeof(Product));

            cout << "Opened " << size << " product(s) from file!" << endl;
        }

        fileIn.close();
    }

    ~Storage()
    {
        ofstream fileOut("storage.bin", ios::out | ios::binary);

        size_t size = data.size();
        fileOut.write((char *)&size, sizeof(size));

        fileOut.write((char *)&data[0], data.size() * sizeof(Product));

        fileOut.close();

        cout << "Saved " << size << " product(s) to file!" << endl;
    }

    void add()
    {
        string productName;

        cout << "Choose product to restock: " << endl
             << "Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, productName);

        auto elementPos = find_if(data.begin(), data.end(), [&productName](const Product i)
                                  { return (i.name == productName); });

        if (elementPos != data.end())
        {
            cout << "Amount to increment quantity by:";

            int temp;
            cin >> temp;

            (*elementPos).available += temp;
        }
        else
        {
            cout << "Product not found. New product will be added." << endl
                 << "Enter the details: " << endl;

            Product product;

            strcpy(product.name, productName.c_str());

            cout << "Price: ";
            cin >> product.price;

            cout << "Available quantity: ";
            cin >> product.available;

            product.sold = 0;

            data.push_back(product);
        }
    }

    void print()
    {
        cout << "|------------------------------------------------------|" << endl;
        cout << "|" << setw(12) << "Name" << setw(8) << "|" << setw(8) << "Price" << setw(4) << "|" << setw(11) << "Available" << setw(3) << "|" << setw(6) << "Sold" << setw(3) << "|" << endl;
        cout << "|------------------------------------------------------|" << endl;

        for (const auto &i : data)
        {
            cout << "| " << setw(18) << left << i.name << "| " << setw(10) << left << i.price << "| " << setw(12) << left << i.available << "|" << setw(8) << left << i.sold << "|" << right << endl;
        }

        cout << "|------------------------------------------------------|" << endl;
    }

    void sell()
    {
        string name;
        cout << "Product name: ";
        cin >> name;
        int index = -1;
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].name == name)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "There is not such product." << endl;
            return;
        }
        //
        int sell;
        cout << "Available quantity: " << data[index].available << endl;
        cout << "How many do you want to sell: " << endl;
        cin >> sell;
        if (sell > data[index].available)
        {
            cout << "There are not enough available " << data[index].name << " items." << endl;
            return;
        }
        data[index].available -= sell;
        data[index].sold += sell;
    }

    void search()
    {
        string name;
        cout << "Product name: ";
        cin >> name;
        int index = -1;
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].name == name)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "There is not such product." << endl;
            return;
        }

        cout << "Price: " << data[index].price << endl;
        cout << "Available: " << data[index].available << endl;
        cout << "Sold: " << data[index].sold << endl;
    }

    void mostSold()
    {
        sort(data.begin(), data.end(), [](const Product &a, const Product &b)
             { return a.sold > b.sold; });

        printTop3Table();
    }

    void leastSold()
    {
        sort(data.begin(), data.end(), [](Product a, Product b)
             { return a.sold < b.sold; });

        printTop3Table();
    }

    void mostEarned()
    {
        sort(data.begin(), data.end(), [](Product a, Product b)
             { return double(a.sold) * a.price > double(b.sold) * b.price; });

        printTop3Table();
    }

    void leastEarned()
    {
        sort(data.begin(), data.end(), [](const Product &a, const Product &b)
             { return a.sold * a.price < b.sold * b.price; });

        printTop3Table();
    }

    void mostExpensive()
    {
        sort(data.begin(), data.end(), [](const Product &a, const Product &b)
             { return a.price > b.price; });

        printTop3Table();
    }

    void mostCheap()
    {
        sort(data.begin(), data.end(), [](Product a, Product b)
             { return a.price < b.price; });

        printTop3Table();
    }

    void mostAvailable()
    {
        sort(data.begin(), data.end(), [](Product a, Product b)
             { return a.available > b.available; });

        printTop3Table();
    }

    void mostUnavailable()
    {
        sort(data.begin(), data.end(), [](Product a, Product b)
             { return a.available < b.available; });

        printTop3Table();
    }

    void random()
    {
        cout << "Enter product quanitity: ";
        int quanitity;
        cin >> quanitity;

        int count = 0;
        for (auto &i : data)
        {
            if (i.available >= quanitity)
            {
                ++count;

                cout << "Sell [" << quanitity << "] units of [" << i.name << "] (y/n): ";
                char choice;
                cin >> choice;

                if (choice == 'y')
                {
                    i.available -= quanitity;
                    i.sold += quanitity;
                    cout << "Units sold!" << endl;

                    return;
                }
            }
        }

        cout << "No " << (count ? "more " : "") << "products match the query!" << endl;
    }

    void sum()
    {
        double money;
        cout << "Enter the maximum amount of money available: ";
        cin >> money;

        int count = 0;
        int quantity;
        for (auto &i : data)
        {
            if (i.price <= money)
            {
                count++;
                for (quantity = 1; (double(quantity) * i.price <= money) && (quantity <= i.available); quantity++)
                {
                }
                quantity--;
                if (quantity == 0)
                {
                    continue;
                }
                cout << "Sell [" << quantity << "] units of [" << i.name << "] for [" << i.price * double(quantity) << "] (y/n): ";
                char choice;
                cin >> choice;

                if (choice == 'y')
                {
                    i.available -= quantity;
                    i.sold += quantity;
                    cout << "Units sold! New balance: " << money - i.price * double(quantity) << endl;

                    return;
                }
            }
        }

        cout << "No " << (count ? "more " : "") << "products match the query!" << endl;
    }

     void asorti()
    {
        double money = 0;
        cout << "Enter the available money: ";
        cin >> money;

        vector<Product> asortiData;
        
        sort(data.begin(), data.end(), [](Product a, Product b)
             { return a.price < b.price; });
        Product leastExpensive = data[0];
        int notBought = 0;

        for (int i = 0; i < data.size(); i++) 
        {
            asortiData.push_back(data[i]);
            asortiData[i].sold = 0;
        }

        while (money >= leastExpensive.price && notBought != data.size()) 
        {
            notBought = 0;
            for (int i = 0; i < data.size(); i++) 
            {
                if (data[i].price <= money && data[i].available != 0) 
                {
                    asortiData[i].sold++;
                    money -= data[i].price;
                    data[i].available--;
                    data[i].sold++;
                } 
                else 
                {
                    notBought++;
                }
            }

        }
        cout << "|------------------------------------------------------|" << endl;
        cout << "|" << setw(12) << "Name" << setw(8) << "|" << setw(8) << "Price" << setw(4) << "|" << setw(11) << "Bought" << setw(3) << "|" << endl;
        cout << "|------------------------------------------------------|" << endl;

        for (const auto &i : asortiData)
        {
            if (i.sold != 0) 
            {
                cout << "| " << setw(18) << left << i.name << "| " << setw(10) << left << i.price << "| " << setw(12) << left << i.sold << "|" << right << endl;
            }
        }
        
        cout << "Money left: " << money << endl;
        cout << "|------------------------------------------------------|" << endl;
    }

    int menu()
    {
        cout << "------------------------------------------" << endl;
        cout << "Choose option:" << endl;
        cout << "1 - Add product" << endl;
        cout << "2 - Output all products" << endl;
        cout << "3 - Sell products" << endl;
        cout << "4 - Search product" << endl;
        cout << "5 - Most sold product Top 3" << endl;
        cout << "6 - Least sold product Top 3" << endl;
        cout << "7 - Most profitable product Top 3" << endl;
        cout << "8 - Least profitable product Top 3" << endl;
        cout << "9 - Most expensive product Top 3" << endl;
        cout << "10 - Least expensive product Top 3" << endl;
        cout << "11 - Most available product Top 3" << endl;
        cout << "12 - Least available product Top 3" << endl;
        cout << "13 - Random product" << endl;
        cout << "14 - Max sum" << endl;
        cout << "15 - Asorti" << endl;
        cout << "16 - Stop execution" << endl;
        cout << "------------------------------------------" << endl;
        int op;
        cout << "Choice: ";
        cin >> op;
        return op;
    }
};

int main()
{
    Storage storage;
    int op = 0;
    while (op != 16)
    {
        op = storage.menu();
        switch (op - 1)
        {
        case (Input):
            storage.add();
            break;
        case (Output):
            storage.print();
            break;
        case (Sell):
            storage.sell();
            break;
        case (Search):
            storage.search();
            break;
        case (MostSold):
            storage.mostSold();
            break;
        case (LeastSold):
            storage.leastSold();
            break;
        case (MostEarned):
            storage.mostEarned();
            break;
        case (LeastEarned):
            storage.leastEarned();
            break;
        case (MostExpensive):
            storage.mostExpensive();
            break;
        case (MostCheap):
            storage.mostCheap();
            break;
        case (MostAvailable):
            storage.mostAvailable();
            break;
        case (MostUnavailable):
            storage.mostUnavailable();
            break;
        case (Random):
            storage.random();
            break;
        case (Sum):
            storage.sum();
            break;
        case (Asorti):
            storage.asorti();
            break;
        case (End):
            return 0;
        default:
            cout << "Invalid option!" << endl;
        }
    }

    return 0;
}