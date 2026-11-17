#include <iostream>

using namespace std;

struct NodeQueue
{
  int kode;
  string nama;
  NodeQueue *next;
};

struct NodeStack
{
  int kode;
  string nama;
  NodeStack *next;
};

struct NodeTree
{
  int kode;
  string nama;
  NodeTree *kiri;
  NodeTree *kanan;
};

NodeQueue *front = nullptr;
NodeQueue *last = nullptr;
NodeStack *top = nullptr;
NodeTree *root = nullptr;

// menu handler
void tambah_energi();
void lihat_antrean_energi();
void proses_energi();
void lihat_energi_terserap();
void hapus_energi_teratas();
void cari_energi();
void lihat_isi_organ();
void gunakan_energi();

// tree
NodeTree *tambah_tree(NodeTree *root, int kode, string nama);
NodeTree *cari_tree(NodeTree *root, int kode);
NodeTree *hapus_tree(NodeTree *root, int kode);

// bst
void preorder(NodeTree *root, int &no);
void inorder(NodeTree *root, int &no);
void postorder(NodeTree *root, int &no);

// stack
void push(int kode, string nama);
void pop();

// utils
void tahan_layar();

int main()
{
  char menu = '0';
  while (menu != '9')
  {
    system("cls");
    cout << "=== Sistem Orgen Inti Nirwana ===" << endl
         << endl
         << "1. Tambah Energi" << endl
         << "2. Lihat Energi dalam Antrean" << endl
         << "3. Proses Energi" << endl
         << "4. Lihat Energi Yang Sudah Terserap" << endl
         << "5. Hapus Riwayat Energi Teratas" << endl
         << "6. Cari Energi di Organ" << endl
         << "7. Lihat isi organ" << endl
         << "8. Gunakan Energi" << endl
         << "9. Keluar" << endl
         << endl;

    cout << "Masukkan pilihan anda: ";

    cin >> menu;

    switch (menu)
    {
    case '1':
    {
      char tambahEnergi = 'y';
      while (tambahEnergi == 'y' || tambahEnergi == 'Y')
      {
        tambah_energi();
        cout << "Apakah anda ingin menambahkan energi lagi? (y/n): ";
        cin >> tambahEnergi;
      }
      break;
    }
    case '2':
    {
      lihat_antrean_energi();
      tahan_layar();
      break;
    }

    case '3':
    {
      proses_energi();
      tahan_layar();
      break;
    }

    case '4':
    {
      lihat_energi_terserap();
      tahan_layar();
      break;
    }

    case '5':
    {
      hapus_energi_teratas();
      tahan_layar();
      break;
    }

    case '6':
    {
      cari_energi();
      tahan_layar();
      break;
    }

    case '7':
    {
      lihat_isi_organ();
      tahan_layar();
      break;
    }

    case '8':
    {
      gunakan_energi();
      tahan_layar();
      break;
    }

    default:
      break;
    }
  }
}

// menu handler
void gunakan_energi()
{
  if (root == nullptr)
  {
    cout << "Isi organ masih kosong!" << endl
         << endl;
    return;
  }

  int kode;
  cout << "Masukkan kode energi: ";
  cin >> kode;
  if (cin.fail() || kode <= 0)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Kode energi harus berupa angka dan lebih dari nol!" << endl
         << endl;
    return;
  }

  NodeTree *hasil = cari_tree(root, kode);
  if (hasil == nullptr)
  {
    cout << "Energi dengan kode " << kode << " tidak ditemukan!" << endl
         << endl;
    return;
  }

  cout << "Energi " << hasil->nama << "telah digunakan!" << endl;
  root = hapus_tree(root, kode);
}

void lihat_isi_organ()
{
  if (root == nullptr)
  {
    cout << "Isi organ masih kosong!" << endl
         << endl;
    return;
  }

  char pil;
  int no = 1;

  cout << "=== Isi Kristal Organ ===" << endl
       << endl
       << "1. Pre-order" << endl
       << "2. In-order" << endl
       << "3. Post-order" << endl
       << endl
       << "Masukkan pilihan anda: ";

  cin >> pil;
  switch (pil)
  {
  case '1':
    preorder(root, no);
    break;
  case '2':
    inorder(root, no);
    break;
  case '3':
    postorder(root, no);
    break;
  default:
    break;
  }
}

void cari_energi()
{
  if (root == nullptr)
  {
    cout << "Energi dalam organ masih kosong!" << endl
         << endl;
    return;
  }
  int kode;
  cout << "Masukkan kode energi: ";
  cin >> kode;

  if (cin.fail() || kode <= 0)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Kode energi harus berupa angka dan lebih dari nol!" << endl
         << endl;
    return;
  }

  NodeTree *hasil = cari_tree(root, kode);
  if (hasil == nullptr)
  {
    cout << "Energi tidak ditemukan" << endl
         << endl;
    return;
  }

  cout << "Ditemukan: " << "[" << hasil->kode << "] " << hasil->nama << endl
       << endl;
}

void hapus_energi_teratas()
{
  if (top == nullptr)
  {
    cout << "Riwayat energi masih kosong!" << endl
         << endl;
    return;
  }

  NodeStack *del = top;

  top = del->next;
  cout << "Riwayat energi " << del->nama << " telah dihapus!" << endl;
  delete top;
}

