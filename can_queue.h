#ifndef can_queue_h
#define can_queue_h

typedef struct{
    int mesaj_id;
    float veri;
    char gonderen[30];
    
} CAN_Mesaj;


typedef struct{
    CAN_Mesaj *mesajlar;
    int front;
    int rear;
    int kapasite;
    int count;

}MesajKuyrugu;

void enqueue(MesajKuyrugu *kuyruk, CAN_Mesaj mesaj);
CAN_Mesaj dequeue(MesajKuyrugu *kuyruk);
void bekleyenleri_goster(MesajKuyrugu *kuyruk);

#endif
