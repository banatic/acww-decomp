/* func_020723a8 @ 0x020723a8, 0x184 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020723a8 {
    int w[0xb1];
} UnkStruct_020723a8;
typedef struct UnkStruct_020723a8_3 {
    int x;
} UnkStruct_020723a8_3;
typedef struct UnkStruct_020723a8_2 {
    char unk_00[0x14];
    UnkStruct_020723a8_3 unk_14;
    char pmid[0x10ad0 - 0x18];
    UnkStruct_020723a8_3 unk_10AD0;
} UnkStruct_020723a8_2;

extern UnkStruct_020723a8 *func_020e98b4(int);
extern void func_020e9898(UnkStruct_020723a8 *);
extern void func_0203d228(UnkStruct_020723a8 *);
extern int func_0203d064(UnkStruct_020723a8 *, u16 *, int);
extern int func_02098844(UnkStruct_020723a8_3 *, int);
extern void *func_020996b8(void *);
extern void *func_02072bd0(void *, int);
extern u8 *func_0203cfe4(UnkStruct_020723a8 *);
extern u8 *func_02072da0(void *);
extern u8 *func_0203cfd0(UnkStruct_020723a8 *);
extern void *func_02072d4c(void *);
extern u16 *func_02072f88(void *);
extern void *func_0203cfc8(UnkStruct_020723a8 *);
extern int func_02056064(void *, int);
extern void *func_02056160(void *, int);
extern int func_020b65c4(void);
extern void *func_02072a48(UnkStruct_020723a8_3 *, int);
extern int func_0203cff8(UnkStruct_020723a8 *, void *);

extern UnkStruct_020723a8_2 data_021dc7a8;
extern void *data_021d054c[4][8];
extern void *data_021d04e4[8];

void func_020723a8(void *object)
{
    u8 i;
    void *p;
    void **tbl;
    UnkStruct_020723a8 *a;
    UnkStruct_020723a8 *b;
    u8 *d;
    u8 *s;
    u16 *d2;
    u16 *s2;
    u16 h;
    u8 k;
    u8 m;
    unsigned int n;

    a = func_020e98b4(0x2c4);
    b = func_020e98b4(0x2c4);
    if (a == 0) {
        return;
    }
    if (b == 0) {
        return;
    }
    if (a != 0) {
        func_0203d228(a);
    }
    if (b != 0) {
        func_0203d228(b);
    }
    h = 0x11a8;
    func_0203d064(a, &h, 0);
    for (i = 0; i < 4; i++) {
        for (k = 0; k < 8; k++) {
            tbl = data_021d054c[i];
            p = func_02072bd0(
                func_020996b8((void *) func_02098844((UnkStruct_020723a8_3 *) ((char *) &data_021dc7a8 + 0x14), i)), k);
            *b = *a;
            d = func_0203cfe4(b);
            s = func_02072da0(p);
            for (n = 0; n < 0x200; n++) {
                *d++ = *s++;
            }
            d2 = (u16 *) func_0203cfd0(b);
            s2 = func_02072f88(func_02072d4c(p));
            for (n = 0; n < 0x10; n++) {
                *d2++ = *s2++;
            }
            if (func_02056064(func_0203cfc8(b), 0) != 0) {
                tbl[k] = func_02056160(func_0203cfc8(b), 0x4e554c4c);
            }
        }
    }
    if (func_020b65c4() == 0xa) {
        for (m = 0; m < 8; m++) {
            func_0203cff8(b, func_02072a48((UnkStruct_020723a8_3 *) ((char *) &data_021dc7a8 + 0x10ad0), m));
            if (func_02056064(func_0203cfc8(b), 0) != 0) {
                data_021d04e4[m] = func_02056160(func_0203cfc8(b), 0x4e554c4c);
            }
        }
    }
    func_020e9898(a);
    func_020e9898(b);
}
