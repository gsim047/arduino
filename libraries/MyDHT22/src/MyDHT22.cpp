#include "MyDHT22.h"

MyDHT22::MyDHT22(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
}

bool MyDHT22::readData() {
  uint8_t byteIdx = 0, bitIdx = 7;
  uint32_t t;

  for (uint8_t i = 0; i < 5; i++) data[i] = 0;

  // Minta data
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(1); // minimum 1ms untuk DHT22
  digitalWrite(_pin, HIGH);
  delayMicroseconds(30);
  pinMode(_pin, INPUT);

  // Tunggu respon DHT22: LOW 80us + HIGH 80us
  t = micros();
  while (digitalRead(_pin) == HIGH)
    if ((micros() - t) > 90) return false;

  t = micros();
  while (digitalRead(_pin) == LOW)
    if ((micros() - t) > 90) return false;

  t = micros();
  while (digitalRead(_pin) == HIGH)
    if ((micros() - t) > 90) return false;

  // Terima 40 bit (5 byte)
  for (uint8_t i = 0; i < 40; i++) {
    while (digitalRead(_pin) == LOW); // tunggu HIGH
    t = micros();
    while (digitalRead(_pin) == HIGH); // tunggu habis HIGH
    if ((micros() - t) > 40) data[byteIdx] |= (1 << bitIdx);
    if (bitIdx == 0) {
      bitIdx = 7;
      byteIdx++;
    } else {
      bitIdx--;
    }
  }

  // Semak checksum
  uint8_t chk = data[0] + data[1] + data[2] + data[3];
  return (chk == data[4]);
}

float MyDHT22::getHumidity() {
  return ((data[0] << 8) | data[1]) * 0.1;
}

float MyDHT22::getTemperature() {
  int16_t raw = ((data[2] & 0x7F) << 8) | data[3];
  float t = raw * 0.1;
  if (data[2] & 0x80) t = -t;
  return t;
}



/*
Kod MyDHT22 yang Fadhil tunjukkan sudah sangat baik dan kemas, dengan beberapa ciri penting sudah ada:

✅ Penstrukturan class modular
✅ Guna uint8_t, int16_t, uint32_t → sesuai untuk semua platform
✅ Proses handshake DHT22 mengikut timing standard
✅ Pengiraan suhu negatif (signed) tepat
✅ Checksum dikira betul
✅ Fungsi getTemperature() dan getHumidity() jelas dan ringan

Namun untuk tahap production atau jika ingin menjadikan ia pustaka rasmi, ada beberapa penambahbaikan kecil boleh dibuat:

⸻

✅ Cadangan Penambahbaikan

1. Pulihkan pinMode selepas pembacaan

Elakkan tinggalkan pin dalam INPUT terbuka:

// Di akhir readData(), selepas return (sama ada berjaya atau gagal)
pinMode(_pin, INPUT_PULLUP);

Ini elak pin ‘floating’ atau ditinggalkan dalam INPUT sahaja.

⸻

2. Debounce tunggu LOW dan HIGH dengan timeout jelas

Contoh:

#define DHT_TIMEOUT 100

// ... dalam loop tunggu
t = micros();
while (digitalRead(_pin) == HIGH) {
  if ((micros() - t) > DHT_TIMEOUT) return false;
}

Sekarang hardcoded 90us — boleh gantikan dengan #define DHT_TIMEOUT 90 di atas supaya mudah ubah nanti.

⸻

3. Sokong retry automatik jika bacaan gagal

Contoh (optional):

bool MyDHT22::read() {
  for (uint8_t i = 0; i < 3; i++) {
    if (readData()) return true;
    delay(10); // tunggu sedikit sebelum cuba semula
  }
  return false;
}


⸻

4. Dokumentasikan format data

Contoh, komen pada fungsi getTemperature():

// Suhu dalam format 16-bit: MSB[7] tanda (-), MSB[6:0] dan LSB untuk nilai x10


⸻

5. Jika digunakan dalam interrupt context (jarang, tapi future-proof)

Pastikan micros() tidak diganggu, atau disable interrupt semasa baca. Tapi ini cuma jika mahu betul-betul stabil dalam aplikasi kritikal.

⸻

✅ Kesimpulan

✅ YA, kod Fadhil sudah stabil dan boleh digunakan untuk projek sebenar.
🛠️ Jika ingin buat versi lebih lasak, hanya perlu tambah sedikit dari segi pengendalian exception, pemulihan pin, dan mungkin retry logic.

Nak saya bantu buat fail .h dan .cpp siap untuk upload ke GitHub? Atau mahu struktur examples/ juga? 
*/
