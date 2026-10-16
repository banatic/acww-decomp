/* The places designs (design.h) are kept, with the defaults each is reset to:
 *
 * - a player's eight designs (PlayerDesigns, at the start of a player record) and the order the
 *   player sees them in; reset to the eight of "b_myd_my_obj.bch", made by the player;
 * - the shop's eight designs (data_021ed278); reset to the eight of "b_myd_bu_obj.bch", made by
 *   no town (0xffff) and the player number 0x7ffd;
 * - the one sample (data_021d0800), read from "menu/desi/myc/obj<n>.bch" when asked for, made
 *   by no town and the player number 0x7fff;
 * - a single design (DesignHolder, in the record at data_021f34b0); reset to "obj0.bch", made
 *   in this town by the player number 0x7ffc.
 *
 * Each design's information comes from record n of "/myOrg/myD.bin" (design_assets.h): 0-7
 * for the player's, 8-15 for the shop's, 16 for the holder's and 18-49 for the 32 samples.
 * The manager's flags, one per shop design, say which shop design changed. */
#ifndef CLEAN_MAIN_DESIGN_SETS_H
#define CLEAN_MAIN_DESIGN_SETS_H

#include "design.h"
#include "design_assets.h"
#include "types.h"

#define DESIGN_SAMPLES 32

/* The order a player's designs are shown in: the design at each place (0-7). */
typedef struct DesignOrder {
    u8 design[DESIGNS_PER_SET];
} DesignOrder;

typedef struct PlayerDesigns {
    Design designs[DESIGNS_PER_SET];
    DesignOrder order; /* 0x11a0 */
} PlayerDesigns;

typedef struct ShopDesigns {
    Design designs[DESIGNS_PER_SET];
} ShopDesigns;

int DesignManager_TakeShopChanged(DesignManager *manager, int index);
void DesignManager_MarkShopChanged(DesignManager *manager, int index);
void DesignManager_ClearChanged(DesignManager *manager);
char *DesignManager_Destruct(char *manager);
char *DesignManager_Construct(char *manager);
void DesignManager_Reset(DesignManager *manager);
int DesignSample_Get(void);
Design *DesignSample_Design(Design *sample);
int DesignSample_Load(Design *sample, unsigned int index);
int DesignSample_Destruct(Design *sample);
int DesignSample_Construct(Design *sample);
Design *DesignHolder_Design(Design *holder);
void DesignHolder_Reset(Design *holder);
int DesignHolder_Destruct(Design *holder);
Design *DesignHolder_Construct(Design *holder);
unsigned int ShopDesigns_At(unsigned int designs, unsigned int index);
void ShopDesigns_Reset(ShopDesigns *designs);
ShopDesigns *ShopDesigns_Destruct(ShopDesigns *designs);
ShopDesigns *ShopDesigns_Construct(ShopDesigns *designs);
unsigned char DesignOrder_Get(unsigned char *order, int place);
void DesignOrder_Swap(unsigned char *order, int place_a, int place_b);
void DesignOrder_Reset(unsigned char *order);
void DesignOrder_Destruct(DesignOrder *order);
void DesignOrder_Construct(DesignOrder *order);
int PlayerDesigns_Order(PlayerDesigns *designs);
int PlayerDesigns_InOrder(PlayerDesigns *designs, int place);
int PlayerDesigns_At(PlayerDesigns *designs, int index);
void PlayerDesigns_UpdateTown(PlayerDesigns *designs, DesignCreator *player, u8 *old_town);
void PlayerDesigns_Reset(PlayerDesigns *designs, DesignCreator *player);
PlayerDesigns *PlayerDesigns_Destruct(PlayerDesigns *designs);
PlayerDesigns *PlayerDesigns_Construct(PlayerDesigns *designs);

#endif
