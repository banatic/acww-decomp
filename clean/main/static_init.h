/* The main program's static initialisers (the compiler's __sinit functions, one for each source
 * file that has global objects): the ROM's start-up code runs them once, in address order,
 * before the game starts. Each builds its file's global objects (their constructors run), hands
 * each object that has a destructor to __register_global_object (with the record that links it
 * into the list of objects destructed at exit), and fills its file's tables of C++ pointers to
 * member functions from the constants in the program's data. */
#ifndef CLEAN_MAIN_STATIC_INIT_H
#define CLEAN_MAIN_STATIC_INIT_H

#include "types.h"

void StaticInit_AbAllObj(void);
int StaticInit_ActorList(void);
void StaticInit_StatusIcons(void);
void StaticInit_AMesObj(void);
void StaticInit_SceneObjectTables(void);
void StaticInit_TalkLetter(void);
void StaticInit_SpecialSceneAnimSpeed(void);
void StaticInit_CollisionOrigin(void);
void StaticInit_CollisionWorld(void);
void StaticInit_Block021c5160(void);
void StaticInit_RoomInterior(void);
void StaticInit_BgModels(void);
void StaticInit_CautionWindow(void);
void StaticInit_CameraView(void);
void StaticInit_PlayerOptions(void);
void StaticInit_MailText(void);
int StaticInit_EventQueueList(void);
int StaticInit_SceneObjectBaseList(void);
void StaticInit_EventEntries(void);
void StaticInit_Globe(void);
void StaticInit_EventCalendar(void);
void StaticInit_EventAnnounce(void);
void StaticInit_TownObjects(void);
void StaticInit_Nothing5250(void);
int StaticInit_BackupCard(void);
void StaticInit_TextFonts(void);
void StaticInit_RoomCells(void);
void StaticInit_FurnitureFiles(void);
void StaticInit_Nothing542c(void);
void StaticInit_Obj020dd33cModes(void);
void StaticInit_RoomScore(void);
void StaticInit_AnimSlots(void);
void StaticInit_BodyLook(void);
void StaticInit_ClothSlots(void);
void StaticInit_FaceAnimSlots(void);
void StaticInit_FaceAnimHeaps(void);
void StaticInit_FaceTexture(void);
void StaticInit_GlassesLook(void);
void StaticInit_HeadLook(void);
void StaticInit_HeldItemPool(void);
void StaticInit_BodyAnimHeaps(void);
void StaticInit_ActorPalettes(void);
void StaticInit_FishingFloat(void);
void StaticInit_MainRandom(void);
void StaticInit_ItemInfo(void);
void StaticInit_Colours5ae4(void);
void StaticInit_Texts5b40(void);
void StaticInit_Colours5ba0(void);
void StaticInit_SoundSet(void);
void StaticInit_OverlayGroups(void);
void StaticInit_Nothing5c90(void);

#endif
