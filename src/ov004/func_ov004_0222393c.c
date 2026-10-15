/* func_ov004_0222393c @ 0x0222393c, 0x2e0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define PTR(o, k) (*(char **) ((o) + (k)))
#define BYTE(o, k) (*(u8 *) ((o) + (k)))
#define HALF(o, k) (*(u16 *) ((o) + (k)))
#define WORD(o, k) (*(int *) ((o) + (k)))
extern char data_021fbee8[];
extern int data_020c814c;
extern u16 data_020c80f8;
extern int data_ov004_02254594;
extern char *func_020984e8(void), *func_02099670(char *);
extern int func_02088bd4(char *);
extern int func_ov004_0222be34(void);
extern int func_ov004_0222dc1c(void), func_ov004_0222db58(void), func_ov004_0222dc7c(void), func_ov004_0222dd1c(void),
    func_ov004_0222dc5c(void), func_ov004_0222dd3c(void);
extern void func_0203ab50(void);
extern void func_0201ad18(char *, u8, int, int, char *, int, int, u8);
extern int func_02019d0c(char *, int, int, int, int, short, short, int, int, u16, u16);
extern int func_02019de8(char *);
extern int func_02019c20(char *, int, int, char, u16, u16);
extern void func_0201b38c(char *, int), func_0201b388(char *, int), func_0201b384(char *, int);
extern int func_0200442c(char *, int, int, int);
extern void func_0206844c(char *, u8 *, int);
extern void func_ov004_0222421c(char *, int);
void func_ov004_0222393c(char *self)
{
    char *owner = PTR(self, 0x40);
    u8 id = (func_02088bd4(func_02099670(func_020984e8())) >> 2) + 0x51;
    char *anim = PTR(self, 0xb4) + 0x564;
    switch (BYTE(self, 0xb8)) {
        case 0:
            if (WORD(owner, 4) != 5) {
                break;
            }
            func_ov004_0222be34();
            func_ov004_0222dc1c();
            BYTE(self, 0xb8) = 1;
            HALF(PTR(self, 0xb4), 0x77c) = 0;
            break;
        case 1:
            HALF(PTR(self, 0xb4), 0x77c)++;
            if (HALF(PTR(self, 0xb4), 0x77c) == 15) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4e6, 0x7f, 0);
            }
            if (HALF(PTR(self, 0xb4), 0x77c) == 20) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4e7, 0x7f, 0);
            }
            if (!func_ov004_0222db58()) {
                break;
            }
            func_0203ab50();
            func_0201ad18(PTR(self, 0xb4) + 0x3b0, 0, 0, 0, data_021fbee8, 4, data_020c814c, 1);
            func_02019c20(anim, 4, 0xf8, 3, data_020c80f8, 0);
            func_ov004_0222dc7c();
            BYTE(self, 0xb8) = 2;
            HALF(PTR(self, 0xb4), 0x77c) = 0;
            break;
        case 2:
            HALF(PTR(self, 0xb4), 0x77c)++;
            if (HALF(PTR(self, 0xb4), 0x77c) == 18) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4e8, 0x7f, 0);
            }
            if (HALF(PTR(self, 0xb4), 0x77c) == 45) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4e9, 0x7f, 0);
            }
            if (!func_02019de8(anim)) {
                break;
            }
            func_ov004_0222dd1c();
            func_02019d0c(anim, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 3;
            break;
        case 3:
            if (!func_02019de8(anim)) {
                break;
            }
            func_02019c20(anim, 1, 0xf6, 3, data_020c80f8, 0);
            func_ov004_0222dc5c();
            func_0201b38c(PTR(self, 0xb4) + 0x2a0, 0xf2);
            func_0201b388(PTR(self, 0xb4) + 0x2a0, 0xf4);
            func_0201b384(PTR(self, 0xb4) + 0x2a0, 0xf4);
            BYTE(self, 0xb8) = 4;
            HALF(PTR(self, 0xb4), 0x77c) = 0;
            break;
        case 4:
            HALF(PTR(self, 0xb4), 0x77c)++;
            if (HALF(PTR(self, 0xb4), 0x77c) == 10) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4ea, 0x7f, 0);
            }
            if (!func_02019de8(anim)) {
                break;
            }
            func_ov004_0222dd3c();
            func_0201ad18(PTR(self, 0xb4) + 0x3b0, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
            func_02019d0c(anim, 3, 1, 0, 0, 0, -0x4000, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 5;
            break;
        case 5:
            if (!func_02019de8(anim)) {
                break;
            }
            {
                u8 selected = id;
                func_0206844c(owner, &selected, data_ov004_02254594);
            }
            WORD(owner, 8) = 1;
            func_ov004_0222421c(self, 0);
            BYTE(self, 0xb9) = 0;
            break;
    }
}
