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
    string kota;//karakter nama kota dari vertex yang bersangkutan.
    vertex *parent;//digunakan untuk menelusuri alamat vertex yang belum dilewati.
    int rank;//tiap vertex diambil sebagai sebuah lintasan(edge)yang berpasangan
    vertex(char l,string k){//nantinya akan digunakan ketika tiap vertex dibuat di dalam class graph.
        lab=l;
        kota=k;
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
                if(add_edge[i]->weight>=item->weight){//pembandingan nilai
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

class graph{//class utama yang memanggil class pendukung lainnya,mendefinisikan method-method utama dalam membuat algoritma kruskal
public:
    //variabel array dua dimensi dan pointer
    vertex **addvertex;//objek untuk tiap vertex yang dibuat didalam graph
    int **add_adjacent;//menghubungkan dua vertex yang saling terhubung
    int nvert,addjacent;

    //prototype fungsi public untuk menjalankan algoritma kruskal
    void Addvertex(char v,string kota);
    void addedge(int s,int e,int w);
    void kruskal();

    graph(){//yang akan dipanggil lewat fungsi main()
        addvertex=new vertex*[20];
        add_adjacent=new int*[20];
        for (int i = 0; i < 20; i++)
        {
            add_adjacent[i]=new int[20];
            for (int j = 0; j < 20; j++)
            {
                add_adjacent[i][j]=1000000;
            }   
        }
        x=new PQ(200,0);
        nvert=0;
        addjacent=0;
    }

    //prototype fungsi private untuk menjalankan algoritma kruskal
    private:
        void makeset(vertex *v);
        void displayvert(int v);
        void displayvertex(int v);
        vertex *findset(vertex *v);
        void uni(vertex *x,vertex *y);
        void link(vertex *x,vertex *y);
        PQ *x;
};

void graph::Addvertex(char lab,string k){//menginputkan vertex yang dibuat dalam graph
addvertex[nvert++]=new vertex(lab,k);//menginputkan vertex dengan nama karakter char lab kedalam array vertex **Addvertex,nvert++ akan menunjukkan indeks dari array tersebut
}

void graph::addedge(int st,int end,int w){//menghubungkan vertex-vertex yang ada didalam graph berdasarkan nilai indeksnya
//vertex asal maupun vertex tujuan dibuat sama karena graph yang dibuat graph yang tidak berarah dan tidak berbobot
this->add_adjacent[st][end]=w;
this->add_adjacent[end][st]=w;
addjacent++;

edge *path=new edge(st,end,w);//objek edge *path yang berisi nilai indeks vertex awal,vertex tujuan,serta nilai bobotnya
x->insert(path);//nilai dari objek edge*path dimasukkan kedalam antrian berprioritas digunakan untuk proses pengerjaan algoritma kruskal
}

//menampilkan nilai vertex dari hasil penelusuran pada algoritma kruskal
void graph::displayvert(int v){//nilai integer dari argument inputan digunakan untuk menampilkan vertex kota
cout<<addvertex[v]->kota;
}

//menampilkan nilai vertex dari hasil penelusuran pada algoritma kruskal
void graph::displayvertex(int v){//nilai integer dari argument inputan digunakan untuk menampilkan vertex
cout<<addvertex[v]->lab<<"";
}

//mengondisikan seluruh vertex yang ada di dalam graph ke kondisi keadaan awal(belum di telusuri)
void graph::makeset(vertex *v){//nilai argument dari variabel vertex *v yang berisi nilai int rank dan vertex *parent dikondisikan dalam keadaan normal
v->parent=v;
v->rank=0;
}

vertex* graph::findset(vertex *v){//mengaplikasikan algoritma kruskal dan berfungsi untuk mendeteksi apabila dua node yang akan dihubungkan membentuk sebuah looping tertutup
if(v != v->parent){//akan mengeksekusi perintah rekursif didalamnya sampai ditemukan nilai root dari node yang diinginkan(atau nilai v == v->parent)
    v->parent=findset(v->parent);
}
return v->parent;
}

//menginputkan nilai vertex kedalam tree,dimana tiap node yang berada didalam tree akan merujuk ke root yang sama
void graph::link(vertex *x,vertex *y){//akan menghubungkan kedua vertex pada parameter argument dan menginputkannya kedalam tree
if (x->rank > y->rank)//jika nilai rank vertex*x lebih besar
{
    y->parent=x;//vertex x sebagai parent dari vertex *y
}else{//jika nilai rank vertex*x lebih kecil
    x->parent=y;//vertex *y sebagai parent dari vertex *x
    if (x->rank == y->rank)
    {
        y->rank=y->rank+1;//nilai rank dari vertex y akan ditambah1
    }
}
}

void graph::uni(vertex *x,vertex *y){//menghubungkan kedua vertex yang memiliki root yang berbeda(tidak membentuk looping)
link(findset(x),findset(y));//memanggil method link
}

void graph::kruskal(){//method utama untuk menjalankan algoritma kruskal dan akan memeanggil method-method lain
int total=0;
//mengkondisikan semua vertex dalam keadaan netral(belum digunakan) dengan cara memanggil makeset(vertex*v)
for (int i = 0; i < nvert; i++)//semua vertex yang berada didalam graph dikondisikan dalam keadaan belum ditelusuri
{
    makeset(addvertex[i]);
}

//mengambil edge(lintasan) dari kecil ke besar yang telah diurutkan kedalam antrean berprioritas
for (int i = 0; i < addjacent; i++)
{
    //mengambil nilai dari vertex awal dan vertex tujuan
    int start=x->add_edge[i]->start;//vertel awal
    int end=x->add_edge[i]->end;//vertex tujuan
    //mencari nilai root dari masing masing vertex,jika root kedua vertex sama lintasan tersebut diabaikan
    vertex *a;
    a=findset(addvertex[start]);//mencari nilai root
    vertex *b;
    b=findset(addvertex[end]);//mencari nilai root

    //memasukkan nilai kedua vertex tersebut kedalam tree artinya lintasan tersebut dapat diambil sebagai bagian dari MST
    if (a->lab != b->lab)//jika root berbeda,perintah if bernilai true
    {
        uni(addvertex[start],addvertex[end]);
        displayvert(start);
        cout<<"-";
        displayvert(end);
        cout<<"(";
        displayvertex(start);
        displayvertex(end);
        cout<<")";
        //cout<<add_adjacent[start][end]<<" "; untuk melihat nilai bobot
        total=total+this->add_adjacent[start][end];
    }
}
    cout<<endl;
    cout<<"Nilai Total keseluruhan MST :"<<total;
}

int main(){//memanggil method method yang telah kita bahas sebelumnya
cout<<"Implementation of graph using kruskal algorithm"<<endl<<endl;
graph *a=new graph();

//create vertex
    a->Addvertex('A',"dompu");//0
    a->Addvertex('B',"Mataram");//1
    a->Addvertex('C',"denpasar");//2
    a->Addvertex('D',"banyuwangi");//3
    a->Addvertex('E',"surabaya");//4
    a->Addvertex('F',"Yogyakarta");//5
    a->Addvertex('G',"semarang");//6
    a->Addvertex('H',"Jakarta");//7
    a->Addvertex('I',"Bandung");//8

//create graph yang akan diimplementasikan dengan menggunakan algoritma kruskal
    a->addedge(0,3,8);//AD //digunakan untuk menghubungkan antarvertex yang satu dengan vertex yang lain
    a->addedge(0,1,6);//AB
    a->addedge(1,2,1);//BC
    a->addedge(1,3,10);//BD
    a->addedge(2,6,20);//CG
    a->addedge(2,5,15);//CF
    a->addedge(2,3,21);//CD
    a->addedge(3,4,14);//DE
    a->addedge(4,5,3);//EF
    a->addedge(4,7,5);//EH
    a->addedge(5,7,11);//FH
    a->addedge(6,7,13);//GH
    a->addedge(6,8,18);//GI
    a->addedge(7,8,17);//HI

    a->kruskal();
return 0;
}