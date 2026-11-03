/* error_message_2: 4 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b804 @ 0x0220b804, 0x2c bytes, Thumb
 * func_ov002_0220b7ec @ 0x0220b7ec, 0x18 bytes, Thumb
 * func_ov002_0220b7b8 @ 0x0220b7b8, 0x34 bytes, Thumb
 * func_ov002_0220b764 @ 0x0220b764, 0x54 bytes, Thumb
 */

#include "types.h"

extern int func_ov002_0220b71c(void *self);
extern void func_ov002_0220b6f4(void);
extern int func_ov002_0220b6d0(u8 *self);
extern void func_ov002_0220b6b0(void *self);
extern int func_0207094c(void *, int);
extern int func_02070be8(void *);
extern void *func_02070c08(void *);
extern void func_0208aa48(void *, void *);
extern void func_0208aa60(void *, int, int);
extern void func_0208aa98(void *);
extern void func_ov002_02207cec(void *, int);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207d00(void *);
extern void func_ov002_0220b6b8(void *receiver);

int func_ov002_0220b804(u8 *self)
{
    if (self[0x118] == 0) {
        if (func_ov002_0220b71c(self)) {
            self[0x118] = 1;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

int func_ov002_0220b7ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b6f4();
    *(u8 *) (self + 0x118) = 0x2;
    return 0x118;
}

int func_ov002_0220b7b8(u8 *self)
{
    if (self[0x118] == 2) {
        if (func_ov002_0220b6d0(self)) {
            func_ov002_0220b6b0(self);
            self[0x118] = 3;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

int func_ov002_0220b764(char *self)
{
    // DECLS
    char frame[0x70];
    // ENDDECLS
    func_02070c08(frame);
    func_0207094c(frame, 0x64);
    func_0208aa48(self, frame);
    func_0208aa60(self, 0x0, 0x40);
    func_ov002_02207cf8(self);
    func_0208aa98(self);
    func_ov002_02207cec(self, 0x0);
    func_ov002_0220b6b8(self);
    func_ov002_02207d00(self);
    return func_02070be8(frame);
}
