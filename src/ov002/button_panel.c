/* button_panel: 30 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220ad0c @ 0x0220ad0c, 0xc bytes, Thumb
 * func_ov002_0220acc4 @ 0x0220acc4, 0x48 bytes, Thumb
 * func_ov002_0220ac7c @ 0x0220ac7c, 0x48 bytes, Thumb
 * func_ov002_0220ac4c @ 0x0220ac4c, 0x30 bytes, Thumb
 * func_ov002_0220ac04 @ 0x0220ac04, 0x48 bytes, Thumb
 * func_ov002_0220abbc @ 0x0220abbc, 0x48 bytes, Thumb
 * func_ov002_0220ab84 @ 0x0220ab84, 0x38 bytes, Thumb
 * func_ov002_0220ab38 @ 0x0220ab38, 0x4c bytes, Thumb
 * func_ov002_0220aacc @ 0x0220aacc, 0x6c bytes, Thumb
 * func_ov002_0220aa60 @ 0x0220aa60, 0x6c bytes, Thumb
 * func_ov002_0220aa20 @ 0x0220aa20, 0x40 bytes, Thumb
 * func_ov002_0220a9e4 @ 0x0220a9e4, 0x3c bytes, Thumb
 * func_ov002_0220a99c @ 0x0220a99c, 0x48 bytes, Thumb
 * func_ov002_0220a960 @ 0x0220a960, 0x3c bytes, Thumb
 * func_ov002_0220a924 @ 0x0220a924, 0x3c bytes, Thumb
 * func_ov002_0220a8e8 @ 0x0220a8e8, 0x3c bytes, Thumb
 * func_ov002_0220a8dc @ 0x0220a8dc, 0xc bytes, Thumb
 * func_ov002_0220a7c0 @ 0x0220a7c0, 0x11c bytes, Thumb
 * func_ov002_0220a784 @ 0x0220a784, 0x3c bytes, Thumb
 * func_ov002_0220a768 @ 0x0220a768, 0x1c bytes, Thumb
 * func_ov002_0220a72c @ 0x0220a72c, 0x3c bytes, Thumb
 * func_ov002_0220a720 @ 0x0220a720, 0xc bytes, Thumb
 * func_ov002_0220a700 @ 0x0220a700, 0x1e bytes, Thumb
 * func_ov002_0220a6e0 @ 0x0220a6e0, 0x1e bytes, Thumb
 * func_ov002_0220a6b8 @ 0x0220a6b8, 0x26 bytes, Thumb
 * func_ov002_0220a690 @ 0x0220a690, 0x26 bytes, Thumb
 * func_ov002_0220a674 @ 0x0220a674, 0x1c bytes, Thumb
 * func_ov002_0220a658 @ 0x0220a658, 0x1a bytes, Thumb
 * func_ov002_0220a63c @ 0x0220a63c, 0x1a bytes, Thumb
 * func_ov002_0220a620 @ 0x0220a620, 0x1a bytes, Thumb
 */

#include "types.h"

extern void func_ov002_0220b338(char *self, int value);
extern void *data_ov002_0220bde0;
extern void *data_ov002_0220bdc0;
extern void *data_ov002_0220be68;
extern void func_ov002_0220b36c(void *, void *, int, int);
extern void *data_ov002_0220be08;
extern void *data_ov002_0220be38;
extern void func_0208aa68(char *p);
extern void *data_ov002_0220bd38;
extern void *data_ov002_0220bd20;
extern void func_ov002_0220b04c(void *);
extern void func_ov002_0220b06c(void *, int, int, int);
extern void func_0208aa70(void *);
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern const u8 data_ov002_0220ba5c[];
extern const u8 data_ov002_0220ba68[];
extern int func_ov002_0220b168(char *p);
extern int func_ov002_0220b280(char *p);
extern void func_0208aa98(void *);
extern void func_ov002_0220b15c(void *);
extern void func_0208aa90(void *);
extern void func_ov002_0220b150(void *);
extern const u8 data_ov002_0220ba74[];
extern void func_ov002_0220b144(char *p);
extern void func_ov002_0220b138(char *p);
extern int func_ov002_0220b12c(char *p);

int func_ov002_0220a674(u8 *self, int i);

void *func_ov002_0220ad0c(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x1c8) = 0x0;
    return self;
}

int func_ov002_0220acc4(char *self)
{
    func_ov002_0220b36c((void *) ((char *) (self + 0x4)), (void *) ((int) (&data_ov002_0220bde0)),
                        (unsigned char) ((unsigned char) (0x8)), (unsigned char) ((unsigned char) (0x2)));
    func_ov002_0220b338(self + 0x4, 0x2);
    func_ov002_0220b36c((void *) ((char *) (self + 0x80)), (void *) ((int) (&data_ov002_0220bdc0)),
                        (unsigned char) ((unsigned char) (0x6)), (unsigned char) ((unsigned char) (0x1)));
    func_ov002_0220b338(self + 0x80, 0x21);
    *(u8 *) (self + 0x1c8) = 0x2;
    return 0x1c8;
}

