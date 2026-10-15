/* func_ov004_02223dcc @ 0x02223dcc, 0x450 bytes, Thumb, module ov004
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
extern char *func_020984e8(void);
extern char *func_02099670(char *);
extern int func_02088bd4(char *);
extern void func_0201ad18(char *, u8, int, int, char *, int, int, u8);
extern int func_02019d0c(char *, int, int, int, int, short, short, int, int, u16, u16);
extern int func_02019de8(char *);
extern int func_02019c20(char *, int, int, char, u16, u16);
extern int func_ov004_0222dcdc(void);
extern int func_ov004_0222dd1c(void);
extern int func_ov004_0222dcbc(void);
extern int func_ov004_0222dcfc(void);
extern int func_ov004_0222dc9c(void);
extern void func_0201b38c(char *, int);
extern void func_0201b388(char *, int);
extern void func_0201b384(char *, int);
extern int func_0200442c(char *, int, int, int);
extern void func_0201af1c(char *, int);
extern void func_0206844c(char *, u8 *, int);
extern void func_ov004_0222421c(char *, int);
void func_ov004_02223dcc(char *self)
{
    char *owner = PTR(self, 0x40);
    u8 id = (func_02088bd4(func_02099670(func_020984e8())) >> 2) + 0x24;
    char *anim = PTR(self, 0xb4) + 0x564;
    switch (BYTE(self, 0xb8)) {
        case 0:
            if (WORD(owner, 4) != 5) {
                break;
            }
            func_0201ad18(PTR(self, 0xb4) + 0x3b0, 0, 0, 0, data_021fbee8, 4, data_020c814c, 1);
            func_02019d0c(anim, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 1;
            break;
        case 1:
            if (!func_02019de8(anim)) {
                break;
            }
            func_02019c20(anim, 1, 0xf6, 1, data_020c80f8, 0);
            func_ov004_0222dcdc();
            func_0201b38c(PTR(self, 0xb4) + 0x2a0, 0xf3);
            func_0201b388(PTR(self, 0xb4) + 0x2a0, 0xf5);
            func_0201b384(PTR(self, 0xb4) + 0x2a0, 0xf5);
            BYTE(self, 0xb8) = 2;
            HALF(PTR(self, 0xb4), 0x77c) = 0;
            break;
        case 2:
            HALF(PTR(self, 0xb4), 0x77c)++;
            if (HALF(PTR(self, 0xb4), 0x77c) == 5) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4db, 0x7f, 0);
            }
            if (!func_02019de8(anim)) {
                break;
            }
            func_0201af1c(PTR(self, 0xb4) + 0x350, 2);
            func_02019d0c(anim, 3, 1, 0, 0, 0, -0x8000, 0, 0, data_020c80f8, 0);
            func_ov004_0222dd1c();
            BYTE(self, 0xb8) = 3;
            break;
        case 3:
            if (!func_02019de8(anim)) {
                break;
            }
            func_02019d0c(anim, 2, 1, 0x19700, 0x14000, 0, 0, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 4;
            break;
        case 4:
            if (!func_02019de8(anim)) {
                break;
            }
            func_0201af1c(PTR(self, 0xb4) + 0x350, 0);
            func_02019d0c(anim, 3, 1, 0, 0, 0, -0x4000, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 5;
            break;
        case 5:
            if (!func_02019de8(anim)) {
                break;
            }
            func_02019c20(anim, 1, 0xf7, 1, data_020c80f8, 0);
            func_ov004_0222dcbc();
            BYTE(self, 0xb8) = 6;
            HALF(PTR(self, 0xb4), 0x77c) = 0;
            break;
        case 6:
            HALF(PTR(self, 0xb4), 0x77c)++;
            if (HALF(PTR(self, 0xb4), 0x77c) == 13) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4dc, 0x7f, 0);
            }
            if (HALF(PTR(self, 0xb4), 0x77c) == 30) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4dd, 0x7f, 0);
            }
            if (HALF(PTR(self, 0xb4), 0x77c) == 70) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4de, 0x7f, 0);
            }
            if (!func_02019de8(anim)) {
                break;
            }
            func_ov004_0222dcfc();
            func_02019d0c(anim, 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 7;
            break;
        case 7:
            if (!func_02019de8(anim)) {
                break;
            }
            func_02019d0c(anim, 2, 1, 0x19700, 0x15000, 0, 0, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 8;
            break;
        case 8:
            if (!func_02019de8(anim)) {
                break;
            }
            func_02019d0c(anim, 3, 1, 0, 0, 0, -0x4000, 0, 0, data_020c80f8, 0);
            BYTE(self, 0xb8) = 9;
            break;
        case 9:
            if (!func_02019de8(anim)) {
                break;
            }
            func_0201ad18(PTR(self, 0xb4) + 0x3b0, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
            func_02019c20(anim, 1, 0xf8, 1, data_020c80f8, 0);
            func_ov004_0222dc9c();
            BYTE(self, 0xb8) = 10;
            HALF(PTR(self, 0xb4), 0x77c) = 0;
            break;
        case 10:
            HALF(PTR(self, 0xb4), 0x77c)++;
            if (HALF(PTR(self, 0xb4), 0x77c) == 15) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4df, 0x7f, 0);
            }
            if (HALF(PTR(self, 0xb4), 0x77c) == 30) {
                func_0200442c(PTR(self, 0xb4) + 0x514, 0x4e0, 0x7f, 0);
            }
            if (!func_02019de8(anim)) {
                break;
            }
            {
                u8 selected = id;
                func_0206844c(owner, &selected, data_ov004_02254594);
            }
            WORD(owner, 8) = 1;
            func_ov004_0222421c(self, 0);
            break;
    }
}
