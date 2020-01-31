// *********************************************
// * Test de programe cross dev pc => Atari ST *
// * Compilation avec GCC                      *
// *********************************************

// ===================
// * Fichier include *
// ===================
#include <stdio.h>
#include <string.h>

/* 
Cibler le fichier h OSBIND.
Lien sur mon pc :
C:\MinGW\mingw32\m68k-atari-mint\sys-root\usr\include\mint\OSBIND.h

*/
#include "OSBIND.h"


// =================
// * Fonction main *
// =================
void main()
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------

  long* Ecran_Phys;
  long* Ecran_Log;
  int   Ecran_Mode_Video;
  short buffer_palette[16];

 
  int   id_image_lenna;
  unsigned char buffer[32034];
  unsigned char i;
  unsigned char test;
  
  // ------------------------------------------------------
  // * Sauvegarde de la résolution et des adresses écrans *
  // ------------------------------------------------------
  Ecran_Phys = Physbase();
  Ecran_Log = Logbase();
  Ecran_Mode_Video = Getrez();
  
  // ----------
  // * Mode 0 * 
  // ----------
  Setscreen(Ecran_Phys,Ecran_Log,0);
  
  // -------------------------------
  // * Sauvegarder la palette init *
  // -------------------------------
  for (i=0;i<16;i++)
  {
    buffer_palette[i] = Setcolor(i,-1);
  }

  // -------------------------
  // * Chargement de l'image *
  // -------------------------
  id_image_lenna = Fopen("LENNA.PI1",0);
  
  // -------------------------------
  // * Placer les donnés en buffer *
  // -------------------------------
  Fread(id_image_lenna,32034,buffer);

  // ------------------
  // * Fermer l'image *
  // ------------------
  Fclose(id_image_lenna);
 
  // ------------------------------------------
  // * Configuration de la palette de couleur *
  // ------------------------------------------
  Setpalette(buffer+2);

  // ---------------------------------------
  // * Afficher l'image à l'écran physique *
  // ---------------------------------------
  memcpy(Ecran_Phys,buffer+34,32034-34);

  // -----------------------
  // * Attendre une touche *
  // -----------------------
  Cconin();

  // -------------------------------------------------
  // * Restitution de la résolution et palette écran *
  // -------------------------------------------------
  
  /*
    La palette écran se met à jour après Vsync();
  */

  Setscreen(Ecran_Phys,Ecran_Log,Ecran_Mode_Video);
  Setpalette(buffer_palette);
  Vsync();
}