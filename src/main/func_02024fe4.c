/* func_02024fe4 @ 0x02024fe4, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02024fe4_2 {
    unsigned char pad_00[0x164];
    void *unk_164;
};
struct UnkStruct_02024fe4 {
    int a;
    int b;
};

extern struct UnkStruct_02024fe4 data_020d8f10;
extern struct UnkStruct_02024fe4 data_020d8e80;
extern struct UnkStruct_02024fe4 data_020d9050;

extern void *func_0202d9c4(struct UnkStruct_02024fe4_2 *);
extern int func_0209bc40(void *);
extern u32 func_0209b914(void *);
extern void *func_02029910(void *);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern void func_02015800(struct UnkStruct_02024fe4_2 *, void *, int, int);
extern int func_02015828(struct UnkStruct_02024fe4_2 *, int);
extern void func_0202dbf0(struct UnkStruct_02024fe4_2 *, struct UnkStruct_02024fe4);
extern void *func_0209bb70(void *);
extern void *func_02029a18(void *);
extern int func_02029e18(unsigned short *, int);
extern int func_02029e5c(unsigned short *, int);
extern int func_02029ea0(unsigned short *, int);

void func_02024fe4(struct UnkStruct_02024fe4_2 *o)
{
    switch (func_0209bc40(func_0202d9c4(o))) {
        case 2:
            if (func_0209b914(o->unk_164) <= 1) {
                func_020157d4(o, func_02029e18, 0xd, 1);
            } else {
                func_02015800(o, func_02029910(o->unk_164), 0xd, 1);
            }
            func_02015828(o, 0);
            func_0202dbf0(o, data_020d8f10);
            break;
        case 3:
            if (func_0209b914(o->unk_164) <= 1) {
                func_020157d4(o, func_02029e5c, 0xd, 1);
            } else {
                func_02015800(o, func_02029a18(func_0209bb70(func_0202d9c4(o))), 0xd, 1);
            }
            func_02015828(o, 0);
            func_0202dbf0(o, data_020d8e80);
            break;
        case 4:
            func_020157d4(o, func_02029ea0, 0xd, 1);
            func_02015828(o, 0);
            func_0202dbf0(o, data_020d9050);
            break;
    }
}
