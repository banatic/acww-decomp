/* The card pulled out (card_pulled.h). */
#include "card_pulled.h"

#include "clean.h"
#include "types.h"

extern u8 data_021cfb64; /* the stop flag */

/* The SDK's setter of the card library's pulled-out callback (CARD_UserCallback). */
extern void func_02120000(int (*callback)(void));
/* The callback as the game knows it; the library calls it, so it is handed over as the game's
 * symbol. */
extern int func_02098414(void);

/* func_02098404: install the callback. */
void CardPulled_Install(void)
{
    func_02120000(func_02098414);
}
CLEAN_AS(func_02098404, CardPulled_Install)

/* func_02098414: the callback: raise the stop flag; 1 asks the library to stop the program. */
int CardPulled_OnPulledOut(void)
{
    data_021cfb64 = 1;
    return 1;
}
CLEAN_AS(func_02098414, CardPulled_OnPulledOut)
