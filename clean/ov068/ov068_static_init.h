/* Overlay 68's static initializers (its __sinit functions, run when the overlay is loaded, in
 * the order of its source files): its tables of C++ pointers to member functions filled from
 * the overlay's constants, two angles copied from main's, and colors several of its source
 * files define for themselves. */
#ifndef CLEAN_OV068_OV068_STATIC_INIT_H
#define CLEAN_OV068_OV068_STATIC_INIT_H

void Ov068Init_OutdoorVillagerBehaviors(void);
void Ov068Init_Colors02278604(void);
int Ov068Init_TownNookTables(void);
void Ov068Init_Colors022786d0(void);
int Ov068Init_CafeGuestTables(void);
void Ov068Init_Colors02278894(void);
void Ov068Init_Colors022788d8(void);

#endif
