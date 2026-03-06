#include <stdio.h>
#include <string.h>
#include "can_queue.h"

// 1. Kuyruğa yeni mesaj ekleme (Enqueue)
void enqueue(MesajKuyrugu *kuyruk, CAN_Mesaj mesaj) {
    if (kuyruk->count == kuyruk->kapasite) {
        // Kapasite kontrolü main.c tarafında da yapılıyor, ek güvenlik için buraya da koyabiliriz.
        return; 
    }
    
    kuyruk->rear = (kuyruk->rear + 1) % kuyruk->kapasite;
    kuyruk->mesajlar[kuyruk->rear] = mesaj;
    kuyruk->count++;
}

// 2. Kuyruktan ilk mesajı çekme (Dequeue)
CAN_Mesaj dequeue(MesajKuyrugu *kuyruk) {
    CAN_Mesaj islenen_mesaj = {0, 0.0, ""}; // Boş bir yapı döndürmek için
    
    if (kuyruk->count == 0) {
        return islenen_mesaj; 
    }
    
    islenen_mesaj = kuyruk->mesajlar[kuyruk->front];
    kuyruk->front = (kuyruk->front + 1) % kuyruk->kapasite;
    kuyruk->count--;
    
    return islenen_mesaj;
}

// 3. Kuyruktaki tüm mesajları listeleme
void bekleyenleri_goster(MesajKuyrugu *kuyruk) {
    int index = kuyruk->front;
    
    for (int i = 0; i < kuyruk->count; i++) {
        printf("   [%d] Sensör: %s | ID: %d | Veri: %.2f\n", 
               i + 1, 
               kuyruk->mesajlar[index].gonderen, 
               kuyruk->mesajlar[index].mesaj_id, 
               kuyruk->mesajlar[index].veri);
               
        index = (index + 1) % kuyruk->kapasite; // Dairesel (circular) iterasyon
    }
}