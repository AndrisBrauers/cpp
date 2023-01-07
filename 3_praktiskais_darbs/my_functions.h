#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

#define PRODUCT_NAME_L 100

struct Product{
    char name[PRODUCT_NAME_L];
    float price;
    int available; 
    int sold;
};

void print(const Product *pr) {
    cout << "\nProdukta nosaukums: " << pr->name << endl;
    cout << "Produkta cena: " << pr->price << endl;
    cout << "Produkta pieejamais daudzums: " << pr->available << endl;
    cout << "Produkta pārdotais daudzums: " << pr->sold << endl << endl;
}

bool compareBySold(const Product &a, const Product &b) {
    return a.sold < b.sold;
}

bool compareByProfit(const Product &a, const Product &b) {
    return a.sold * a.price < b.sold * b.price;
}

bool compareByPrice(const Product &a, const Product &b) {
    return a.price < b.price;
}

int fillTop3(Product *top, const string file) {
    int length = 0;
    fstream f;
    f.open(file, ios::in |ios::binary);

    if (f.is_open()) {
        f.seekg (0, ios::end);
        length = f.tellg();
        f.seekg (0, ios::beg);

        for (int i = 0; i < length / sizeof(Product) && i < 3; i++) {
            f.read(reinterpret_cast<char *>(&top[i]), sizeof(Product));
        }
    } else {
        cout << "ERROR\n";
    }
    f.close();
    return length;
}

int findProduct(fstream &f, const char *name) {
    char buffer[PRODUCT_NAME_L];
    int retVal = -1;

    f.seekg (0, ios::end);
    int length = f.tellg();
    f.seekg (0, ios::beg);

    for (int i = 0; i < length; i += sizeof(Product)) {
        f.read(buffer, PRODUCT_NAME_L);
        if (!strcmp(name, buffer)) {
            retVal = f.tellg();
            break;
        } else {
            f.seekg(sizeof(float) + sizeof(int) * 2, ios::cur);
        }
    }
    return retVal;
}

