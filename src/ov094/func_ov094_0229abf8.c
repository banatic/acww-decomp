/* func_ov094_0229abf8 @ 0x0229abf8, 0xb8 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02070c08(void *);
extern void func_0208aecc(void *);
extern void func_02062fbc(void *);
extern void func_02094fd4(void *);
extern void func_0207094c(void *, int);
extern void func_02051a78(void *, void *);
extern void func_02062ea4(void *, void *);
extern void func_02099e7c(void *, void *);
extern void func_020b496c(int, void *);
extern int func_ov094_02299a70(int);
extern void func_0208aa48(void *, void *);
extern void func_02094fbc(void *);
extern void func_02062f4c(void *);
extern void func_0208aeb8(void *);
extern void func_02070be8(void *);

void func_ov094_0229abf8(int a0, void *arg1, u16 *arg2, int mode)
{
    struct {
        u8 unk0[0x30];
        u8 unk30[0x28];
        u8 unk58[0x20];
        u8 unk78[0x70];
    } buf;

    func_02070c08(buf.unk78);
    func_0208aecc(buf.unk0);
    func_02062fbc(buf.unk30);
    func_02094fd4(buf.unk58);

    switch (mode) {
        case 1:
            func_0207094c(buf.unk78, 0x18);
            func_02051a78(buf.unk0, buf.unk78);
            break;
        case 2:
            if (func_ov094_02299a70(*arg2) != 0) {
                func_02062ea4(buf.unk30, arg2);
                func_02051a78(buf.unk0, buf.unk30);
            } else {
                func_02099e7c(buf.unk58, arg2);
                func_020b496c(0, buf.unk58);
                func_0207094c(buf.unk78, 0x40);
                func_02051a78(buf.unk0, buf.unk78);
            }
            break;
        case 0:
        default:
            func_02062ea4(buf.unk30, arg2);
            func_02051a78(buf.unk0, buf.unk30);
            break;
    }

    func_0208aa48(arg1, buf.unk0);
    func_02094fbc(buf.unk58);
    func_02062f4c(buf.unk30);
    func_0208aeb8(buf.unk0);
    func_02070be8(buf.unk78);
}
