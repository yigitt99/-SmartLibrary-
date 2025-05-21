#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"
#include <thread>


using namespace std::this_thread;
using namespace std::chrono;
using json = nlohmann::json;
using namespace std;

// Kitap bilgilerini tutacak struct
struct Book {
    int kitap_no;
    string isbn;
    string baslik;
    string yazar;
};


// Kullanıcı bilgilerini temsil eden struct
struct Kullanici {
    int kullanici_no;
    string ad;
    string sifre;
    string rol;
};


vector<Kullanici> loadUsersFromJson(const string& filename) {
    vector<Kullanici> users;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "users.json dosyası açılamadı!" << endl;
        return users;
    }

    json j;
    file >> j;

    for (const auto& item : j) {
        Kullanici u;
        u.kullanici_no = item["kullanici_no"];
        u.ad = item["ad"];
        u.sifre = item["sifre"];
        u.rol = item["rol"];
        users.push_back(u);
    }

    return users;
}

void clear();
void intro();
bool login(bool& isAdmin);
bool isAdminLogin();
void normalMenu(bool isAdmin);

void intro() {
    cout << "\n\t##      ## ####### ##      ######  ###### ####  #### #######";
    cout << "\n\t##      ## ##      ##      ##      ##  ## ##  ##  ## ##       ";
    cout << "\n\t##  ##  ## #####   ##      ##      ##  ## ##  ##  ## #####      ";
    cout << "\n\t##  ##  ## ##      ##      ##      ##  ## ##      ## ##           ";
    cout << "\n\t####  #### ####### ####### ######  ###### ##      ## #######     ";
    cout << "\n\n\t\t\t         !!!!!!!  !!!!!        ";
    cout << "\n\t\t\t           !!     !   !      ";
    cout << "\n\t\t\t           !!     !!!!!    ";

    cout << "\n\n\n\t\t********  LIBRARY   PROJECT  *******";
    cout << "\n\t\t====================================";
    cout << "\n\n\t\t\t  MADE BY  :-";
    cout << "\n\n\t\t\t  YIGIT EFE KILIC  ";
    cout << " \n\n\n\t\t         Press any KEY to continue... ";
    cin.get();
    clear();

}

void clear() {
	system("cls"); // Clear the console screen (Windows)
}

// Admin giriş kontrolü
bool isAdminLogin() {
    string adminUser = "admin";
    string adminPassword = "admin123";
    string username, password;

    cout << "\n\tAdmin Girisi:\n";
    cout << "\tKullanici adi: ";
    cin >> username;
    cout << "\tSifre: ";
    cin >> password;

    return (username == adminUser && password == adminPassword);
}

//Kullanıcı giriş fonksiyonu
bool login(bool& isAdmin) {
    vector<Kullanici> kullanicilar = loadUsersFromJson("users.json");

    string girilenAd, girilenSifre;

    do {
        clear();
        cout << "\n\t\t\t\t\t---------------------------------------------";
        cout << "\n\t\t\t\t\t|                                           |";
        cout << "\n\t\t\t\t\t|               W E L C O M E               |";
        cout << "\n\t\t\t\t\t|                                           |";
        cout << "\n\t\t\t\t\t---------------------------------------------";

        cout << "\n\n\n\t\t\t\t\t\tKullanici adinizi girin: ";
        cin >> girilenAd;

        cout << "\n\n\t\t\t\t\t\tSifrenizi girin: ";
        cin >> girilenSifre;

        for (const auto& k : kullanicilar) {
            if (k.ad == girilenAd && k.sifre == girilenSifre) {
                clear();
                cout << "\n\t\t\t\t\t---------------------------------------------";
                cout << "\n\t\t\t\t\t|               P L E A S E                 |";
                cout << "\n\t\t\t\t\t|                                           |";
                cout << "\n\t\t\t\t\t|                   W A I T . . .           |";
                cout << "\n\t\t\t\t\t---------------------------------------------";

                cout << "\033[32m\n\t\t\t\t\t    Giris basarili. Hosgeldiniz, " << girilenAd << "!\033[0m" << endl;
                cout << "\n\t\t\t\t\tLutfen Bekleyin Menuye Aktariliyorsunuz...";
                sleep_for(seconds(1));

                // Admin kontrolü
                isAdmin = (k.rol == "admin");
                return true; // Başarılı giriş
            }
        }

        // Hatalı giriş
        clear();
        cout << "\n\t\t\t\t\t\033[31m    Hatali Giris! Lutfen tekrar deneyin.\033[0m" << endl;
        sleep_for(seconds(1));

    } while (true); // Doğru giriş yapılana kadar döngü devam eder
}

void normalMenu(bool isAdmin) {
    int choice;
    do
    {
        clear();

        cout << "\n\n\n\tANA MENU";
        cout << "\n\n\t1. Kitap Odunc Al";
        cout << "\n\n\t2. ISBN DOGRULAMA";
        cout << "\n\n\t3. IADE ISLEMLERI";

        if (isAdmin) {
            cout << "\n\n\t4. Admin Menusune Git";
        }

        cout << "\n\n\t(5) CIKIS";
        cout << "\n\n\tLutfen 1 ile 4 arasinda bir sayi giriniz: ";
        cin >> choice;

        if (choice < 1 || choice > 5) {
            cout << "\n\n\tGecersiz secim! Lutfen tekrar deneyin.\n";
            cin.ignore();
            cin.get();
            continue;
        }

        switch (choice) {
            
        }
    } while (choice != 5);
    }

int main()
{
    intro();

	bool isAdmin = false;

    login(isAdmin);

	normalMenu(isAdmin);

    return 0;
}