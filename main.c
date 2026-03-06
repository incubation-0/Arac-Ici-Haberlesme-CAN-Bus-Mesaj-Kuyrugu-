#include <stdio.h>
#include <stdlib.h>
#include "can_queue.h"

int main() {
    int kapasite, secim;
    MesajKuyrugu kuyruk;
    
    
    printf("[SİSTEM] Lütfen CAN Bus mesaj kuyruğu kapasitesini giriniz: ");
    scanf("%d", &kapasite); 

    
    kuyruk.mesajlar = (CAN_Mesaj*)malloc(kapasite * sizeof(CAN_Mesaj));
    if (kuyruk.mesajlar == NULL) {
    printf("[KRİTİK HATA] Bellek tahsisi başarısız oldu!\n");
    return 1; // Programı hata koduyla sonlandır
    };

    kuyruk.kapasite = kapasite;
    kuyruk.front = 0;
    kuyruk.rear = -1;
    kuyruk.count = 0;

    printf("[BİLGİ] %d kapasiteli dinamik mesaj kuyruğu bellekte oluşturuldu!\n", kapasite); 

    do {
        
        printf("\n--- CAN BUS İLETİŞİM SİSTEMİ ---\n");
        printf("1. Sensörden Mesaj Üret (Enqueue)\n"); 
        printf("2. Bekleyen İlk Mesajı İşle (Dequeue)\n"); 
        printf("3. Bekleyen Mesajları Göster\n"); 
        printf("4. Çıkış\n"); 
        printf("Seçiminiz: "); 
        scanf("%d", &secim);

        if (secim == 1) {
            if (kuyruk.count == kuyruk.kapasite) {
                printf("[HATA]: CAN Bus hattı dolu! Yeni mesaj eklenemez.\n"); 
            } else {
                CAN_Mesaj yeni_mesaj;
                printf("Sensör Adı: ");
                scanf("%29s", yeni_mesaj.gonderen);
                printf("Mesaj ID: "); 
                scanf("%d", &yeni_mesaj.mesaj_id); 
                printf("Veri: ");
                scanf("%f", &yeni_mesaj.veri); 

                enqueue(&kuyruk, yeni_mesaj); // <-- FONKSİYON BURAYA EKLENDİ
                printf("[BİLGİ] Mesaj alındı, kuyruğa iletildi...\n");
            }
        } 
        else if (secim == 2) {
            if (kuyruk.count == 0) {
                printf("[BİLGİ]: İşlenecek yeni mesaj bulunmuyor.\n");
            } else {
                CAN_Mesaj islenen = dequeue(&kuyruk); // <-- FONKSİYON BURAYA EKLENDİ
                printf("[BİLGİ] Mesaj başarıyla işlendi. (İşlenen: %s, ID: %d, Veri: %.2f)\n", islenen.gonderen, islenen.mesaj_id, islenen.veri); 
            }
        }
        else if (secim == 3) {
            if (kuyruk.count == 0) {
                printf("[BİLGİ]: İşlenecek yeni mesaj bulunmuyor.\n"); 
            } else {
                printf("[BEKLEYEN MESAJLAR Toplam: %d]\n", kuyruk.count); 
                bekleyenleri_goster(&kuyruk); // <-- FONKSİYON BURAYA EKLENDİ
            }
        }
        else if (secim == 4) {
        
            free(kuyruk.mesajlar); 
            printf("[BİLGİ] Dinamik bellek (RAM) temizleniyor...\n"); 
            printf("[BİLGİ] Sistem güvenli bir şekilde kapatıldı.\n"); 
        }
    } while (secim != 4);

    return 0;
}