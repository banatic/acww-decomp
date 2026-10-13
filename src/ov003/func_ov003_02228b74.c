/* func_ov003_02228b74 @ 0x02228b74, 0x160 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_0225f76c[];
extern char data_ov003_0225f4dc[];
extern char data_ov003_0223c0b4[];
extern char data_ov003_0223c0c0[];
extern int data_ov003_0223bdac;
extern int data_021fbe94;
extern int data_020ccf94;
extern void func_0205c960(void);
extern void func_0205c944(void);
extern void func_0205c92c(void);
extern void func_0205c910(void);
extern void func_0209d180(char *p, int a, int b, int c, int d, void (*e)(void), void (*f)(void), char *g);
extern int func_02064b2c(int a, int b, int c, int d);
extern void func_ov003_02227778(char *rec, int h, char *p);
extern void func_0200451c(char *p);
extern void func_0200430c(char *p);
extern int func_02073d90(int a);
extern int func_02073918(int a, int b);
extern int func_0204fee8(u8 a);
extern void func_0204ff00(u8 a, int b, int c, int d, int e);

int func_ov003_02228b74(char *self)
{
    char *rec;
    int i;
    int z;
    int m;
    func_0209d180(self + 0x50, 6, 0, 0, 0x800, func_0205c960, func_0205c944, data_ov003_0223c0b4);
    func_0209d180(self + 0x68, 1, 0x400, 0x80, 0x800, func_0205c92c, func_0205c910, data_ov003_0223c0c0);
    *(int *) (self + 0x80) = func_02064b2c(data_ov003_0223bdac, data_021fbe94, 4, 0);
    rec = data_ov003_0225f76c;
    i = 0;
    z = i;
    do {
        func_ov003_02227778(rec, *(int *) (self + 0x80), self + 0x50);
        if (i < 3) {
            *(u8 *) (rec + 0x1fc) = 3;
        } else if (i < 6) {
            *(u8 *) (rec + 0x1fc) = 4;
        }
        {
            int *q = (int *) (rec + 0x208);
            q[0] = i;
            q[1] = z;
        }
        *(u8 *) (rec + 0x211) = i;
        *(short *) (rec + 0x212) = i * 0x190 + 0x960;
        func_0200451c(rec);
        func_0200430c(rec + 0x40);
        rec += 0x24c;
        i++;
    } while (i < 6);
    rec = data_ov003_0225f4dc;
    i = 0;
    m = data_020ccf94;
    z = i;
    do {
        if (func_02073d90(m) != 0 && func_02073918(m, i) == 0 && func_0204fee8(i) == 3) {
            func_0204ff00(i, 6, -1, z, z);
        }
        func_0200451c(rec);
        rec += 0xa4;
        i++;
    } while (i < 4);
    return 1;
}
