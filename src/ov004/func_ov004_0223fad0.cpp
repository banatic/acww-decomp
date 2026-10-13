/* func_ov004_0223fad0 @ 0x0223fad0, 0x654 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// The empty destructor keeps one 12-byte temporary per case, which gives the 0x2A0-byte frame.
struct Vec {
    int x, y, z;
    Vec(int a, int b, int c) : x(a), y(b), z(c) {}
    ~Vec() {}
};
extern "C" int func_ov004_0223ea78(void);
extern "C" int FX_MulFunc(int, int);
extern "C" void func_ov004_0223fad0(void *unused, char *entry)
{
    Vec *p = (Vec *) (entry + 0x2c8);
    int mask = func_ov004_0223ea78();
    switch (*(signed char *) (entry + 0x196)) {
        case 0:
            *p = Vec(0x176, 0x13, 0x71);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 1:
            *p = Vec(0x170, 0x13, 0x9c);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 2:
            *p = Vec(0x17f, 0x13, 0x85);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 3:
            *p = Vec(0x177, 0x13, 0xd0);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 4:
            *p = Vec(0x184, 0x13, 0xb5);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 5:
            *p = Vec(0x187, 0x13, 0xe4);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 6:
            *p = Vec(0x178, 0x13, 0xfb);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 7:
            *p = Vec(0x170, 0x13, 0x123);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 8:
            *p = Vec(0x128, 0x40, 0x66);
            *(u8 *) (entry + 0x22) = mask & 0x21;
            break;
        case 9:
            *p = Vec(0x82, 0x1c, 0x1aa);
            *(u8 *) (entry + 0x22) = mask & 0x21;
            break;
        case 10:
            *p = Vec(0xd0, 0x13, 0xfc);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 11:
            *p = Vec(0x86, 0x26, 0x1a6);
            *(u8 *) (entry + 0x22) = mask & 0xe;
            break;
        case 12:
            *p = Vec(0x146, 0x8, 0xf6);
            *(u8 *) (entry + 0x22) = mask & 0x1c;
            break;
        case 13:
            *p = Vec(0x185, 0x8, 0x140);
            *(u8 *) (entry + 0x22) = mask & 0x1c;
            break;
        case 14:
            *p = Vec(0xb5, 0x13, 0x141);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 15:
            *p = Vec(0x181, 0x13, 0x13f);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 16:
            *p = Vec(0x8e, 0x24, 0xd1);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 17:
            *p = Vec(0x8a, 0x1a, 0xd5);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 18:
            *p = Vec(0xbe, 0x1a, 0x4d);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 19:
            *p = Vec(0xb8, 0x22, 0x4b);
            *(u8 *) (entry + 0x22) = mask & 0x1a;
            break;
        case 20:
            *p = Vec(0xf1, 0x24, 0x3d);
            *(u8 *) (entry + 0x22) = mask & 0x1b;
            break;
        case 21:
            *p = Vec(0x16c, 0x14, 0xd2);
            *(u8 *) (entry + 0x22) = mask & 0x1c;
            break;
        case 22:
            *p = Vec(0x132, 0x14, 0x10d);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 23:
            *p = Vec(0x178, 0x14, 0x122);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 24:
            *p = Vec(0x89, 0x9, 0x104);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 25:
            *p = Vec(0x7a, 0x0, 0x12c);
            *(u8 *) (entry + 0x22) = mask & 0x1c;
            break;
        case 26:
            *p = Vec(0xaa, 0x13, 0xfa);
            *(u8 *) (entry + 0x22) = mask & 0x1c;
            break;
        case 27:
            *p = Vec(0x15e, 0x8, 0x118);
            *(u8 *) (entry + 0x22) = mask & 0x33;
            break;
        case 28:
            *p = Vec(0x19f, 0x8, 0x11a);
            *(u8 *) (entry + 0x22) = mask & 0x33;
            break;
        case 29:
            *p = Vec(0x16f, 0x8, 0xf2);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 30:
            *p = Vec(0xe2, 0x8, 0x13e);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 31:
            *p = Vec(0x1a2, 0x24, 0x4c);
            *(u8 *) (entry + 0x22) = mask & 0x1e;
            break;
        case 32:
            *p = Vec(0x91, 0x13, 0xdf);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 33:
            *p = Vec(0x82, 0x18, 0x65);
            *(u8 *) (entry + 0x22) = mask & 0x33;
            break;
        case 34:
            *p = Vec(0x88, 0x22, 0x62);
            *(u8 *) (entry + 0x22) = mask & 0x3;
            break;
        case 35:
        // Preset 56 shares the case-35 body.
        case 56:
            *p = Vec(0x165, 0x8, 0xec);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 36:
            *p = Vec(0xae, 0x2a, 0xcd);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 37:
            *p = Vec(0x53, 0x13, 0x146);
            *(u8 *) (entry + 0x22) = mask & 0x21;
            break;
        case 38:
            *p = Vec(0xeb, 0x16, 0x42);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 39:
            *p = Vec(0x122, 0x22, 0x52);
            *(u8 *) (entry + 0x22) = mask & 0xc;
            break;
        case 40:
            *p = Vec(0x128, 0x18, 0x55);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 41:
            *p = Vec(0x15e, 0x16, 0x47);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 42:
            *p = Vec(0x164, 0x20, 0x43);
            *(u8 *) (entry + 0x22) = mask & 0x3;
            break;
        case 43:
            *p = Vec(0x82, 0x21, 0x138);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 44:
            *p = Vec(0x19c, 0x16, 0x51);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 45:
            *p = Vec(0xaa, 0x1a, 0xd3);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 46:
            *p = Vec(0x79, 0x1a, 0xe8);
            *(u8 *) (entry + 0x22) = mask & 0x23;
            break;
        case 47:
            *p = Vec(0x7d, 0x2a, 0xe2);
            *(u8 *) (entry + 0x22) = mask & 0x3;
            break;
        case 48:
            *p = Vec(0x12c, 0x0, 0x12c);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 49:
            *p = Vec(0x0, 0x0, 0x0);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 50:
            *p = Vec(0xb4, 0x19, 0xfa);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 51:
            *p = Vec(0x118, 0x23, 0xf0);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 52:
            *p = Vec(0x14a, 0x0, 0xb4);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 53:
            *p = Vec(0x96, 0x29, 0x133);
            *(u8 *) (entry + 0x22) = mask & 0x3f;
            break;
        case 54:
            *p = Vec(0x134, 0x8, 0x11e);
            *(u8 *) (entry + 0x22) = mask & 0x21;
            break;
        case 55:
            *p = Vec(0x128, 0x8, 0x136);
            *(u8 *) (entry + 0x22) = mask & 0x21;
            break;
    }
    p->x = FX_MulFunc(p->x << 12, 0x100);
    p->y = FX_MulFunc(p->y << 12, 0x100);
    p->z = FX_MulFunc(p->z << 12, 0x100);
}
