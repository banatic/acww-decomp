/* The current player's bells as the scene objects handle them (scene_bells.h). */
#include "scene_bells.h"

#include "clean.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"

/* The current player's pockets. */
static PlayerPockets *scene_bells_pockets(void)
{
    return PlayerRecord_Pockets(PlayerRecords_Current());
}

/* func_0201b3a4: `amount` bells into the current player's pockets. */
void SceneBells_Give(int unused, int amount)
{
    (void) unused;
    PlayerPockets_AddBells(scene_bells_pockets(), amount, PLAYER_POCKETS_USE_BAGS);
}
CLEAN_AS(func_0201b3a4, SceneBells_Give)

/* func_0201b3c0: whether `amount` bells fit in the wallet (SCENE_BELLS_FIT_WALLET), in the
 * wallet and the bags with `extra_bags` (SCENE_BELLS_FIT_BAGS), or not (SCENE_BELLS_FIT_NONE).
 * Without a current player both rooms count as 0. */
int SceneBells_Fit(int unused, int amount, int extra_bags)
{
    (void) unused;
    PlayerPockets *pockets = NULL;
    if (PlayerRecords_Current() != NULL) {
        pockets = scene_bells_pockets();
    }
    int wallet_room = pockets != NULL ? PlayerPockets_BellsRoom(pockets, 0, 0) : 0;
    int room = pockets != NULL ? PlayerPockets_BellsRoom(pockets, 1, extra_bags) : 0;

    if (amount <= wallet_room) {
        return SCENE_BELLS_FIT_WALLET;
    }
    if (amount <= room) {
        return SCENE_BELLS_FIT_BAGS;
    }
    return SCENE_BELLS_FIT_NONE;
}
CLEAN_AS(func_0201b3c0, SceneBells_Fit)

/* func_0201b420: `amount` bells out of the current player's pockets.
 * QUIRK: the amount is negated as the ARM does (-0x80000000 stays itself). */
void SceneBells_Take(int unused, int amount)
{
    (void) unused;
    PlayerPockets_AddBells(scene_bells_pockets(), (int) (0u - (u32) amount), PLAYER_POCKETS_USE_BAGS);
}
CLEAN_AS(func_0201b420, SceneBells_Take)

/* func_0201b43c: whether the current player can pay `amount` bells, the bags included. */
int SceneBells_CanPay(int unused, int amount)
{
    (void) unused;
    return PlayerPockets_CanChangeBells(scene_bells_pockets(), (int) (0u - (u32) amount), 1, 0);
}
CLEAN_AS(func_0201b43c, SceneBells_CanPay)
