/* func_02049160 @ 0x02049160, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pair;
typedef struct {
    int unk_00;
    int h1;
    Pair items[64];
    char tail[0x80];
} Row;
typedef struct {
    char b[0x24];
} UnkStruct_02049160;

extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_020492c8(Row *arr, UnkStruct_02049160 *e);
extern int func_0204ba94(u16 *p);
extern void func_0204927c(Row *arr, int tile, int cx, int cz, int dx, int dz);
extern void func_02049240(Row *arr);
extern UnkStruct_02049160 data_021c7a08[][4];

void func_02049160(int p0, void *ctx, int nj, int ni)
{
    Row arr[4];
    Row *p;
    Pair *q;
    int j, i, k;
    u16 *e;

    p = arr;
    do {
        q = p->items;
        do {
            q->x = 0;
            q->y = 0;
            q++;
        } while (q != p->items + 64);
        p++;
    } while (p != arr + 4);
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            e = func_0204f5e0(ctx, j + 1, i + 1, 0, 0, 0);
            func_020492c8(arr, &data_021c7a08[j][i]);
            for (k = 0; k < 256; k++) {
                if (e != 0) {
                    if (func_0204ba94(e) != 0) {
                        func_0204927c(arr, *e, j + 1, i + 1, k & 0xf, (k >> 4) & 0xf);
                    }
                }
                e++;
            }
            func_02049240(arr);
        }
    }
}
