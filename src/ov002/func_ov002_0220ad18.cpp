/* func_ov002_0220ad18 @ 0x0220ad18, 0x25c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0220ad18 {
  public:
    virtual void vf0();
    virtual void vf4();
    virtual void vf8();
};

extern "C" void func_ov002_0220b1a4(void *a, int b, int c, int d);
extern "C" void func_0208aa60(void *a, int b, int c);

extern "C" void func_ov002_0220ad18(char *self, int n)
{
    u8 k;
    UnkStruct_0220ad18 *p;
    int m;

    k = *(u8 *) (self + 0x1c8);
    switch (k) {
        case 0:
            break;
        case 1:
            func_ov002_0220b1a4(self + 0x80, 0, n + 0xac, -1);
            break;
        case 2:
            func_ov002_0220b1a4(self + 4, 0, n + 0xac, -1);
            func_ov002_0220b1a4(self + 0x80, 0, n + 0xac, -1);
            break;
        case 3:
            func_ov002_0220b1a4(self + 0x80, 0x3c, n + 0x35, -1);
            func_ov002_0220b1a4(self + 4, 0x3c, n + 0x48, -1);
            break;
        case 4:
            func_ov002_0220b1a4(self + 0x80, 0x3c, n + 0x4c, -1);
            func_ov002_0220b1a4(self + 4, -0x7c, n + 0x4c, -1);
            break;
        case 5:
            func_ov002_0220b1a4(self + 0x80, 0x3c, n + 0x4c, -1);
            break;
        case 6:
            func_ov002_0220b1a4(self + 0x80, 0x3c, n + 0x4c, -1);
            func_ov002_0220b1a4(self + 4, -0xc, n + 0x4c, -1);
            break;
        case 7:
        case 9:
        case 10:
            if (k != 0xa) {
                func_0208aa60(self + 0xfc, 0, -(n >> 2));
                p = (UnkStruct_0220ad18 *) (self + 0xfc);
                p->vf8();
            }
            m = n >> 2;
            if (*(u8 *) (self + 0x1c8) == 7) {
                func_ov002_0220b1a4(self + 4, 0, m, -1);
                func_ov002_0220b1a4(self + 0x80, 0, m, -1);
            } else {
                func_ov002_0220b1a4(self + 4, -0x50, m + 0x44, -1);
                func_ov002_0220b1a4(self + 0x80, 0x10, m + 0x44, -1);
            }
            break;
        case 8:
            m = -(n >> 2);
            if (k != 0xa) {
                func_0208aa60(self + 0xfc, 0, m - 8);
                p = (UnkStruct_0220ad18 *) (self + 0xfc);
                p->vf8();
            }
            m = (n >> 1) - 0x1e;
            func_ov002_0220b1a4(self + 4, 0, m, -1);
            func_ov002_0220b1a4(self + 0x80, 0, m, -1);
            break;
        case 11:
            m = n >> 1;
            func_0208aa60(self + 0xfc, 0, -m);
            p = (UnkStruct_0220ad18 *) (self + 0xfc);
            p->vf8();
            func_ov002_0220b1a4(self + 4, -0x50, m + 0x44, -1);
            func_ov002_0220b1a4(self + 0x80, 0x10, m + 0x44, -1);
            break;
        case 12:
            m = n >> 1;
            func_0208aa60(self + 0xfc, 0, -m);
            p = (UnkStruct_0220ad18 *) (self + 0xfc);
            p->vf8();
            func_ov002_0220b1a4(self + 4, -0x50, m + 0x24, -1);
            func_ov002_0220b1a4(self + 0x80, 0x10, m + 0x24, -1);
            break;
        case 13:
            m = n >> 1;
            func_0208aa60(self + 0xfc, 0, -m);
            p = (UnkStruct_0220ad18 *) (self + 0xfc);
            p->vf8();
            func_ov002_0220b1a4(self + 4, -0x50, m + 0x36, -1);
            func_ov002_0220b1a4(self + 0x80, 0x10, m + 0x36, -1);
            break;
    }
}
