// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 29/02/2020                              *
// * Fonction ........... Fonction dev pour Atari Ste GCC mint    *
// * Licence ............ CC-BY-SA                                *
// ****************************************************************


/*
  29/02/2020 : Ajout du background color dans le draw_text
  25/02/2020 : Le Load Data peut calculer automatiquement la taille du fichier chargé avant l'envois dans le buffer. (-1)
  17/02/2020 : Ajout du chargement de fichier "Data" dans un buffer choisis.
  16/02/2020 : Contrôle si le fichier pi est ouvert
  12/02/2020 : ajout de define Mode video et Wait_key
  11/02/2020 : Ajout de l'argument couleurs dans le draw_text();

*/

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
  short get_keyboard();// Récupérer les touches du buffer (A améliorer)
  void load_picture(char* name); // Charge et place une image PC1 dans la mémoire vidéo.
  void bip_clavier_off(); // Desactive le bip sonore des touches
  void bip_clavier_on(); // Active le bip sonore des touches
  
  // charge un fichier dans le buffer de votre choix. Si size = -1 alors c'est le fichier entier qui est copier
  void load_data(char* source,char* destination,long size); 

  void draw_text(unsigned char position_x,unsigned char position_y,char* texte,unsigned char couleur, unsigned char bakckground_color); // Affiche un text
  void draw_error(int id_error); // Afficher les erreurs


  // ======================
  // * Define de fonction *
  // ======================
  #define WAIT_KEY Cconin() // Attendre qu'une touche est utilisé
  #define MOUSSE_OFF v_hide_c(1); // Cache la sourie
  
  // -------------------------
  // * Configuration de mode *
  // -------------------------
  #define SET_MODE_LOWRES       Setscreen(Physbase(),Logbase(),0)
  #define SET_MODE_MEDRES       Setscreen(Physbase(),Logbase(),1)
  #define SET_MODE_HIRES        Setscreen(Physbase(),Logbase(),2)
  

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