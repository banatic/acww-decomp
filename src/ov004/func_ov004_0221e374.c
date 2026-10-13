/* func_ov004_0221e374 @ 0x0221e374, 0x220 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_020ccf94;
extern void func_0201c054(char *, int, int, int);
extern void func_ov004_0221eb6c(char *, char *, int);
extern int func_0201c0e0(char *);
extern int func_0207f150(void *);
extern int func_0201cddc(char *);
extern void func_0202dc3c(char *, char *, int);
extern int func_0201c2a4(char *, int);
extern void func_02016108(char *, int);
extern int func_020a7278(void);
extern int func_ov004_0221eb44(char *, char *);
extern int func_0201c014(char *);
extern int func_0201c040(char *, int *, int *);
#define OWNER (*(int *) (data_020ccf94 + 0x64))
#define STATE (*(int *) (self + 0x8d8))
void func_ov004_0221e374(char *self, int event, int player)
{
    switch (event) {
        case 3:
            *(u8 *) (self + 0x560) = player;
            if (player != 4) {
                func_0201c054(self, 1, OWNER, player);
                func_ov004_0221eb6c(self + 0x8a0, self, 2);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, OWNER, OWNER);
                if (*(void **) (self + 0x830) && func_0207f150(*(void **) (self + 0x830)) != 3) {
                    STATE = 12;
                } else {
                    switch (func_0201cddc(self)) {
                        case 1:
                            STATE = 3;
                            break;
                        case 0:
                            STATE = 5;
                            break;
                        case 8:
                        case 9:
                            STATE = 11;
                            break;
                        default:
                            STATE = 0;
                            break;
                    }
                }
                func_ov004_0221eb6c(self + 0x8a0, self, 2);
            }
            break;
        case 0:
            *(u8 *) (self + 0x560) = player;
            if (player != 4 && player != OWNER) {
                func_0201c054(self, 1, player, player);
                func_ov004_0221eb6c(self + 0x8a0, self, 4);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, OWNER, OWNER);
                func_0202dc3c(self + 0x680, self, STATE);
                func_02016108(self + 0x680, func_0201c2a4(self, 4));
                func_ov004_0221eb6c(self + 0x8a0, self, 1);
                STATE = 0;
            }
            break;
        case 8:
            if (player == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, OWNER, 4);
                    if (!func_ov004_0221eb44(self + 0x8a0, self)) {
                        func_ov004_0221eb6c(self + 0x8a0, self, 0);
                    }
                } else {
                    func_0201c054(self, 1, 4, OWNER);
                    func_ov004_0221eb6c(self + 0x8a0, self, 3);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                int a = 4, b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if ((player != 4 && player == b) || player == 4) {
                        func_0201c054(self, 1, OWNER, 4);
                        if (!func_ov004_0221eb44(self + 0x8a0, self)) {
                            func_ov004_0221eb6c(self + 0x8a0, self, 0);
                        }
                    }
                }
            }
            break;
    }
}
