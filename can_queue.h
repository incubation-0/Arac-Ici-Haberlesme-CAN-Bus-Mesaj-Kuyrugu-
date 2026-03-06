#ifndef can_queue_h
#define can_queue_h

typedef struct{
    int mesaj_id;
    float veri;
    char gönderen[30];
    
}; CAN_mesaj;

typedef struct{
    CAN_mesaj *mesajlar;
    int front;
    int rear;
    int kapasite;
    int count;

}MesajKuyrugu;

#endif

