/* The insect catalog of overlay 116 (ov115/catalog_scene.h): tab 3 of the menu's bar (overlay
 * group 5, with overlay 114), the catalog list of the insects. It is the code of the fish
 * catalog (ov115/fish_catalog.h) with its own tab and list. */
#ifndef CLEAN_OV116_INSECT_CATALOG_H
#define CLEAN_OV116_INSECT_CATALOG_H

#include "ov115/catalog_scene.h"
#include "types.h"

CatalogScene *InsectCatalog_Destroy(CatalogScene *self);
CatalogScene *InsectCatalog_Delete(CatalogScene *self);
void InsectCatalog_SetFlags(CatalogScene *self, u16 flags);
int InsectCatalog_TestFlags(CatalogScene *self, u16 flags);
u8 *InsectCatalog_BeginRelease(CatalogScene *self);
void InsectCatalog_BeginPress(CatalogScene *self);
void InsectCatalog_ShowCursorIdle(CatalogScene *self);
void InsectCatalog_GlideCursorTo(CatalogScene *self, int x, int y);
void InsectCatalog_FollowListCursor(CatalogScene *self);
void InsectCatalog_HideCursor(CatalogScene *self);
int InsectCatalog_CursorY(CatalogScene *self);
int InsectCatalog_CursorX(CatalogScene *self);
void InsectCatalog_PlaceCursor(CatalogScene *self);
void InsectCatalog_CloseLabel(CatalogScene *self);
void InsectCatalog_EnterInputMode(CatalogScene *self);
void InsectCatalog_EnterKeysMode(CatalogScene *self);
void InsectCatalog_EnterTouchMode(CatalogScene *self);
void InsectCatalog_EndScrollByKeys(CatalogScene *self);
void InsectCatalog_ScrollWhileHeld(CatalogScene *self);
void InsectCatalog_StartScrollByKeys(CatalogScene *self);
void InsectCatalog_FinishRelease(CatalogScene *self);
int InsectCatalog_FinishPress(CatalogScene *self);
void InsectCatalog_WaitCursorGlide(CatalogScene *self);
void InsectCatalog_IdleByKeys(CatalogScene *self);
void InsectCatalog_DragByTouch(CatalogScene *self);
void InsectCatalog_IdleByTouch(CatalogScene *self);
void InsectCatalog_LoadObjects(CatalogScene *self);
void InsectCatalog_LoadBackground(CatalogScene *self);
void InsectCatalog_SetUpLayers(void);
void InsectCatalog_EndFrame(CatalogScene *self);
void InsectCatalog_BeginFrame(CatalogScene *self);
void InsectCatalog_EndInteractiveFrame(CatalogScene *self);
void InsectCatalog_BeginInteractiveFrame(CatalogScene *self);
void InsectCatalog_Teardown(CatalogScene *self);
void InsectCatalog_Init(CatalogScene *self);
void InsectCatalog_ScrollLayers(CatalogScene *self);
void InsectCatalog_WipeOut(CatalogScene *self);
void InsectCatalog_StartWipeOut(CatalogScene *self);
void InsectCatalog_WipeIn(CatalogScene *self);
void InsectCatalog_Setup(CatalogScene *self);
int InsectCatalog_SelectTab(CatalogScene *self, int tab);
int InsectCatalog_CheckTabKeys(CatalogScene *self);
int InsectCatalog_RequestDelete(CatalogScene *self);
int InsectCatalog_Phase4(void);
int InsectCatalog_Phase3(void);
int InsectCatalog_RunInteractive(CatalogScene *self);
void InsectCatalog_RunSubState(CatalogScene *self);
int InsectCatalog_RunState(CatalogScene *self);
int InsectCatalog_Draw(CatalogScene *self);
int InsectCatalog_End(CatalogScene *self);
int InsectCatalog_Start(CatalogScene *self);
CatalogScene *InsectCatalog_New(void);

#endif
