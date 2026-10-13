/* func_ov002_02208b74 @ 0x02208b74, 0xe4 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02208b74 UnkStruct_02208b74;
typedef void (*VF)(void *);
typedef struct {
    u8 b[0x6c];
} UnkStruct_02208b74_2;
typedef struct {
    u8 b[0x70];
} UnkStruct_02208b74_3;

extern void func_ov002_02208f58(UnkStruct_02208b74 *, u8 *, int, u8 *);
extern void func_ov002_022092e0(UnkStruct_02208b74 *);
extern void func_02070c08(void *);
extern void func_020708e4(void *, short *, int);
extern void func_020a8bb8(void *, void *);
extern void func_020a89f8(void *, void *);
extern void func_020a89dc(void *, void *);
extern void func_0208f218(u8 *, void *);
extern void func_02070be8(void *);
extern u8 data_ov002_0220ba50[];

void func_ov002_02208b74(UnkStruct_02208b74 *self, u8 *p)
{
    int val;
    short v[4];
    UnkStruct_02208b74_2 a;
    UnkStruct_02208b74_3 b;
    int i;
    int k;
    int t;
    void *obj;

    k = p[0] * 5;
    i = 0;
    *((u8 *) self + 0x1c) = 0;
    for (; i < 5; i++, k++) {
        val = *((u8 *) self + k + 0x3cc);
        if (val != 0) {
            t = i;
            t = t * 0x74;
            func_ov002_02208f58(self, (u8 *) self + 0x28 + t, val, (u8 *) self + 0x28);
            *((u8 *) self + 0x1c) = (u8) (*((u8 *) self + 0x1c) + 1);
        } else {
            i = 5;
        }
    }
    func_ov002_022092e0(self);
    v[0] = (short) (p[0] + 0xff11);
    v[1] = 0;
    v[2] = (short) (*((u8 *) self + 0x1d) + 0xff10);
    v[3] = 0;
    func_02070c08(&a);
    func_02070c08(&b);
    func_020708e4(&b, &v[0], 2);
    func_020a8bb8(&a, &b);
    func_020a89f8(&a, data_ov002_0220ba50);
    func_020708e4(&b, &v[2], 2);
    func_020a89dc(&a, &b);
    func_0208f218((u8 *) self + 0x26c, &a);
    obj = (u8 *) self + 0x26c;
    (*(VF *) ((u8 *) *(void **) obj + 0xc))(obj);
    *((u8 *) self + 0x20) = p[0];
    func_02070be8(&b);
    func_02070be8(&a);
}
