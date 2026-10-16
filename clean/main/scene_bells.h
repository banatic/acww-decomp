/* The current player's bells as the scene objects handle them: given, taken, whether a payment
 * can be made and whether an amount fits (player_pockets.h). Each takes a first argument it does
 * not use (overlay 52, which takes bells and checks payments, hands its word at 0xb4). Bells
 * beyond the wallet's room go into bell bags and a payment the wallet cannot cover is taken from
 * them. */
#ifndef CLEAN_MAIN_SCENE_BELLS_H
#define CLEAN_MAIN_SCENE_BELLS_H

#include "types.h"

/* What SceneBells_Fit answers. */
#define SCENE_BELLS_FIT_WALLET 0 /* the wallet takes the amount */
#define SCENE_BELLS_FIT_BAGS 1   /* the wallet and bags take it */
#define SCENE_BELLS_FIT_NONE 2

void SceneBells_Give(int unused, int amount);
int SceneBells_Fit(int unused, int amount, int extra_bags);
void SceneBells_Take(int unused, int amount);
int SceneBells_CanPay(int unused, int amount);

#endif
