/* func_ov003_02220e20 @ 0x02220e20, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} UnkStruct_02220e20;
typedef struct {
    int x, y, z;
} UnkStruct_02220e20_2;

extern int func_ov003_022213f8(int *data, int a1, int *pair, int *dest, int a5, int a6, int a7, int a8);
extern int data_ov003_0223cfe4[];

void func_ov003_02220e20(int a0, int id, UnkStruct_02220e20 *p2, UnkStruct_02220e20_2 *p3)
{
    volatile unsigned short t = 0xfff1;
    unsigned int h, g, f, e, d, c, b, a;
    unsigned short lo, hi;
    int pair[2];
    int dest[3];

    t = (unsigned short) id;
    h = 1;
    g = 1;
    f = 1;
    e = 1;
    d = 1;
    c = 1;
    b = 1;
    a = 0;
    lo = t;
    hi = t;
    if (hi <= 5) {
        a = 1;
    }
    if (a == 0) {
        if (!(lo >= 6 && lo <= 0xb)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(lo >= 0xc && lo <= 0x11)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
            d = 0;
        }
    }
    if (d == 0) {
        if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
              (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
            e = 0;
        }
    }
    if (e == 0) {
        if (lo != 0x1a) {
            f = 0;
        }
    }
    if (f == 0) {
        if (lo != 0xa4) {
            g = 0;
        }
    }
    if (g == 0) {
        if (lo != 0x1d) {
            h = 0;
        }
    }
    if (h != 0 || (lo >= 0x14fe && lo <= 0x1517) || id == 0x1567) {
        id = 0x1408;
    }

    dest[0] = p3->x;
    dest[1] = p3->y;
    dest[2] = p3->z;
    pair[0] = p2->x;
    pair[1] = p2->y;
    func_ov003_022213f8(data_ov003_0223cfe4, a0, pair, dest, 9, id, 0, 0);
}
