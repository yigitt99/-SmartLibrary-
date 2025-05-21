#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

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
int main()
{

}