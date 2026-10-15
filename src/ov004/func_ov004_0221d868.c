/* func_ov004_0221d868 @ 0x0221d868, 0xc4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 func_020e8ed8(int dx, int dy);
extern char *func_ov004_0221d4e8(void);
extern int func_ov004_0221c844(char *g, int mode);
extern int func_02019d0c(char *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0201ad18(char *p, int a, int b, char *c, int d, int e, int f, int g);
extern char *data_ov004_02257a18;
extern u16 data_020c80f8;
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_ov004_0221d868(char *self)
{
    // DECLS
    char *o;
    char *m;
    char *g;
    int r;
    // ENDDECLS

    if (*(u16 *) (self + 0xa4e) == 0) {
        m = self + 0x564;
        o = func_ov004_0221d4e8();
        if (o != 0) {
            *(short *) (self + 0xa50) =
                func_020e8ed8(*(int *) (o + 0x5c) - *(int *) (self + 0x5c), *(int *) (o + 0x64) - *(int *) (self + 0x64));
            g = data_ov004_02257a18;
            if (g != 0 && *(unsigned int *) (g + 0x898) <= 1) {
                r = func_ov004_0221c844(g, 1);
            } else {
                r = 0;
            }
            if (r != 0) {
                func_02019d0c(m, 3, 1, 0, 0, 0, *(short *) (self + 0xa50), 0, 0, data_020c80f8, 0);
                func_0201ad18(self + 0x3b0, 2, 0, o, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
                return 1;
            }
        }
    }
    return 0;
}
