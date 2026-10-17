/* The order catalog as a menu scene (order_catalog.h): its graphics and layers, the frames, the
 * states, the draw, and its construction and destruction. The phases run the vtable's slots
 * 0x48 + 4 * phase (ov092/menu_dispatch.h): 1 OrderCatalog_RunState, 2
 * OrderCatalog_RunInteractive, 3 and 4 nothing, 5 OrderCatalog_End. */
#ifndef CLEAN_OV142_ORDER_CATALOG_SCENE_H
#define CLEAN_OV142_ORDER_CATALOG_SCENE_H

#include "order_catalog.h"
#include "types.h"

OrderCatalog *OrderCatalog_Destroy(OrderCatalog *self);
OrderCatalog *OrderCatalog_Delete(OrderCatalog *self);
void OrderCatalog_LoadObjGraphics(OrderCatalog *self);
void OrderCatalog_LoadBgGraphics(OrderCatalog *self);
void OrderCatalog_SetUpLayers(void);
void OrderCatalog_EndFrame(OrderCatalog *self);
void OrderCatalog_BeginFrame(OrderCatalog *self);
void OrderCatalog_EndInteractiveFrame(OrderCatalog *self);
void OrderCatalog_BeginInteractiveFrame(OrderCatalog *self);
void OrderCatalog_Teardown(OrderCatalog *self);
void OrderCatalog_Setup(OrderCatalog *self);
void OrderCatalog_ScrollWithWipe(OrderCatalog *self);
void OrderCatalog_PanelInToBrowse(OrderCatalog *self);
void OrderCatalog_PanelOutToBrowse(OrderCatalog *self);
void OrderCatalog_PanelInToConfirm(OrderCatalog *self);
void OrderCatalog_PanelOutToConfirm(OrderCatalog *self);
void OrderCatalog_WipeOut(OrderCatalog *self);
void OrderCatalog_StartWipeOut(OrderCatalog *self);
void OrderCatalog_WipeIn(OrderCatalog *self);
void OrderCatalog_StartWipeIn(OrderCatalog *self);
int OrderCatalog_End(OrderCatalog *self);
int OrderCatalog_Phase4Idle(void);
int OrderCatalog_Phase3Idle(void);
int OrderCatalog_RunInteractive(OrderCatalog *self);
int OrderCatalog_RunState(OrderCatalog *self);
int OrderCatalog_Draw(OrderCatalog *self);
int OrderCatalog_Shutdown(OrderCatalog *self);
int OrderCatalog_Start(OrderCatalog *self);
OrderCatalog *OrderCatalog_New(void);

#endif
