/* func_ov004_0221b6d8 @ 0x0221b6d8, 0x130 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0221b98c(void *);
extern int func_ov004_0221ba40(void *);
extern int func_ov004_0221b9f4(void *);
extern void func_0206844c(void *, u8 *, int);
extern void *func_0206837c(void *);
extern void func_020ab670(void *, int, int);
extern void func_020ab628(void *, int, u8 *, int, void *, int, int);
extern void func_020ab5f8(void *);
extern void func_02068388(void *, int);
extern u8 data_021f43e8;
extern char data_021f43f8;
#define DIALOGUE (*(void **) (self + 0x12c))
void func_ov004_0221b6d8(char *self)
{
    if (func_ov004_0221b98c(self)) {
        return;
    }
    if (*(int *) (self + 0x15c) == 3) {
        if (*(u8 *) (self + 0x10a) != 5) {
            if (func_ov004_0221ba40(self)) {
                if (*(short *) (self + 0x160) == *(u8 *) (self + 0x10a)) {
                    u8 message = *(u8 *) (self + 0x10a) + 1;
                    func_0206844c(DIALOGUE, &message, 0);
                } else {
                    u8 message = data_021f43e8;
                    func_0206844c(DIALOGUE, &message, 0);
                }
            } else {
                u8 message = data_021f43e8;
                func_0206844c(DIALOGUE, &message, 0);
            }
        } else {
            u8 message = data_021f43e8;
            func_0206844c(DIALOGUE, &message, 0);
        }
    } else if (func_ov004_0221b9f4(self)) {
        void *dialogue = func_0206837c(DIALOGUE);
        if (dialogue) {
            u8 first, second;
            func_020ab670(dialogue, 2, 1);
            first = 0xe5;
            func_020ab628(dialogue, 0, &first, 0, &data_021f43f8, 0, 0);
            second = 0xe6;
            func_020ab628(dialogue, 1, &second, 0, &data_021f43f8, 0, 0);
            func_020ab5f8(dialogue);
            func_02068388(DIALOGUE, 1);
        }
    } else {
        u8 message = data_021f43e8;
        func_0206844c(DIALOGUE, &message, 0);
    }
}
