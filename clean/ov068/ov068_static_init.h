/* Overlay 68's static initialisers (its __sinit functions, run when the overlay is loaded, in
 * the order of its source files): its tables of C++ pointers to member functions filled from
 * the overlay's constants, two angles copied from main's, and colours several of its source
 * files define for themselves. */
#ifndef CLEAN_OV068_OV068_STATIC_INIT_H
#define CLEAN_OV068_OV068_STATIC_INIT_H

void Ov068Init_OutdoorVillagerBehaviours(void);
void Ov068Init_Colours02278604(void);
int Ov068Init_TownNookTables(void);
void Ov068Init_Colours022786d0(void);
int Ov068Init_CafeGuestTables(void);
void Ov068Init_Colours02278894(void);
void Ov068Init_Colours022788d8(void);

#endif
