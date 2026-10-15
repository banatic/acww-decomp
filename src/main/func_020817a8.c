/* func_020817a8 @ 0x020817a8, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02081f18(void *);
extern void *func_02081f30(void *);
extern char *func_02072dbc(void *);
extern void func_02066694(void *);
extern void *func_0209b634(void *);
extern void func_02034ce0(void *);
extern void func_020051b0(void *);
extern int func_02003780(void *);
extern void func_020642fc(void *);
extern int func_02081fa0(void *);

struct UnkStruct_020817a8 {
    u8 pad_00[0x400];
    u8 pad_400[0x634 - 0x400];
    u8 pad_634[0x734 - 0x634];
    u8 pad_734[0x78c - 0x734];
    u8 pad_78C[0x7a0 - 0x78c];
    u8 pad_7A0[0x7b0 - 0x7a0];
    u8 pad_7B0[0x7b8 - 0x7b0];
    u8 pad_7B8[0x7ce - 0x7b8];
    u16 unk_7CE;                   // offset 0x7ce
    u8 pad_extra[0x7d2 - 0x7d0];   // offset 0x7d0, size 2
    u16 unk_7D2;                   // offset 0x7d2
    u8 pad_7D4[0x7dc - 0x7d2 - 2]; // remaining to 0x7dc
};

void *func_020817a8(struct UnkStruct_020817a8 *p)
{
    __cxa_vec_ctor((void *) (p), 8, 0x80, (((void (*)(void *)) func_02081f30)), (((void (*)(void *)) func_02081f18)));
    func_02072dbc((char *) p + 0x400);
    func_02066694((char *) p + 0x634);
    func_0209b634((char *) p + 0x734);
    __cxa_vec_ctor((void *) ((char *) p + 0x78c), 10, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_02003780((char *) p + 0x7a0);
    __cxa_vec_ctor((void *) ((char *) p + 0x7b0), 4, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_020642fc((char *) p + 0x7b8);
    func_02081fa0(&p->unk_7CE);
    p->unk_7D2 = 0xfff1;
    func_020642fc((char *) p + 0x7dc);
    return p;
}
