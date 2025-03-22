/*
* \Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
* \Description du programme: Cette classe nous permet de deboguer des partie de notre code
*/
#include "communication.h"
Communication communication;
#define DEBUG // à mettre en commentaire ou non au besoin
#ifdef DEBUG
#define DEBUG_PRINT(x) communication.sendMessage(x) // ou par RS-232
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0) // code mort
#endif