int func_ov002_0220ac7c(char *self)
{
    func_ov002_0220b36c((void *) ((char *) (self + 0x4)), (void *) ((int) (&data_ov002_0220be68)),
                        (unsigned char) ((unsigned char) (0xc)), (unsigned char) ((unsigned char) (0x3)));
    func_ov002_0220b338(self + 0x4, 0x20);
    func_ov002_0220b36c((void *) ((char *) (self + 0x80)), (void *) ((int) (&data_ov002_0220bdc0)),
                        (unsigned char) ((unsigned char) (0x6)), (unsigned char) ((unsigned char) (0x1)));
    func_ov002_0220b338(self + 0x80, 0x21);
    *(u8 *) (self + 0x1c8) = 0x2;
    return 0x1c8;
}

int func_ov002_0220ac4c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220bdc0, 0x6, 0x1);
    func_ov002_0220b338(self + 0x80, 0x21);
    *(u8 *) (self + 0x1c8) = 0x1;
    return 0x1c8;
}

int func_ov002_0220ac04(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, 0x21);
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be38, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, 0x65);
    *(u8 *) (self + 0x1c8) = 0x3;
    return 0x1c8;
}

int func_ov002_0220abbc(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, 0x21);
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be38, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, 0x65);
    *(u8 *) (self + 0x1c8) = 0x4;
    return 0x1c8;
}

int func_ov002_0220ab84(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, (u8) a1);
    *(u8 *) (self + 0x1c8) = 0x5;
    return 0x1c8;
}

int func_ov002_0220ab38(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, 0x21);
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be38, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, a1);
    *(u8 *) (self + 0x1c8) = 0x6;
    return 0x1c8;
}

int func_ov002_0220aacc(char *self, void *arg)
{
    func_ov002_0220b04c((void *) (self + 0xfc));
    func_ov002_0220b06c((void *) (self + 0xfc), (int) arg, 0x80, 0x4);
    func_0208aa68(self + 0xfc);
    func_ov002_0220b36c((void *) ((char *) (self + 0x4)), (void *) ((int) (&data_ov002_0220bd38)),
                        (unsigned char) ((unsigned char) (0x4)), (unsigned char) ((unsigned char) (0x1)));
    func_ov002_0220b338(self + 0x4, 0x4);
    func_ov002_0220b36c((void *) ((char *) (self + 0x80)), (void *) ((int) (&data_ov002_0220bd20)),
                        (unsigned char) ((unsigned char) (0x4)), (unsigned char) ((unsigned char) (0x1)));
    func_ov002_0220b338(self + 0x80, 0x13);
    *(u8 *) (self + 0x1c8) = 0x7;
    return 0x1c8;
}

int func_ov002_0220aa60(char *self, void *arg)
{
    func_ov002_0220b04c((void *) (self + 0xfc));
    func_ov002_0220b06c((void *) (self + 0xfc), (int) arg, 0x80, 0x11);
    func_0208aa68(self + 0xfc);
    func_ov002_0220b36c((void *) ((char *) (self + 0x4)), (void *) ((int) (&data_ov002_0220bd38)),
                        (unsigned char) ((unsigned char) (0x4)), (unsigned char) ((unsigned char) (0x1)));
    func_ov002_0220b338(self + 0x4, 0x4);
    func_ov002_0220b36c((void *) ((char *) (self + 0x80)), (void *) ((int) (&data_ov002_0220bd20)),
                        (unsigned char) ((unsigned char) (0x4)), (unsigned char) ((unsigned char) (0x1)));
    func_ov002_0220b338(self + 0x80, 0x13);
    *(u8 *) (self + 0x1c8) = 0x8;
    return 0x1c8;
}

void func_ov002_0220aa20(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, 0x4);
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be38, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, 0x13);
}

int func_ov002_0220a9e4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, a1, 0x80, 0x4);
    func_0208aa68((char *) (self + 0xfc));
    func_ov002_0220aa20(self);
    *(u8 *) (self + 0x1c8) = 0x9;
    return 0x1c8;
}

int func_ov002_0220a99c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be08, 0x6, 0x2);
    func_ov002_0220b338(self + 0x4, 0x15);
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220be38, 0x6, 0x2);
    func_ov002_0220b338(self + 0x80, 0x19);
    *(u8 *) (self + 0x1c8) = 0xa;
    return 0x1c8;
}

int func_ov002_0220a960(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, a1, 0x80, 0x22);
    func_0208aa68((char *) (self + 0xfc));
    func_ov002_0220aa20(self);
    *(u8 *) (self + 0x1c8) = 0xb;
    return 0x1c8;
}

