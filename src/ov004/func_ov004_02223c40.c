/* func_ov004_02223c40 @ 0x02223c40, 0x18c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern void *data_ov004_02254594;
extern int func_ov004_0222dc00(void), func_ov004_0222dc3c(void), func_ov004_0222be58(void), func_ov004_0222dbac(void),
    func_020950c0(void *), func_020644cc(int), func_0202ea80(int, int), func_02088bd4(void *);
extern void *func_020984e8(void), *func_02099870(void *), *func_02099670(void *);
extern void func_0200442c(void *, int, int, int), func_02035684(int, int, int), func_02035624(int),
    func_020356c4(int, int, int, int), func_0206844c(void *, u8 *, void *), func_02088bc4(void *, int),
    func_ov004_0222421c(void *, int);
void func_ov004_02223c40(u8 *self)
{
    u8 message;
    u8 *dialogue = P(self, 0x40);
    if (W(dialogue, 4) == 5) {
        if (func_ov004_0222dc00() == 5) {
            func_ov004_0222dc3c();
            func_ov004_0222be58();
            H(P(self, 0xb4), 0x77c) = 0;
        }
        H(P(self, 0xb4), 0x77c)++;
        if (H(P(self, 0xb4), 0x77c) == 7) {
            func_0200442c(P(self, 0xb4) + 0x514, 0x4e1, 127, 0);
        }
        if (H(P(self, 0xb4), 0x77c) == 20) {
            func_0200442c(P(self, 0xb4) + 0x514, 0x4e2, 127, 0);
            func_02035684(16, 20, 0);
        }
        if (H(P(self, 0xb4), 0x77c) == 40) {
            func_0200442c(P(self, 0xb4) + 0x514, 0x4e3, 127, 0);
        }
        if (H(P(self, 0xb4), 0x77c) == 70) {
            if (func_020950c0(func_02099870(func_020984e8())) == 0) {
                func_0200442c(P(self, 0xb4) + 0x514, 0x4e4, 127, 0);
            } else {
                func_0200442c(P(self, 0xb4) + 0x514, 0x4e5, 127, 0);
            }
        }
        if (func_ov004_0222dbac()) {
            u8 response;
            void *state;
            if (self[0xb9]) {
                response = 0x30;
            } else {
                response = func_020644cc(11) + 0x31;
            }
            func_02035624(16);
            func_02035684(12, 0, 10);
            func_020356c4(13, 62, 127, 1);
            message = response;
            func_0206844c(dialogue, &message, data_ov004_02254594);
            W(dialogue, 8) = 1;
            func_0202ea80(23, 1);
            state = func_02099670(func_020984e8());
            if (func_020644cc(10) < 5) {
                func_02088bc4(state, func_02088bd4(state) + 1);
            }
            func_ov004_0222421c(self, 0);
        }
    }
}
