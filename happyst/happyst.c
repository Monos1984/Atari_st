// ****************************************************************
// * Nom ................ Happy St                                *
// * Programmeur ........ Jean Monos                              *
// * Data mise à jour.... 25/02/2020                              *
// * Fonction ........... Fonction dev pour Atari Ste GCC mint    *
// * Licence ............ CC-BY-SA                                *
// ****************************************************************


// ====================
// * Fichier includes *
// ====================

#include "header/happyst.h"


// ==================================
// * Declaration des variables glob *
// ==================================
long* Save_Ecran_Phys;
long* Save_Ecran_Log;
int   Save_Ecran_Mode_Video;
short Save_Buffer_Palette[16];


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
    *(Save_Buffer_Palette+i) = Setcolor(i,-1);
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


// ===============
// * load_data() *
// ===============

void load_data(char* source,char* destination,long size)
{
  // -------------------------------------
  // * Declaration des variables locales *
  // -------------------------------------
  signed int f_handles;
  unsigned char buffer_dta[44];

  // -------------------------
  // * Ouverture du fichier  *
  // -------------------------
  
  f_handles = Fopen(source,0);

  // -------------------------------
  // * Fichier correctement ouvert *
  // -------------------------------
  if (f_handles >= 0)
  {
    // -----------------------------------------------
    // * Calcule automatique de la taille du fichier *
    // -----------------------------------------------
    if (size==-1)
    {
      // -------------------------------
      // * preparation des données dta *
      // -------------------------------
      Fsetdta(buffer_dta);
      Fsfirst(source,0);

      // ----------------------------------
      // * Recuperer la taille du fichier *
      // ----------------------------------
   
      size = *(buffer_dta+26)*1024+*(buffer_dta+27)*512+*(buffer_dta+28)*256+*(buffer_dta+29);
     //  size = buffer_dta[26]*1024+buffer_dta[27]*512+buffer_dta[28]*256+buffer_dta[29];
    }

    // ----------------------------------------------
    // * Placer les donnés en dans le buffer voulu  *
    // ----------------------------------------------
    Fread(f_handles,size,destination);
    // ---------------------
    // * Fermer le fichier *
    // ---------------------
    Fclose(f_handles);
  }
  else
  {    
    draw_error(f_handles);
  }


}




// ================
// * Load Picture *
// ================
void load_picture(char* name)
{
  signed int f_handles;
  unsigned char picture_buffer[32034];


  // -------------------------
  // * Chargement de l'image *
  // -------------------------
  
  f_handles = Fopen(name,0);
  
  if (f_handles >= 0)
  {
  // -------------------------------
  // * Placer les donnés en buffer *
  // -------------------------------
  // Fread(f_handles,32034,picture_buffer);
  Fread(f_handles,32034,picture_buffer);
  // ---------------------
  // * Fermer le fichier *
  // ---------------------
  Fclose(f_handles);

  // ------------------------------------------
  // * Configuration de la palette de couleur *
  // ------------------------------------------
  Setpalette(picture_buffer+2);

  // ---------------------------------------
  // * Afficher l'image à l'écran physique *
  // ---------------------------------------
  memcpy(Physbase() ,(picture_buffer)+34,32000);
  }
  else
  {
     
    draw_error(f_handles);

  }


}


// ===============
// * Draw_Erreur *
// ===============
void draw_error(int id_error)
{

    switch (id_error)
    {

      case -33 :  draw_text(0,0,"Fichier Non trouver",1); break;
      case -34 :  draw_text(0,0,"Chemin non trouver",1); break;
    }


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

 
  return id_key;
}

// ====================
// * Afficher du text *
// ====================
void draw_text(unsigned char position_x,unsigned char position_y,char* texte,unsigned char couleur)
{
  printf( CURS_LOC, 32+position_y, 32+position_x ); fflush(stdout);
  printf(CHAR_COLOR , couleur);fflush(stdout);
  Cconws(texte);
}