void addProduct(const string file) {
    char productName[PRODUCT_NAME_L];
    cout << "Kuru produktu papildināt: ";
    cin.ignore();
    cin.get(productName, PRODUCT_NAME_L);

    fstream shopFile;
    shopFile.open(file, ios::out | ios::in |ios::binary | ios::ate);

    if (shopFile.is_open()) {
        int pos = findProduct(shopFile, productName);
        if (pos > -1) {
            cout << productName << " - Par cik vienībām papildināt skaitu: ";
            int toAdd;
            int curVol;
            cin >> toAdd;
            shopFile.seekg(pos + sizeof(float), ios::beg);
            shopFile.read(reinterpret_cast<char *>(&curVol), sizeof(int));
            toAdd += curVol;
            shopFile.seekp(pos + sizeof(float), ios::beg);
            shopFile.write(reinterpret_cast<char *>(&toAdd), sizeof(int));
        } else {
            Product prod;
            cout << "Produkts vēl neeksistē. Ievadi visus parametrus.\n";
            strcpy(prod.name, productName);
            cout << productName << " - Cena: ";
            cin >> prod.price;
            cout << productName << " - Pieejamais daudzums: ";
            cin >> prod.available;
            cout << productName << " - Pārdotais daudzums: ";
            cin >> prod.sold;

            shopFile.seekp(0, ios::end);
            shopFile.write(reinterpret_cast<char *>(&prod), sizeof(Product));
        }
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void printAll(const string file) {
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        shopFile.seekg (0, ios::end);
        int length = shopFile.tellg();
        shopFile.seekg (0, ios::beg);

        Product prod;

        for (int i = 0; i < length; i += sizeof(Product)) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            print(&prod);
        }   
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void sellProduct(const string file) {
    char productName[PRODUCT_NAME_L];
    cout << "Kuru produktu pārdot: ";
    cin.ignore();
    cin.get(productName, PRODUCT_NAME_L);

    fstream shopFile;
    shopFile.open(file, ios::out | ios::in |ios::binary);

    if (shopFile.is_open()) {
        int pos = findProduct(shopFile, productName);
        if (pos > -1) {
            int curVol;
            int curSold;
            shopFile.seekg(pos + sizeof(float), ios::beg);
            shopFile.read(reinterpret_cast<char *>(&curVol), sizeof(int));
            shopFile.seekg(pos + sizeof(float) + sizeof(int), ios::beg);
            shopFile.read(reinterpret_cast<char *>(&curSold), sizeof(int));
            if (curVol <= 0) {
                cout << productName << " - Vairāk nav\n";
            } else {
                curVol--;
                curSold++;
                shopFile.seekp(pos + sizeof(float), ios::beg);
                shopFile.write(reinterpret_cast<char *>(&curVol), sizeof(int));
                shopFile.seekp(pos + sizeof(float) + sizeof(int), ios::beg);
                shopFile.write(reinterpret_cast<char *>(&curSold), sizeof(int));
            }
        } else {
            cout << productName << " - Produkts neeksistē\n";
        }
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void printProduct(const string file) {
    char productName[PRODUCT_NAME_L];
    cout << "Kura produkta datus izvadit: ";
    cin.ignore();
    cin.get(productName, PRODUCT_NAME_L);

    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        int pos = findProduct(shopFile, productName);
        Product prod;
        shopFile.seekg(pos - PRODUCT_NAME_L, ios::beg);
        shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));

        print(&prod);
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void top3Sold(const string file) {
    Product top3[3];
    int length = fillTop3(top3, file);
    sort(top3, top3 + (sizeof(top3) / sizeof(Product)), &compareBySold);

    if (length / sizeof(Product) <= 3) {
        for (int i = 0; i < length / sizeof(Product); i++) {
            print(&top3[i]);
        }
        return;
    }
    
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        Product prod;
        shopFile.seekg(sizeof(Product) * 3, ios::beg);

        for (int i = 3; i < length / sizeof(Product); i++) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            if (prod.sold > top3[0].sold) {
                if (prod.sold > top3[1].sold) {
                    if (prod.sold > top3[2].sold) {
                        top3[0] = top3[1];
                        top3[1] = top3[2];
                        top3[2] = prod; 
                    } else {
                        top3[0] = top3[1];
                        top3[1] = prod; 
                    }
                } else {
                    top3[0] = prod;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            print(&top3[i]);
        }
        
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void least3Sold(const string file) {
    Product top3[3];
    int length = fillTop3(top3, file);
    sort(top3, top3 + (sizeof(top3) / sizeof(Product)), &compareBySold);

    if (length / sizeof(Product) <= 3) {
        for (int i = 0; i < length / sizeof(Product); i++) {
            print(&top3[i]);
        }
        return;
    }
    
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        Product prod;
        shopFile.seekg(sizeof(Product) * 3, ios::beg);

        for (int i = 3; i < length / sizeof(Product); i++) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            if (prod.sold < top3[2].sold) {
                if (prod.sold < top3[1].sold) {
                    if (prod.sold < top3[0].sold) {
                        top3[2] = top3[1];
                        top3[1] = top3[0];
                        top3[0] = prod; 
                    } else {
                        top3[2] = top3[1];
                        top3[1] = prod; 
                    }
                } else {
                    top3[2] = prod;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            print(&top3[i]);
        }
        
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void top3Profitable(const string file) {
    Product top3[3];
    int length = fillTop3(top3, file);
    sort(top3, top3 + (sizeof(top3) / sizeof(Product)), &compareByProfit);

    if (length / sizeof(Product) <= 3) {
        for (int i = 0; i < length / sizeof(Product); i++) {
            print(&top3[i]);
        }
        return;
    }
    
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        Product prod;
        shopFile.seekg(sizeof(Product) * 3, ios::beg);

        for (int i = 3; i < length / sizeof(Product); i++) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            if (prod.sold * prod.price > top3[0].sold * top3[0].price) {
                if (prod.sold * prod.price > top3[1].sold * top3[1].price) {
                    if (prod.sold * prod.price > top3[2].sold * top3[2].price) {
                        top3[0] = top3[1];
                        top3[1] = top3[2];
                        top3[2] = prod; 
                    } else {
                        top3[0] = top3[1];
                        top3[1] = prod; 
                    }
                } else {
                    top3[0] = prod;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            print(&top3[i]);
        }
        
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void least3Profitable(const string file) {
    Product top3[3];
    int length = fillTop3(top3, file);
    sort(top3, top3 + (sizeof(top3) / sizeof(Product)), &compareByProfit);

    if (length / sizeof(Product) <= 3) {
        for (int i = 0; i < length / sizeof(Product); i++) {
            print(&top3[i]);
        }
        return;
    }
    
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        Product prod;
        shopFile.seekg(sizeof(Product) * 3, ios::beg);

        for (int i = 3; i < length / sizeof(Product); i++) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            if (prod.sold * prod.price < top3[2].sold * top3[2].price) {
                if (prod.sold * prod.price < top3[1].sold * top3[1].price) {
                    if (prod.sold * prod.price < top3[0].sold * top3[0].price) {
                        top3[2] = top3[1];
                        top3[1] = top3[0];
                        top3[0] = prod; 
                    } else {
                        top3[2] = top3[1];
                        top3[1] = prod; 
                    }
                } else {
                    top3[2] = prod;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            print(&top3[i]);
        }
        
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void top3Expensive(const string file) {
    Product top3[3];
    int length = fillTop3(top3, file);
    sort(top3, top3 + (sizeof(top3) / sizeof(Product)), &compareByPrice);

    if (length / sizeof(Product) <= 3) {
        for (int i = 0; i < length / sizeof(Product); i++) {
            print(&top3[i]);
        }
        return;
    }
    
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        Product prod;
        shopFile.seekg(sizeof(Product) * 3, ios::beg);

        for (int i = 3; i < length / sizeof(Product); i++) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            if (prod.price > top3[0].price) {
                if (prod.price > top3[1].price) {
                    if (prod.price > top3[2].price) {
                        top3[0] = top3[1];
                        top3[1] = top3[2];
                        top3[2] = prod; 
                    } else {
                        top3[0] = top3[1];
                        top3[1] = prod; 
                    }
                } else {
                    top3[0] = prod;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            print(&top3[i]);
        }
        
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}

void least3Expensive(const string file) {
    Product top3[3];
    int length = fillTop3(top3, file);
    sort(top3, top3 + (sizeof(top3) / sizeof(Product)), &compareByPrice);

    if (length / sizeof(Product) <= 3) {
        for (int i = 0; i < length / sizeof(Product); i++) {
            print(&top3[i]);
        }
        return;
    }
    
    fstream shopFile;
    shopFile.open(file, ios::in |ios::binary);

    if (shopFile.is_open()) {
        Product prod;
        shopFile.seekg(sizeof(Product) * 3, ios::beg);

        for (int i = 3; i < length / sizeof(Product); i++) {
            shopFile.read(reinterpret_cast<char *>(&prod), sizeof(Product));
            if (prod.price < top3[2].price) {
                if (prod.price < top3[1].price) {
                    if (prod.price < top3[0].price) {
                        top3[2] = top3[1];
                        top3[1] = top3[0];
                        top3[0] = prod; 
                    } else {
                        top3[2] = top3[1];
                        top3[1] = prod; 
                    }
                } else {
                    top3[2] = prod;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            print(&top3[i]);
        }
        
    } else {
        cout << "ERROR\n";
    }
    shopFile.close();
}
