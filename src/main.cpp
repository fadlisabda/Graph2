//Graph Tidak Berarah Dan Berbobot Dengan Algoritma Kruskal
#include <iostream>
using namespace std;

//vertex merupakan himpunan node atau titik pada sebuah graph
//edge adalah garis yang menghubungkan tiap vertex pada sebuah graph
//adjacent dua buah vertex berdekatan(adjacent) dan terhubung  dengan satu garis
//cycle siklus atau sirkuit yaitu lintasan yang berawal dan berakhir pada simpul yang sama
//weight bobot nilai yang dimiliki oleh sebuah lintasan(edge)antara dua buah vertex yang terhubung

class vertex{//akan digunakan sebagai representasi objek vertex atau node didalam sebuah graph.
    public:
        char lab;//karakter nama dari vertex yang bersangkutan.
        vertex *parent;//digunakan untuk menelusuri alamat vertex yang belum dilewati.
        int rank;
        vertex(char l){//nantinya akan digunakan ketika tiap vertex dibuat di dalam class graph.
            lab=l;
        }
};

class edge{//menetapkan jalur(path)
    public:
        int start;//nilai index vertex awal
        int weight;//nilai bobot lintasan
        int end;//index vertex tujuan
        //objek dari class edge akan dibuat pada class priority_Q;
        edge(int s,int e,int w){
            start=s;
            end=e;
            weight=w;
        }
};


int main(){
    
    return 0;
}