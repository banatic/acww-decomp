/* func_0203a508 @ 0x0203a508, 0xec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_0203a508;

// {1, 0, 2}, the template of the local kind table
typedef struct {
    int v[3];
} KindTable;
extern const KindTable data_020da6f8;

extern int func_020644cc(int);
extern void func_02063ccc(UnkStruct_0203a508 *o, int a, int b);
extern void func_020638d4(u16 *out, UnkStruct_0203a508 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_0203a508 *o);

void func_0203a508(u16 *arr, int n)
{
    int k;
    int starti;
    int zkind;
    int z1;
    int z2;
    int count;
    int i;
    int j;
    int r;
    int kind;
    u16 h[2];
    UnkStruct_0203a508 o;
    KindTable tbl = data_020da6f8;

    count = 0;
    for (j = 0; j < 0xf; j++) {
        if (arr[j] != 0xfff1) {
            count++;
        }
    }
    k = 0;
    zkind = 0;
    starti = 0;
    z1 = 0;
    z2 = 0;
    while (k < n) {
        if (count >= 10) {
            return;
        }
        for (i = starti; i < 0xf; i++) {
            if (arr[i] != 0xfff1) {
                continue;
            }
            r = func_020644cc(100);
            kind = 0xff;
            if (r >= 50 && r < 100) {
            } else if (r >= 30 && r < 50) {
                arr[i] = 0x1566;
                count++;
            } else if (r >= 20 && r < 30) {
                kind = zkind;
            } else if (r >= 10 && r < 20) {
                kind = 1;
            } else if (r >= 0 && r < 10) {
                kind = 2;
            }
            if (kind == 0xff) {
                break;
            }
            func_02063ccc(&o, tbl.v[kind], z1);
            func_020638d4(&h[0], &o, z2, z2, 1, 1, z2);
            func_02063cc8(&o);
            arr[i] = h[0];
            count++;
            break;
        }
        k++;
    }
}
