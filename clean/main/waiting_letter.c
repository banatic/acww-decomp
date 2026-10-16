/* The letter waiting for the current player (waiting_letter.h). */
#include "waiting_letter.h"

#include "clean.h"

static_assert(offsetof(WaitingLetter, checksum) == 0x100 && sizeof(WaitingLetter) == 0x104, "WaitingLetter");

/* A letter's state (0: no letter), emptying it, and its destructor and constructor (both set
 * its vtable, data_020de760). */
extern u8 func_02065ec0(const MailLetter *letter);
extern void func_02066650(MailLetter *letter);
extern void func_02066688(MailLetter *letter);
extern void func_02066694(MailLetter *letter);

/* func_0208ffe4: the letter (the object itself). */
MailLetter *WaitingLetter_Letter(WaitingLetter *waiting)
{
    return &waiting->letter;
}
CLEAN_AS(func_0208ffe4, WaitingLetter_Letter)

/* func_0208ffe8 */
u8 WaitingLetter_Checksum(WaitingLetter *waiting)
{
    return waiting->checksum;
}
CLEAN_AS(func_0208ffe8, WaitingLetter_Checksum)

/* func_0208fff4 */
void WaitingLetter_SetChecksum(WaitingLetter *waiting, u8 checksum)
{
    waiting->checksum = checksum;
}
CLEAN_AS(func_0208fff4, WaitingLetter_SetChecksum)

/* func_02090000: whether a letter waits (its state is not 0). */
int WaitingLetter_IsSet(WaitingLetter *waiting)
{
    return func_02065ec0(&waiting->letter) != 0;
}
CLEAN_AS(func_02090000, WaitingLetter_IsSet)

/* func_02090018: the letter emptied. */
void WaitingLetter_Clear(WaitingLetter *waiting)
{
    func_02066650(&waiting->letter);
}
CLEAN_AS(func_02090018, WaitingLetter_Clear)

/* func_02090020: the destructor (the letter's). */
int WaitingLetter_Destruct(WaitingLetter *waiting)
{
    func_02066688(&waiting->letter);
    return (int) (uintptr_t) waiting;
}
CLEAN_AS(func_02090020, WaitingLetter_Destruct)

/* func_02090030: the constructor (the letter's). */
WaitingLetter *WaitingLetter_Construct(WaitingLetter *waiting)
{
    func_02066694(&waiting->letter);
    return waiting;
}
CLEAN_AS(func_02090030, WaitingLetter_Construct)
