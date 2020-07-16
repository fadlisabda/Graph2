//Graph Tidak Berarah Dan Berbobot Dengan Algoritma Kruskal
//proses pencarian nilai Minimum Spanning Tree(MST)
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

class PQ{//mengurutkan lintasan(edge)yang masuk berdasarkan aturan antrean(queue) berprioritas
    public:
        int size;//menentukan ukuran dari antrean yang diinginkan
        edge **add_edge;//variabel array bentukan untuk menyimpan nilai bobot,vertex awal dan vertex tujuan
        int top;//mengetahui panjang dari antrean yang ada

        PQ(int i,int x){ //constructor PQ ini akan aktif jika objek dari class PQ dibuat
            size=i;
            add_edge=new edge*[size];//menentukan batas jumlah array 
            top=x;//menentukan kondisi awal dari antrean
        }

        int isempty(){//mengetahui apakah antrean berapa dalam keadaan kosong atau tidak
            if(top<=0){
                return 1;
            }
            else{
                return 0;
            }
        }    

        void insert(edge *item){//menginput dan mengurutkan seluruh lintasan(edge) yang ada di dalam graph,nantinya akan digunakan untuk menentukan nilai MST
            if(isempty()==1){//ketika antrean berada dalam keadaan kosong 
                add_edge[top++]=item;
            }else{//jika antrian telah terisi sebelumnya
                int i;
                for (i = 0; i < top; i++)
                {
                    if(add_edge[i]->weight=item->weight){//pembandingan nilai
                        break;
                    }
                }
                for (int j = top; j > i; j--)//jika nilai yang dimasukkan lebih kecil
                {
                    add_edge[j]=add_edge[j-1];//pergeseran nilai
                }
                add_edge[i]=item;
                top++;
            }
        }
};

int main(){
    
    return 0;
}