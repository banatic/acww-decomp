/* The order catalog's lists (order_catalog.h): its flags, the lists of item codes and their
 * counts, the list's scroll and the scroll bar's thumb, the screens and palettes it queues, the
 * picked item and the labels. */
#ifndef CLEAN_OV142_ORDER_CATALOG_LIST_H
#define CLEAN_OV142_ORDER_CATALOG_LIST_H

#include "order_catalog.h"
#include "types.h"

void OrderCatalog_ClearFlags(OrderCatalog *self, u16 flags);
void OrderCatalog_SetFlags(OrderCatalog *self, u16 flags);
int OrderCatalog_TestFlags(OrderCatalog *self, int flags);
void OrderCatalog_StepFade(OrderCatalog *self);
void OrderCatalog_ApplyFade(OrderCatalog *self, u32 step);
u16 OrderCatalog_BlendColour(void *self, u16 colour, u16 faded, int step);
void OrderCatalog_PageStep(OrderCatalog *self);
void OrderCatalog_ReleaseArrows(OrderCatalog *self);
void OrderCatalog_HoldDownArrow(OrderCatalog *self);
void OrderCatalog_HoldUpArrow(OrderCatalog *self);
void OrderCatalog_ScrollToPickedRow(OrderCatalog *self);
void OrderCatalog_ShowPickedPage(OrderCatalog *self);
void OrderCatalog_HideBar(OrderCatalog *self);
void OrderCatalog_ShowBar(OrderCatalog *self);
void OrderCatalog_SetBarPalette(OrderCatalog *self, int palette);
void OrderCatalog_ThumbFromScroll(OrderCatalog *self);
void OrderCatalog_ScrollFromThumb(OrderCatalog *self);
void OrderCatalog_PlaceThumb(OrderCatalog *self);
int OrderCatalog_ThumbReleased(OrderCatalog *self);
void OrderCatalog_MoveThumbByPad(OrderCatalog *self);
void OrderCatalog_ReleaseThumb(OrderCatalog *self);
void OrderCatalog_DragThumb(OrderCatalog *self, int y, int jump);
int OrderCatalog_GrabThumb(OrderCatalog *self, int x, int y);
int OrderCatalog_PickItem(OrderCatalog *self, int category, int row);
void OrderCatalog_QueueListScreen(OrderCatalog *self);
void OrderCatalog_StepScroll(OrderCatalog *self);
void OrderCatalog_SetScroll(OrderCatalog *self, int scroll);
void OrderCatalog_FlushChanges(OrderCatalog *self);
void OrderCatalog_BuildListScreen(OrderCatalog *self);
u16 *OrderCatalog_ItemAt(OrderCatalog *self, int row);
s16 OrderCatalog_Count(OrderCatalog *self);
s16 OrderCatalog_Listed(OrderCatalog *self);
int OrderCatalog_CollectItems(OrderCatalog *self, u16 *out, u16 first, int count, int category);
int OrderCatalog_CollectEveryFourth(OrderCatalog *self, u16 *out, u16 first, int count, int category);
void OrderCatalog_ListCategory5(OrderCatalog *self);
void OrderCatalog_ListCategory8(OrderCatalog *self);
void OrderCatalog_ListCategory7(OrderCatalog *self);
void OrderCatalog_ListCategory6(OrderCatalog *self);
void OrderCatalog_ListCategory4(OrderCatalog *self);
void OrderCatalog_ListCategory3(OrderCatalog *self);
void OrderCatalog_ListCarpets(OrderCatalog *self);
void OrderCatalog_ListWallpaper(OrderCatalog *self);
void OrderCatalog_ListCategory0(OrderCatalog *self);
void OrderCatalog_StartFade(OrderCatalog *self, u8 tab);
void OrderCatalog_ShowCategory(OrderCatalog *self, u8 category);
void OrderCatalog_ClearPriceLabel(OrderCatalog *self);
void OrderCatalog_ShowNotOrderable(OrderCatalog *self);
void OrderCatalog_ShowMessage(OrderCatalog *self, int message, int x, int y, u8 colour, int centred);
void OrderCatalog_ShowPrice(OrderCatalog *self, int price);
void OrderCatalog_ShowCounts(OrderCatalog *self);
void OrderCatalog_SetRowLabels(OrderCatalog *self);
void OrderCatalog_CloseLabels(OrderCatalog *self);
TextLabel *OrderCatalog_NextLabel(OrderCatalog *self);

#endif
