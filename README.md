# Proyek-UAS
Wands and Sandals - Linked List based Game

Swords and Sandals merupakan game yang menggunakan engine flash dimana 2 karakter melakukan combat dengan konsep turn-based, dimana dapat melakukan 1 aksi dari beberapa pilihan aksi, dengan tujuan membuat HP (Health Points) dari lawan menjadi 0.
Game tersebut merupakan inspirasi dari proyek kami, dimana kami membuat suatu game yang memiliki fondasi yang sama, namun mekanisme yang kami rasa lebih baik dengan implementasi modul dan materi yang sudah diajarkan dalam mata kuliah Algoritma dan Pemrograman

Detail Fitur

Fitur 1 : Memainkan game Wands and Sandals sebagai Player 1 

Fitur 2 : Mengambil input user berupa aksi yang ditampilkan, kemudian membuat projectile yang berupa linked list yang berubah nilai pada setiap waktu, sehingga dapat mengemulasikan pergerakan projectile.

Kebutuhan

C Programming Language
Modular
Array
Linked List
Struct


Keunggulan

Program ini dapat membuat projectile yang sepenuhnya sesuai dengan bentuk yang diinginkan, sebab hanya perlu memilih partikel yang akan muncul pada suatu projectile

User tidak akan mengalami kesulitan dalam navigasi program telah dibuat.

Program ini dapat dibuat agar dapat dimainkan 2 orang, serta membuat AI yang lebih menantang dengan menggunakan script


Untuk mengawali program, kami memanggil beberapa library dan mendefinisikan global variabel.

Kemudian kami membuat 3 tipe data yang penting yaitu arena (“layar yang akan dipakai untuk mendesain arena, karakter, dan projectile), character yaitu struct objek yang digunakan untuk menyimpan informasi character 1 dan 2, serta magic yaitu pembuatan objek linked list yang digunakan untuk membuat projectile dan pergerakannya.

Dua fungsi Arena berguna untuk membuat arena yang dicapai dengan membuat linked list yang terkai dengan 2 character yang akan ditampilkan, kemudian arena dapat berubah jika memanggil fungsi magic agar partikel projectile dapat disertai dalam tampilan tersebut.

Fungsi Arena berguna untuk membuat arena yang dicapai dengan membuat linked list yang terkai dengan 2 character yang akan ditampilkan, kemudian arena dapat berubah jika memanggil fungsi magic agar partikel projectile dapat disertai dalam tampilan tersebut.

Projectile yang akan tertampil dicapai dengan membuat linked list yang mengisi kekosongan layar dengan partikel agar membentuk bentuk projectile yang diinginkan. 

Dua kondisi yang dipaparkan disini bergantungan dengan apakah fungsi yang memanggil createMagic berasal dari karakter 1 atau 2, sehingga posisi awal dari projectile dapat sesuai dengan karakter yang menembaknya.

Disini pemain dapat mengambil keputusan untuk action yang ingin diambil apa saja, dan bagaimana permainan membatasi pemain dengan AP (action points), serta bagaiman damage dan HP berinteraksi satu sama lain.

Disini terdapat pemanggilan pembuatan dan pergerakkan projectile sesuai dengan actionnya, misalkan pada serangan Fireball, maka akan membuat projectile fireball, dan seterusnya.

Programmer dapat memilih apakah pemain kedua berupa AI yang dibuat sendiri atau melawan orang lain.

Jika memutuskan dengan menggunakan AI, maka sejauh ini kami masih menggunakan RNG (random number generator) untuk memilih suatu action, namun jika kita ingin membuat AI yang lebih advanced, maka kita dapat membuat script atau machine learning agar menjadi tantangan yang menantang.
