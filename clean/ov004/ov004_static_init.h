/* Overlay 4's static initialisers (its __sinit functions, run when the overlay is loaded, in the
 * order of its source files): its global C++ objects constructed and registered with their
 * destructors (__register_global_object, which runs them when the overlay goes), its tables of
 * member pointers filled from constants, and colours several of its source files define for
 * themselves. */
#ifndef CLEAN_OV004_OV004_STATIC_INIT_H
#define CLEAN_OV004_OV004_STATIC_INIT_H

void Ov004Init_Corners(void);
void Ov004Init_MusicPlayer(void);
void Ov004Init_Colours022577b0(void);
void Ov004Init_Colours02257910(void);
void Ov004Init_Colours022579fc(void);
void Ov004Init_Colours02257bbc(void);
int Ov004Init_RoomVillager(void);
int Ov004Init_FleaMarketVillager(void);
void Ov004Init_FleaMarketBuyer(void);
int Ov004Init_Shop3Villager(void);
void Ov004Init_Colours02257f78(void);
int Ov004Init_TailorSister(void);
int Ov004Init_CafeMaster(void);
int Ov004Init_Gatekeeper2(void);
int Ov004Init_TtiNpc(void);
void Ov004Init_Colours02258278(void);
void Ov004Init_CafePoints(void);
void Ov004Init_Colours02258448(void);
void Ov004Init_Colours0225848c(void);
void Ov004Init_TailorCloth(void);
void Ov004Init_Telephone(void);
void Ov004Init_RoomShell(void);
void Ov004Init_DroppedItems(void);
void Ov004Init_Aquarium(void);
void Ov004Init_RoomObjects(void);
void Ov004Init_MuseumInsects(void);
void Ov004Init_MuseumSpots(void);
int Ov004Init_PlayerPick(void);
void Ov004Init_RoomExits(void);
void Ov004Init_RoomCamera(void);

#endif
