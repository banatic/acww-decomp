/* func_02045f24 @ 0x02045f24, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;

typedef struct {
    u8 low3 : 3;
    u8 kind : 5;
    u8 p1 : 7;
    u8 flag : 1;
    u8 pad_02[10];
    u16 w;
    u16 pad_0E;
} UnkStruct_02045f24;

extern UnkStruct_02045f24 data_021c7884[];

extern int func_02045cec(Pt *a, u8 b);
extern void func_ov003_02222d8c(u16 *a, int b, Pt *c);
extern void func_0204629c(UnkStruct_02045f24 *e);
extern int func_020460ec(void *a, Pt *b, void *c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10);
extern int func_02046194(int i, void *a, Pt *b, void *c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10);

int func_02045f24(void *a, Pt *b, void *c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10)
{
    u16 u;
    Pt t1;
    Pt t2;
    Pt t3;
    Pt t4;
    int i;
    UnkStruct_02045f24 *e;

    t1.x = b->x;
    t1.y = b->y;
    i = func_02045cec(&t1, p9);
    if (i >= 0) {
        e = &data_021c7884[i];
        if (!e->flag) {
            switch (e->kind) {
                case 1:
                case 2:
                case 6:
                case 7:
                    u = 0xfff1;
                    u = e->w;
                    t2.x = b->x;
                    t2.y = b->y;
                    func_ov003_02222d8c(&u, e->low3, &t2);
                    break;
            }
            func_0204629c(e);
        }
        t3.x = b->x;
        t3.y = b->y;
        return func_02046194(i, a, &t3, c, d, p5, p6, p7, p8, p9, p10);
    } else {
        t4.x = b->x;
        t4.y = b->y;
        return func_020460ec(a, &t4, c, d, p5, p6, p7, p8, p9, p10);
    }
}
