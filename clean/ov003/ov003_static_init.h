/* Overlay 3's static initialisers (its __sinit functions, run when the overlay is loaded, in the
 * order of its source files): its global C++ objects constructed and registered with their
 * destructors (__register_global_object, which runs them when the overlay goes), its tables of
 * member pointers filled from constants, and colours several of its source files define for
 * themselves. */
#ifndef CLEAN_OV003_OV003_STATIC_INIT_H
#define CLEAN_OV003_OV003_STATIC_INIT_H

void Ov003Init_Colours0223c5a4(void);
void Ov003Init_Colours0223c734(void);
void Ov003Init_Colours0223c784(void);
void Ov003Init_Colours0223c9bc(void);
void Ov003Init_Colours0223caa0(void);
void Ov003Init_Colours0223cab8(void);
void Ov003Init_Colours0223cad8(void);
void Ov003Init_TownExits(void);
void Ov003Init_HouseFiles(void);
void Ov003Init_TileEvents(void);
void Ov003Init_Fish(void);
void Ov003Init_TownInsects(void);
void Ov003Init_SessionObjects(void);
void Ov003Init_Colours02262d78(void);

#endif
