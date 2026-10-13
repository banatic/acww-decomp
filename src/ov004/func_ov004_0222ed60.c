/* func_ov004_0222ed60 @ 0x0222ed60, 0x2c8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define BYTE(p, o) (*(u8 *) ((p) + (o)))
#define HALF(p, o) (*(u16 *) ((p) + (o)))
#define WORD(p, o) (*(u32 *) ((p) + (o)))
extern char *data_ov004_02258310;
extern char data_ov004_02255030[], data_ov004_02255048[], data_ov004_02255064[], data_ov004_0225507c[];
extern char data_ov004_02255098[], data_ov004_022550b0[], data_ov004_022550cc[], data_ov004_022550e4[];
extern char data_ov004_02255100[], data_ov004_02255118[], data_ov004_02255134[], data_ov004_0225514c[];
extern void *data_021c9b24;
extern Vec data_ov004_02258318, data_ov004_02258330;
extern void func_ov004_0222c600(char *, char *, char *);
extern void func_ov004_0222de14(char *, int, char *, char *);
extern void *func_ov004_0222c3c4(char *, int);
extern int func_02055140(char *, void *);
extern void func_02055060(char *, void *, int, int, u16, u16);
extern int func_02055050(char *);
extern void func_ov004_0222dd5c(char *, int);
extern int func_ov004_0222e73c(char *, int);
extern void func_ov004_0222db14(char *, int, char *, char *, u8, int, u16, u16);
int func_ov004_0222ed60(char *self)
{
    u8 i;
    data_ov004_02258310 = self;
    func_ov004_0222c600(self, data_ov004_02255030, data_ov004_02255048);
    func_ov004_0222de14(self, 0, data_ov004_02255064, data_ov004_0225507c);
    func_ov004_0222de14(self, 1, data_ov004_02255098, data_ov004_022550b0);
    func_ov004_0222de14(self, 2, data_ov004_022550cc, data_ov004_022550e4);
    func_ov004_0222de14(self, 3, data_ov004_02255100, data_ov004_02255118);
    func_ov004_0222de14(self, 4, data_ov004_02255098, data_ov004_022550b0);
    func_ov004_0222de14(self, 5, data_ov004_022550cc, data_ov004_022550e4);
    func_ov004_0222de14(self, 6, data_ov004_02255098, data_ov004_022550b0);
    func_ov004_0222de14(self, 7, data_ov004_022550cc, data_ov004_022550e4);
    func_ov004_0222de14(self, 8, data_ov004_02255134, data_ov004_0225514c);
    if (func_ov004_0222c3c4(self + 0x1a4, 0)) {
        if (func_02055140(self + 0xec, data_021c9b24)) {
            func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 1, 0x1000, 0, 0);
            func_02055050(self + 0xec);
            WORD(self, 0x198) = 0;
        }
    }
    for (i = 0; i < 9; i++) {
        func_ov004_0222dd5c(self, i);
    }
    func_ov004_0222e73c(self, 0);
    BYTE(self, 0xef3) = 1;
    func_ov004_0222db14(self, 8, self + 0x570, self + 0xb98, 0, 0x1000, 0, 0);
    func_ov004_0222db14(self, 6, self + 0x628, self + 0xc3c, 0, 0x1000, 0, 0);
    func_ov004_0222db14(self, 8, self + 0x6e0, self + 0xce0, 0, 0x1000, 0, 0);
    func_ov004_0222db14(self, 6, self + 0x798, self + 0xd84, 0, 0x1000, 0, 0);
    WORD(self, 0xf1c) = data_ov004_02258318.x;
    WORD(self, 0xf20) = data_ov004_02258318.y;
    WORD(self, 0xf24) = data_ov004_02258318.z;
    WORD(self, 0xf28) = data_ov004_02258330.x;
    WORD(self, 0xf2c) = data_ov004_02258330.y;
    WORD(self, 0xf30) = data_ov004_02258330.z;
    HALF(self, 0xf34) = 0;
    HALF(self, 0xf36) = 0;
    WORD(self, 0x61c) = 0;
    WORD(self, 0x614) = (u16) (((WORD(self, 0x610) << 4) >> 16) - 1) << 12;
    WORD(self, 0x6d4) = 0;
    WORD(self, 0x6cc) = (u16) (((WORD(self, 0x6c8) << 4) >> 16) - 1) << 12;
    WORD(self, 0x78c) = 0;
    WORD(self, 0x784) = (u16) (((WORD(self, 0x780) << 4) >> 16) - 1) << 12;
    WORD(self, 0x844) = 0;
    WORD(self, 0x83c) = (u16) (((WORD(self, 0x838) << 4) >> 16) - 1) << 12;
    WORD(self, 0xf38) = -1;
    WORD(self, 0xf3c) = -1;
    WORD(self, 0xf40) = -1;
    return 1;
}
