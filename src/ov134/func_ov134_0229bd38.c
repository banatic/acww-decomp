/* func_ov134_0229bd38 @ 0x0229bd38, 0x176 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220a580(void *);
extern void func_ov134_022995b0(void *, int);
extern void func_0209e474(void *);
extern void func_0209e29c(void *, int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_0209e268(void *, int);
extern void func_ov134_0229af60(void *);

void func_ov134_0229bd38(void *arg0, int p1, int p2, int p3, u8 p4)
{
    char *r4 = (char *) arg0;

    *(u16 *) (r4 + 0x90) = 0;
    *(u8 *) (r4 + 0xb7) = 0;
    *(u8 *) (r4 + 0xa0) = (u8) p1;
    *(u8 *) (r4 + 0x98) = 0;

    switch (*(u8 *) (r4 + 0xa0)) {
        case 0:
        case 1:
            *(u8 *) (r4 + 0xa1) = 0;
            break;
        case 2:
            *(u8 *) (r4 + 0xa1) = 1;
            break;
        case 3:
            *(u8 *) (r4 + 0xa1) = 2;
            break;
    }

    *(u8 *) (r4 + 0xa2) = (u8) p2;
    *(u8 *) (r4 + 0xa3) = (u8) p3;
    *(u8 *) (r4 + 0xa4) = p4;

    *(int *) (r4 + 0x70) = 0;
    *(int *) (r4 + 0x74) = 0;
    *(int *) (r4 + 0x78) = 0;

    func_ov002_0220a580(r4 + 0x18);

    *(int *) (r4 + 4) = 0;

    switch (*(u8 *) (r4 + 0xa0)) {
        case 0:
        case 3:
            *(u8 *) (r4 + 0xb1) = 0;
            break;
        case 1:
            *(u8 *) (r4 + 0xb1) = 3;
            func_ov134_022995b0(r4, 0x40);
            func_ov134_022995b0(r4, 0x80);
            break;
        case 2:
            *(u8 *) (r4 + 0xb1) = 1;
            break;
    }

    if (*(u8 *) (r4 + 0xa0) == 2) {
        *(int *) (r4 + 0xb8) = 0;
        *(int *) (r4 + 0xbc) = 0;
        *(u8 *) (r4 + 0xbd) = 1;
        *(u8 *) (r4 + 0xbc) = 1;
        *(u8 *) (r4 + 0xbb) = 1;
    } else {
        func_0209e474(r4 + 0xb8);
        *(u8 *) (r4 + 0xb8) = 0;

        if (*(u8 *) (r4 + 0xa0) == 3) {
            func_0209e29c(r4 + 0xb8, 1);
        }

        MI_CpuCopy8(r4 + 0xb8, r4 + 0xc8, 8);
        MI_CpuCopy8(r4 + 0xb8, r4 + 0xd0, 8);
        func_0209e268(r4 + 0xd0, 0xc);

        *(u8 *) (r4 + 0xb2) = *(u8 *) (r4 + 0xca);
        *(u8 *) (r4 + 0xb3) = *(u8 *) (r4 + 0xd2);
        *(u8 *) (r4 + 0xb4) = *(u8 *) (r4 + 0xc9);

        func_ov134_0229af60(r4);
    }
}
