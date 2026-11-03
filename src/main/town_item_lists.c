/* town_item_lists: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203a670 @ 0x0203a670, 0x2 bytes, Thumb
 * func_0203a66c @ 0x0203a66c, 0x2 bytes, Thumb
 * func_0203a658 @ 0x0203a658, 0x14 bytes, Thumb
 * func_0203a5f4 @ 0x0203a5f4, 0x64 bytes, Thumb
 * func_0203a508 @ 0x0203a508, 0xec bytes, Thumb
 * func_0203a504 @ 0x0203a504, 0x2 bytes, Thumb
 * func_0203a500 @ 0x0203a500, 0x2 bytes, Thumb
 * func_0203a4ec @ 0x0203a4ec, 0x14 bytes, Thumb
 * func_0203a46c @ 0x0203a46c, 0x80 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_0203a5f4;

typedef struct {
    int a;
    int b;
} UnkStruct_0203a508;

// {1, 0, 2}, the template of the local kind table
typedef struct {
    int v[3];
} KindTable;

extern int func_020644cc(int);
extern void func_02063ccc(UnkStruct_0203a5f4 *o, int a, int b);
extern void func_020638d4(u16 *out, UnkStruct_0203a5f4 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_0203a5f4 *o);
extern const KindTable data_020da6f8;
extern void func_0209e100(void *ptr, int a);
extern unsigned int func_0209de88(int a, int b, int c);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_0203a670(void *self) {}

void func_0203a66c(void *self) {}

void func_0203a658(unsigned short *arr)
{
    int i;
    for (i = 0; i < 15; i++) {
        arr[i] = 0xfff1;
    }
}

void func_0203a5f4(u16 *dst)
{
    int i;
    for (i = 0; i < 3; i++) {
        int ids[3] = {1, 0, 2};
        u16 h[2];
        UnkStruct_0203a5f4 o;
        func_02063ccc(&o, ids[func_020644cc(3)], 0);
        func_020638d4(&h[0], &o, 0, 0, 1, 1, 0);
        func_02063cc8(&o);
        dst[i] = h[0];
    }
}

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
            func_02063ccc((UnkStruct_0203a5f4 *) (&o), tbl.v[kind], z1);
            func_020638d4(&h[0], (UnkStruct_0203a5f4 *) (&o), z2, z2, 1, 1, z2);
            func_02063cc8((UnkStruct_0203a5f4 *) (&o));
            arr[i] = h[0];
            count++;
            break;
        }
        k++;
    }
}

void func_0203a504(void *self) {}

void func_0203a500(void *self) {}

void func_0203a4ec(unsigned short *arr)
{
    int i;
    for (i = 0; i < 15; i++) {
        arr[i] = 0xFFF1;
    }
}

void func_0203a46c(int arg0, const void *arg1, int arg2)
{
    if (arg2 == 0) {
        return;
    }
    if (arg2 >= 4) {
        func_0203a4ec((unsigned short *) arg0);
        return;
    }
    {
        union {
            unsigned long long value;
            unsigned char bytes[8];
        } temp;
        temp.value = 0;
        MI_CpuCopy8(arg1, &temp, 8);
        func_0209e100(&temp, 6);
        {
            unsigned int result = func_0209de88(temp.bytes[5], temp.bytes[4], temp.bytes[3]);
            switch (result) {
                case 0:
                    break;
                case 1:
                case 4:
                    func_0203a4ec((unsigned short *) arg0);
                    break;
                case 2:
                case 5:
                    if (arg2 >= 2) {
                        func_0203a4ec((unsigned short *) arg0);
                    }
                    break;
                case 3:
                case 6:
                    if (arg2 >= 3) {
                        func_0203a4ec((unsigned short *) arg0);
                    }
                    break;
            }
        }
    }
}
