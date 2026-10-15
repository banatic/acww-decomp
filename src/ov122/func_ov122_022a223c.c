/* func_ov122_022a223c @ 0x022a223c, 0x238 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_ov122_022a2700; // pool 0x022a2700
extern int data_ov122_022a25b0; // pool 0x022a25b0

extern void func_ov002_0220919c(void *);
extern int func_ov122_0229efe8(void *, int);
extern void func_02088df8(int, void *, int, void *, int, int, int, int, int, int, int, int);
extern void func_ov095_0229b1c8(void *, int, void *, int);
extern void func_ov095_0229ae84(void *, int, void *);
extern int func_0206fe54(void);
extern int func_020896b8(int, void *, int, void *, int, int, int);

extern int func_ov122_0229f444(void *);
extern void func_ov122_0229f3c8(void *);
extern void func_0200284c(int, int, int);
extern void func_ov122_0229efd8(void *, int);
extern void func_ov122_0229efc8(void *, int);
extern void func_02001b7c(int);
extern void func_02001b6c(int);
extern void func_02001d74(int, int);
extern void func_02001d00(int);
extern void func_02002808(int, int, int, int, int);

extern void func_0208ea70(void *, int, int);
extern void *func_ov002_0220a4f8(void *);
extern void *func_ov002_0220a4d4(void *);
extern void func_ov095_02299b30(void *, void *, void *);

extern void func_ov002_0220a0b4(void *, void *, void *);
extern void func_ov002_02209eb8(void *);

extern void func_ov002_0220ad18(void *, int);

extern int func_ov095_0229af58(void *, int, int, int);

int func_ov122_022a223c(u8 *self)
{
    void *r5;
    void *r2;

    func_ov002_0220919c(self + 0x42b0);

    if (func_ov122_0229efe8(self, 1) != 0) {
        r5 = (u8 *) (*(int *) (self + 0x94)) + 0x60;

        func_02088df8(1, &data_ov122_022a2700, 0x80, (u8 *) r5 - 0x10, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        func_ov095_0229b1c8(self + 0xc0, 0x80, r5, 1);
        func_ov095_0229ae84(self + 0xc0, 0x80, r5);

        if (func_0206fe54() != 0) {
            func_020896b8(1, &data_ov122_022a25b0, 0x80, r5, -1, 1, 0);
        }
    }

    if (func_ov122_0229f444(self) != 0) {
        func_ov122_0229f3c8(self);
        func_0200284c(4, 0, *(u8 *) (self + 0xb2));
        func_0200284c(3, 0, *(u8 *) (self + 0xb2));
        if (*(u8 *) (self + 0xb2) > 0x40) {
            if (func_ov122_0229efe8(self, 0x20) == 0) {
                func_ov122_0229efd8(self, 0x20);
                func_02001b7c(1);
                func_02001d74(0x1d, 1);
                func_02001d00(0x1f);
                func_02002808(2, 0, 0xb0, 0xfe, 0xc0);
            }
        } else {
            if (func_ov122_0229efe8(self, 0x20) != 0) {
                func_ov122_0229efc8(self, 0x20);
                func_02001b6c(1);
            }
        }
    }

    if (func_ov122_0229efe8(self, 1) != 0) {
        func_0208ea70(self + 0x4010, 100, (*(int *) (self + 0x94) - 0x58) + (*(u8 *) (self + 0xb2) >> 1));
        r5 = func_ov002_0220a4f8(self + 0x4010);
        r2 = func_ov002_0220a4d4(self + 0x4010);
        func_ov095_02299b30(self + 0xc0, r5, r2);
        (*(void (**)(void *))((u8 *) (*(void **) (self + 0x4010)) + 8))(self + 0x4010);
    }

    if (func_0206fe54() != 0) {
        if (func_ov122_0229efe8(self, 0x200) != 0) {
            r5 = func_ov002_0220a4f8(self + 0x4010);
            r2 = func_ov002_0220a4d4(self + 0x4010);
            func_ov002_0220a0b4(self + 0x4058, r5, r2);
        }
        func_ov002_02209eb8(self + 0x4058);
    }

    if (func_ov122_0229efe8(self, 1) != 0) {
        func_ov002_0220ad18(self + 0x4698, *(int *) (self + 0x94));
    }
    if (func_ov122_0229efe8(self, 2) != 0) {
        func_ov002_0220ad18(self + 0x4698, *(int *) (self + 0x98));
    }
    if (func_ov122_0229efe8(self, 4) != 0) {
        int t1 = *(int *) (self + 0x9c);
        int t2 = *(int *) (self + 0xa0) - *(u8 *) (self + 0xb2);
        *(u8 *) (self + 0xab) = (u8) (*(u8 *) (self + 0xab) + 1);
        if ((*(u8 *) (self + 0xab) & 0x10) != 0) {
            func_ov095_0229af58(self + 0xc0, t1, t2, 3);
        }
    }

    return 1;
}
