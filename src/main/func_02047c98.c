/* func_02047c98 @ 0x02047c98, 0x120 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pair;

typedef struct {
    u16 unk_00;
} Entry;

extern Entry *func_0204f5e0(int param1, int a, int b, int c, int d, int e);
extern int func_0204b910(Entry *e);
extern void func_0204f800(int *out0, int *out1, int a, int b, int c, int d);
extern int func_020644cc(int n);
extern unsigned short func_02047db8(int param0);
extern void func_0204a25c(int param1, int x, int y, int z, int zero);

extern const u8 data_020ca57c[];

void func_02047c98(int param0, int param1, int param2, int param3)
{
    Pair arr[256];
    Pair *p;
    int r5, r6;
    int count;
    int out0, out1;
    int local_y;
    int zero1;
    int zero2;

    p = arr;
    do {
        p->x = 0;
        p->y = 0;
        p++;
    } while (p != arr + 256);
    count = 0;

    for (r6 = 0; r6 < 16; r6++) {
        for (r5 = 0; r5 < 16; r5++) {
            Entry *e = func_0204f5e0(param1, param2 + 1, param3 + 1, r5, r6, 0);
            if (e != 0) {
                int valid = 0;
                u16 f = e->unk_00;
                if (f >= 0x26 && f <= 0x2a) {
                    valid = 1;
                }
                if (valid != 0 || (f >= 0x66 && f <= 0x68)) {
                    if (func_0204b910(e) != 0) {
                        func_0204f800(&out0, &out1, param2 + 1, param3 + 1, r5, r6);
                        arr[count].x = out0;
                        arr[count].y = out1;
                        count++;
                    }
                }
            }
        }
    }

    if (count > 0) {
        int idx = func_020644cc(count);
        Pair *base = &arr[idx];
        const u8 *table = data_020ca57c;
        int i;
        zero1 = 0;
        zero2 = 0;

        for (i = 0; i < 3; i++) {
            u8 b = *table;
            int x = base->x + ((b >> 4) - 8);
            int y = base->y + ((b & 0xf) - 8);
            int tile_x = x >> 4;
            int tile_y = y >> 4;
            int sub_y = y - (tile_y << 4);
            int sub_x = x - (tile_x << 4);
            Entry *e;
            local_y = y;
            e = func_0204f5e0(param1, tile_x, tile_y, sub_x, sub_y, zero2);
            if (e != 0 && e->unk_00 == 0xfff1) {
                int z = func_02047db8(param0);
                func_0204a25c(param1, x, local_y, z, zero1);
            }
            table++;
        }
    }
}
