/* The order catalog's cursor (order_catalog.h): its moves by the d-pad and by touch, its sprite,
 * what each place does, the order and its confirmation, and the sub states. */
#ifndef CLEAN_OV142_ORDER_CATALOG_CURSOR_H
#define CLEAN_OV142_ORDER_CATALOG_CURSOR_H

#include "order_catalog.h"
#include "types.h"

int OrderCatalog_MoveCursorByKeys(OrderCatalog *self, int keys);
void OrderCatalog_CursorToTabs(OrderCatalog *self);
void OrderCatalog_CursorLeftFromBar(OrderCatalog *self);
int OrderCatalog_CursorRightFromTabs(OrderCatalog *self);
int OrderCatalog_CursorToList(OrderCatalog *self);
void OrderCatalog_CursorLeftFromButtons(OrderCatalog *self);
int OrderCatalog_CursorRightFromList(OrderCatalog *self);
int OrderCatalog_CursorToBar(OrderCatalog *self);
int OrderCatalog_CursorToButtons(OrderCatalog *self);
int OrderCatalog_TouchedPlace(OrderCatalog *self, int x, int y);
int OrderCatalog_RunAction(OrderCatalog *self, int place);
void OrderCatalog_ResumeAfterPress(OrderCatalog *self);
void OrderCatalog_PressCursor(OrderCatalog *self);
void OrderCatalog_ShowCursorSprite(OrderCatalog *self);
void OrderCatalog_GlideCursorTo(OrderCatalog *self, int x, int y);
void OrderCatalog_GlideCursor(OrderCatalog *self);
void OrderCatalog_HideCursorSprite(OrderCatalog *self);
int OrderCatalog_CursorY(OrderCatalog *self);
int OrderCatalog_CursorX(OrderCatalog *self);
void OrderCatalog_PlaceCursorSprite(OrderCatalog *self);
void OrderCatalog_Quit(OrderCatalog *self);
void OrderCatalog_Order(OrderCatalog *self);
void OrderCatalog_Close(OrderCatalog *self);
void OrderCatalog_ResumeConfirm(OrderCatalog *self);
void OrderCatalog_ConfirmByKeysStart(OrderCatalog *self);
void OrderCatalog_ConfirmByTouchStart(OrderCatalog *self);
void OrderCatalog_Resume(OrderCatalog *self);
void OrderCatalog_ResumeByKeys(OrderCatalog *self);
void OrderCatalog_ResumeByTouch(OrderCatalog *self);
void OrderCatalog_FollowPanelPress(OrderCatalog *self);
void OrderCatalog_Decline(OrderCatalog *self);
void OrderCatalog_Accept(OrderCatalog *self);
void OrderCatalog_ConfirmByKeys(OrderCatalog *self);
void OrderCatalog_ConfirmByTouch(OrderCatalog *self);
void OrderCatalog_WaitPressEnd(OrderCatalog *self);
void OrderCatalog_WaitPressThenAct(OrderCatalog *self);
void OrderCatalog_WaitCursorSprite(OrderCatalog *self);
void OrderCatalog_HoldArrowByKeys(OrderCatalog *self);
void OrderCatalog_WaitThumbRelease(OrderCatalog *self);
void OrderCatalog_MoveThumbByKeys(OrderCatalog *self);
void OrderCatalog_BrowseByKeys(OrderCatalog *self);
void OrderCatalog_HoldArrowByTouch(OrderCatalog *self);
void OrderCatalog_PressTrackByTouch(OrderCatalog *self);
void OrderCatalog_DragThumbByTouch(OrderCatalog *self);
void OrderCatalog_BrowseByTouch(OrderCatalog *self);
void OrderCatalog_RunSubState(OrderCatalog *self);

#endif
