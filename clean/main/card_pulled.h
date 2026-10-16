/* What the game does when the game card is pulled out: at start-up (NitroStartUp) it gives the
 * card library a callback that raises the stop flag at data_021cfb64 (the flag func_0206e3f4
 * waits on, halting) and asks the library to stop the program. */
#ifndef CLEAN_MAIN_CARD_PULLED_H
#define CLEAN_MAIN_CARD_PULLED_H

void CardPulled_Install(void);
int CardPulled_OnPulledOut(void);

#endif