void lihat_energi_terserap()
{
  if (top == nullptr)
  {
    cout << "Belum ada energi yang terserap!" << endl
         << endl;

    return;
  }

  cout << "=== Energi Yang Sudah Terserap ===" << endl;
  int no = 1;
  for (NodeStack *s = top; s != nullptr; s = s->next)
  {
    cout << no << ". " << "[" << s->kode << "] " << s->nama << endl;
    no++;
  }
}

void proses_energi()
{
  if (front == nullptr)
  {
    cout << "Antrean energi masih kosong!" << endl
         << endl;
    return;
  }

  NodeQueue *del = front;
  push(del->kode, del->nama);
  root = tambah_tree(root, del->kode, del->nama);
  cout << "Berhasil memproses energi " << del->nama << "!" << endl
       << endl;

  front = del->next;
  if (front == nullptr)
    last = nullptr;
  delete del;
}

void lihat_antrean_energi()
{
  if (front == nullptr)
  {
    cout << "Antrean energi masih kosong!" << endl
         << endl;
    return;
  }

  cout << "=== Energi Dalam Antrean ===" << endl;
  int no = 1;
  // for (NodeQueue *q = front; q != nullptr; q = q->next)
  // {
  //   cout << no << ". " << "[" << q->kode << "] " << q->nama << endl;
  //   no++;
  // }

  NodeQueue *q = front;
  while (q != nullptr)
  {
    cout << no << ". " << "[" << q->kode << "] " << q->nama << endl;
    no++;
    q = q->next;
  }

  cout << endl;
}

void tambah_energi()
{
  int kode = 0;
  string nama = "";

  cout << "Masukkan kode energi: ";
  cin >> kode;

  if (cin.fail() || kode <= 0)
  {
    cout << "Kode energi harus berupa angka dan lebih dari nol!" << endl
         << endl;
    return;
  }

  for (NodeQueue *q = front; q != nullptr; q = q->next)
  {
    if (q->kode == kode)
    {
      cout << "Kode energi sudah digunakan!" << endl
           << endl;
      return;
    }
  }

  for (NodeStack *s = top; s != nullptr; s = s->next)
  {
    if (s->kode == kode)
    {
      cout << "Kode energi sudah digunakan!" << endl
           << endl;
      return;
    }
  }

  cout << "Masukkan nama energi: ";
  cin.ignore();
  getline(cin, nama);

  if (nama.empty())
  {
    cout << "Nama energi tidak boleh kosong!" << endl;
    return;
  }

  NodeQueue *newNode = new NodeQueue{kode, nama, nullptr};

  if (front == nullptr)
    front = last = newNode;
  else
  {
    last->next = newNode;
    last = newNode;
  }

  cout << "Berhasil memasukkan energi!" << endl
       << endl;
}

// bst
void preorder(NodeTree *root, int &no)
{
  if (root == nullptr)
    return;
  cout << no << ". [" << root->kode << "] " << root->nama << endl;
  no++;
  preorder(root->kiri, no);
  preorder(root->kanan, no);
};

void inorder(NodeTree *root, int &no)
{
  if (root == nullptr)
    return;
  inorder(root->kiri, no);
  cout << no << ". [" << root->kode << "] " << root->nama << endl;
  no++;
  inorder(root->kanan, no);
};

void postorder(NodeTree *root, int &no)
{
  if (root == nullptr)
    return;
  postorder(root->kiri, no);
  postorder(root->kanan, no);
  cout << no << ". [" << root->kode << "] " << root->nama << endl;
  no++;
};

// stack
void push(int kode, string nama)
{
  NodeStack *newNode = new NodeStack{kode, nama, top};
  top = newNode;
}
void pop()
{
  if (top == nullptr)
    return;
  NodeStack *del = top;
  top = top->next;
  delete del;
}

// tree
NodeTree *tambah_tree(NodeTree *root, int kode, string nama)
{
  if (root == nullptr)
    return new NodeTree{kode, nama, nullptr, nullptr};
  if (kode < root->kode)
    root->kiri = tambah_tree(root->kiri, kode, nama);
  else
    root->kanan = tambah_tree(root->kanan, kode, nama);

  return root;
}

NodeTree *cari_tree(NodeTree *root, int kode)
{
  if (root == nullptr || root->kode == kode)
    return root;
  if (kode < root->kode)
    return cari_tree(root->kiri, kode);
  return cari_tree(root->kanan, kode);
}

NodeTree *hapus_tree(NodeTree *root, int kode)
{
  if (root == nullptr)
    return nullptr;
  if (kode < root->kode)
  {
    root->kiri = hapus_tree(root->kiri, kode);
  }
  else if (kode > root->kode)
  {
    root->kanan = hapus_tree(root->kanan, kode);
  }
  else if (root->kanan == nullptr)
  {
    NodeTree *sisa = root->kanan;
    delete root;
    return sisa;
  }
  else if (root->kiri == nullptr)
  {
    NodeTree *sisa = root->kiri;
    delete root;
    return sisa;
  }
  else
  {
    NodeTree *pengganti = root->kanan;
    while (pengganti->kiri != nullptr)
      pengganti = pengganti->kiri;
    root->kode = pengganti->kode;
    root->nama = pengganti->nama;
    root->kanan = hapus_tree(root->kanan, pengganti->kode);
  }

  return root;
}

// utils
void tahan_layar()
{
  cout << "Tekan ENTER untuk melanjutkan...";
  cin.get();
  cin.ignore(1000, '\n');
}