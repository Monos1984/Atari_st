// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 10/02/2020                              *
// * Fonction ........... Fonction dev pour Atari Ste GCC mint    *
// ****************************************************************


// ====================
// * Fichier includes *
// ====================
// #include "header/include.h"
#include "header/happyst.h"


// ==================================
// * Declaration des variables glob *
// ==================================
long* Save_Ecran_Phys;
long* Save_Ecran_Log;
int   Save_Ecran_Mode_Video;
short Save_Buffer_Palette[16];
unsigned char picture_buffer[32034];



// ===================
// * Bip Clavier Off *
// ===================
void bip_clavier_off() 
{
   Supexec(clavier_off); 
}
 
// ==================
// * Bip Clavier On *
// ==================
void bip_clavier_on() 
{ 
  Supexec(clavier_on);
}

// =======================
// * Bip Clavier routine *
// =======================
void clavier_off() 
{
   CONTERM &= 0xFE;
}
 
void clavier_on() 
{ 
  CONTERM |= 0x01;
}



// ================
// * save_init_st *
// ================
void save_init_st()
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  unsigned char i;
  
  // ---------------------------
  // * Sauvegarder les données *
  // ---------------------------
  Save_Ecran_Phys = Physbase();
  Save_Ecran_Log = Logbase();
  Save_Ecran_Mode_Video = Getrez();

  // -------------------------------------
  // * Sauvegarder la palette de couleur *
  // -------------------------------------
  for (i=0;i<16;i++)
  {
    Save_Buffer_Palette[i] = Setcolor(i,-1);
  }

}

// ===================
// * restore_init_st *
// ===================
void restore_init_st()
{
  Setscreen(Save_Ecran_Phys,Save_Ecran_Log,Save_Ecran_Mode_Video);
  Setpalette(Save_Buffer_Palette);
  Vsync();
}

// ================
// * Load Picture *
// ================
void load_picture(char* name)
{
  unsigned char id_image;
  // -------------------------
  // * Chargement de l'image *
  // -------------------------
  
  id_image = Fopen(name,0);
  
  // -------------------------------
  // * Placer les donnés en buffer *
  // -------------------------------
  Fread(id_image,32034,picture_buffer);

  // ---------------------
  // * Fermer le fichier *
  // ---------------------
  Fclose(id_image);

  // ------------------------------------------
  // * Configuration de la palette de couleur *
  // ------------------------------------------
  Setpalette(picture_buffer+2);

  // ---------------------------------------
  // * Afficher l'image à l'écran physique *
  // ---------------------------------------
  memcpy(Physbase(),picture_buffer+34,32034-34);
}


// ================
// * Get Keyboard *
// ================

short get_keyboard()
{
  short id_key;

  if(Cconis()!= 0)
  {     
    id_key = Crawcin()>>16; 
  }

  // Vsync();
  return id_key;
}

// ====================
// * Afficher du text *
// ====================
void draw_text(unsigned char position_x,unsigned char position_y,char* texte)
{
  printf( CURS_LOC, 32+position_y, 32+position_x ); fflush(stdout);
  Cconws(texte);
}