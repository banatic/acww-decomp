/* The fish catalog of overlay 115 (catalog_scene.h): tab 2 of the menu's bar (overlay group 4,
 * with overlay 114), the catalog list of the fish. The insect catalog (ov116/insect_catalog.h)
 * is the same code with tab 3 and the list of insects. */
#ifndef CLEAN_OV115_FISH_CATALOG_H
#define CLEAN_OV115_FISH_CATALOG_H

#include "catalog_scene.h"
#include "types.h"

CatalogScene *FishCatalog_Destroy(CatalogScene *self);
CatalogScene *FishCatalog_Delete(CatalogScene *self);
void FishCatalog_SetFlags(CatalogScene *self, u16 flags);
int FishCatalog_TestFlags(CatalogScene *self, u16 flags);
u8 *FishCatalog_BeginRelease(CatalogScene *self);
void FishCatalog_BeginPress(CatalogScene *self);
void FishCatalog_ShowCursorIdle(CatalogScene *self);
void FishCatalog_GlideCursorTo(CatalogScene *self, int x, int y);
void FishCatalog_FollowListCursor(CatalogScene *self);
void FishCatalog_HideCursor(CatalogScene *self);
int FishCatalog_CursorY(CatalogScene *self);
int FishCatalog_CursorX(CatalogScene *self);
void FishCatalog_PlaceCursor(CatalogScene *self);
void FishCatalog_CloseLabel(CatalogScene *self);
void FishCatalog_EnterInputMode(CatalogScene *self);
void FishCatalog_EnterKeysMode(CatalogScene *self);
void FishCatalog_EnterTouchMode(CatalogScene *self);
void FishCatalog_EndScrollByKeys(CatalogScene *self);
void FishCatalog_ScrollWhileHeld(CatalogScene *self);
void FishCatalog_StartScrollByKeys(CatalogScene *self);
void FishCatalog_FinishRelease(CatalogScene *self);
int FishCatalog_FinishPress(CatalogScene *self);
void FishCatalog_WaitCursorGlide(CatalogScene *self);
void FishCatalog_IdleByKeys(CatalogScene *self);
void FishCatalog_DragByTouch(CatalogScene *self);
void FishCatalog_IdleByTouch(CatalogScene *self);
void FishCatalog_LoadObjects(CatalogScene *self);
void FishCatalog_LoadBackground(CatalogScene *self);
void FishCatalog_SetUpLayers(void);
void FishCatalog_EndFrame(CatalogScene *self);
void FishCatalog_BeginFrame(CatalogScene *self);
void FishCatalog_EndInteractiveFrame(CatalogScene *self);
int FishCatalog_BeginInteractiveFrame(CatalogScene *self);
void FishCatalog_Teardown(CatalogScene *self);
void FishCatalog_Init(CatalogScene *self);
void FishCatalog_ScrollLayers(CatalogScene *self);
void FishCatalog_WipeOut(CatalogScene *self);
void FishCatalog_StartWipeOut(CatalogScene *self);
void FishCatalog_WipeIn(CatalogScene *self);
void FishCatalog_Setup(CatalogScene *self);
int FishCatalog_SelectTab(CatalogScene *self, int tab);
int FishCatalog_CheckTabKeys(CatalogScene *self);
int FishCatalog_RequestDelete(CatalogScene *self);
int FishCatalog_Phase4(void);
int FishCatalog_Phase3(void);
int FishCatalog_RunInteractive(CatalogScene *self);
void FishCatalog_RunSubState(CatalogScene *self);
int FishCatalog_RunState(CatalogScene *self);
int FishCatalog_Draw(CatalogScene *self);
int FishCatalog_End(CatalogScene *self);
int FishCatalog_Start(CatalogScene *self);
CatalogScene *FishCatalog_New(void);

#endif
