// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 10/02/2020                              *
// * Fonction ........... Fonction dev pour Atari Ste GCC mint    *
// ****************************************************************


#ifndef HAPPST_H
	#define  HAPPST_H
  
  // ====================
  // * Fichier includes *
  // ====================
  #include <OSBIND.h>
  #include <vt52.h>
  #include <stdio.h>
  #include <string.h>
  // ==============
  // * Signatures *
  // ==============

  void save_init_st(); // Sauvegarder les données ecran 
  void restore_init_st();// Restorer les données ecran
  short get_keyboard();
  void load_picture(char* name);
  void bip_clavier_off();
  void bip_clavier_on();

  void draw_text(unsigned char position_x,unsigned char position_y,char* texte);

  // ==========================================
  // * Signature divers hors fonction directe *
  // ==========================================
  void clavier_off();
  void clavier_on();
  // ==================
  // * Define keybord *
  // ==================

  #define KEY_UP     0x48
  #define KEY_LEFT   0x4B
  #define KEY_RIGHT  0x4D
  #define KEY_DOWN   0x50

  #define KEY_ESC    0x01
  #define KEY_RETURN 0x1C
  #define KEY_SPACE  0x39
  #define KET_ENTER  0x72

  // =============
  // Define Divers
  // =============
  #define CONTERM *((unsigned char *) 0x484)


  // ---------------------------------------
  // * PEEK(addr)                          *
  // ---------------------------------------
  /* 
    - Permet de lire un octet à une adresse 
     # addr : Adresse mémoire sur 2 octets (int )
  */
 
  #define PEEK(addr)         (*(long*) (addr))
  
  // ---------------------------------------
  // * POKE(adrr,val)                      *
  // ---------------------------------------
  /* 
    - Permet d'écrire un octet à une adresse
     # addr : Adresse mémoire sur 2 octets (int)
     # val  : valeur sur 1 octet (0-255) 
  */
  
  #define POKE(addr,val)     (*(long*) (addr) = (val))

#endif