int func_ov002_0220a924(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, a1, 0x80, 0x2a);
    func_0208aa70(self + 0xfc);
    func_ov002_0220aa20(self);
    *(u8 *) (self + 0x1c8) = 0xc;
    return 0x1c8;
}

int func_ov002_0220a8e8(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, a1, 0x80, 0x12);
    func_0208aa70(self + 0xfc);
    func_ov002_0220aa20(self);
    *(u8 *) (self + 0x1c8) = 0xd;
    return 0x1c8;
}

void func_ov002_0220a8dc(char *self)
{
    // DECLS
    // ENDDECLS
    func_0208aa70(self + 0xfc);
}

int func_ov002_0220a7c0(void *self, int i, int x, int y)
{
    switch (i) {
        case 1:
            if (x >= 0xc0 && y >= 0x95 && y < 0xa5) {
                return 1;
            }
            return 0;
        case 2:
            if (x >= 0xc0 && y >= 0xa9 && y < 0xb9) {
                return 1;
            }
            return 0;
        case 0:
            if (x >= 0x52 && x <= 0xba && y >= 0xac && y <= 0xc0) {
                return 1;
            }
            return 0;
        case 3:
            if (y >= 0xa4 && y < 0xb4 && x >= 0x38 && x <= 0x68) {
                return 1;
            }
            return 0;
        case 4:
            if (y >= 0xa4 && y < 0xb4 && x >= 0x98 && x <= 0xc8) {
                return 1;
            }
            return 0;
        case 5:
            if (y >= 0xac && y <= 0xc0 && x >= 0 && x <= 0x40) {
                return 1;
            }
            return 0;
        case 6:
            if (y >= 0xac && y <= 0xc0 && x >= 0xc0 && x <= 0x100) {
                return 1;
            }
            return 0;
        case 7:
            if (y >= 0xac && y <= 0xc0 && x >= 0x78 && x <= 0xb8) {
                return 1;
            }
            return 0;
        case 8:
            if (x >= 0x6a && x <= 0xbc && y >= 0xac && y <= 0xc0) {
                return 1;
            }
            return 0;
        case 9:
            if (x >= 0xc0 && y >= 0 && y >= 0xac && y <= 0xc0) {
                return 1;
            }
            return 0;
    }
    return 0;
}

int func_ov002_0220a784(u8 *self, int x)
{
    int a = data_021f6c58;
    int b = data_021f6c54;

    switch (self[0x1c8]) {
        case 8:
            b += 0x1e;
            break;
        case 0xc:
            b += 0x20;
            break;
        case 0xd:
            b += 0xe;
            break;
    }
    return func_ov002_0220a7c0((void *) self, x, a, b);
}

int func_ov002_0220a768(u8 *self, int i)
{
    if (i == -1) {
        i = self[0x1c9];
    }
    return data_ov002_0220ba5c[i];
}

int func_ov002_0220a72c(u8 *self, int i)
{
    int v;

    if (i == -1) {
        i = self[0x1c9];
    }
    v = data_ov002_0220ba68[i];
    switch (self[0x1c8]) {
        case 8:
            v -= 0x1e;
            break;
        case 0xc:
            v -= 0x20;
            break;
        case 0xd:
            v -= 0xe;
            break;
    }
    return v;
}

void *func_ov002_0220a720(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x1c9) = a1;
    return self;
}

int func_ov002_0220a700(char *self)
{
    return func_ov002_0220b168(self + 4 + func_ov002_0220a674((u8 *) self, -1) * 0x7c);
}

int func_ov002_0220a6e0(char *self)
{
    return func_ov002_0220b280(self + 4 + func_ov002_0220a674((u8 *) self, -1) * 0x7c);
}

void func_ov002_0220a6b8(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    func_0208aa98(self + 0xfc);
    for (i = 0; i < 0x2; i++) {
        func_ov002_0220b15c(self + 0x4 + (0x7c * i));
    }
}

void func_ov002_0220a690(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    func_0208aa90(self + 0xfc);
    for (i = 0; i < 0x2; i++) {
        func_ov002_0220b150(self + 0x4 + (0x7c * i));
    }
}

int func_ov002_0220a674(u8 *self, int i)
{
    if (i == -1) {
        i = self[0x1c9];
    }
    return data_ov002_0220ba74[i];
}

void func_ov002_0220a658(char *self, int i)
{
    func_ov002_0220b144(self + 4 + func_ov002_0220a674((u8 *) self, i) * 0x7c);
}

void func_ov002_0220a63c(char *self, int i)
{
    func_ov002_0220b138(self + 4 + func_ov002_0220a674((u8 *) self, i) * 0x7c);
}

int func_ov002_0220a620(char *self, int i)
{
    return func_ov002_0220b12c(self + 4 + func_ov002_0220a674((u8 *) self, i) * 0x7c);
}
