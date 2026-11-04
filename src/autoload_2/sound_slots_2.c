/* sound_slots_2: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ef498 @ 0x020ef498, 0x2bc bytes, ARM
 * func_020ef3ac @ 0x020ef3ac, 0xec bytes, ARM
 * func_020ef2a4 @ 0x020ef2a4, 0x108 bytes, ARM
 */

#include "types.h"

typedef struct {
    void *unk_00;
    u8 pad_04[2];
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[2];
} Elem;

typedef struct UnkStruct_020ef498 {
    u8 pad_00[8];
    Elem arr[3];
    void (*fn2c)(struct UnkStruct_020ef498 *, int, int);
    void (*fn30)(struct UnkStruct_020ef498 *, int, int);
    u16 flags;
    u8 count;
} UnkStruct_020ef498;

typedef struct {
    UnkStruct_020ef498 *self;
    void *arg1;
    int pad_08[3];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_020ef498_2;

struct UnkStruct_020ef3ac {
    int pad_00[3];
};

typedef struct {
    unsigned char pad_00[8];
    struct UnkStruct_020ef3ac arr[3];
    unsigned char pad_2C[8];
    unsigned short flags;
    unsigned char count;
} UnkStruct_020ef3ac_2;

typedef struct {
    char pad_00[0x34];
    unsigned short flag;
    unsigned char count;
} Header;

typedef struct {
    char data[12];
} UnkStruct_020ef2a4;

extern u16 data_0213e858;
extern void OS_Terminate(void);
extern void func_020ef144(UnkStruct_020ef498 *, int);
extern void func_020ef874(UnkStruct_020ef498 *, int, int);
extern int func_020ef8bc(Elem *);
extern void func_020ef1f8(UnkStruct_020ef498 *, int, int);
extern void func_020ef8d0(Elem *, int, int);
extern void func_020efa6c(UnkStruct_020ef498_2 *);
extern u8 *NNS_SndArcGetSeqArcParam(int, int);
extern void NNS_SndPlayerSetVolume(Elem *, int);
extern void func_0210b734(Elem *, int);
extern void func_0210b634(Elem *, int, int);
extern int func_020ef968(struct UnkStruct_020ef3ac *p, int a, int b);
extern int func_020ef7fc(UnkStruct_020ef3ac_2 *s);
extern void func_020ef9dc(struct UnkStruct_020ef3ac *p, int a, int b, int c, short d);
extern void func_020efa30(void *ptr, int p4, int p5);
extern void func_020ef998(void *ptr, int p2, int p3, int p4, int p5);

void func_020ef498(UnkStruct_020ef498 *self, void *arg1)
{
    UnkStruct_020ef498_2 ctx;
    int st;
    int code;
    int i;
    int started;
    Elem *e;

    started = 0;
    if (self->count == 0) {
        OS_Terminate();
    }
    if ((self->flags & 1) == 0) {
        if ((self->flags & 2) == 0) {
            return;
        }
        func_020ef144(self, 0);
        func_020ef874(self, 1, 0);
        return;
    }
    i = 0;
    ctx.self = self;
    ctx.arg1 = arg1;
    ctx.unk_20 = 0;
    ctx.unk_14 = 0;
    ctx.unk_1C = 0;
    ctx.unk_18 = 0;
    if ((int) self->count > 0) {
        e = &self->arr[0];
        do {
            code = -1;
            st = 0;
            if (func_020ef8bc(e) != 0) {
                if ((e->unk_09 & 8) == 0) {
                    func_020ef1f8(self, i, 0);
                    goto next;
                }
                func_020ef8d0(e, 3, 0);
                st = 2;
            }
            if (e->unk_09 & 2) {
                if (started == 0) {
                    func_020efa6c(&ctx);
                    started = 1;
                }
                if (ctx.unk_14 > 0) {
                    u8 *p;
                    int base;
                    base = ctx.unk_1C;
                    p = NNS_SndArcGetSeqArcParam(e->unk_08, e->unk_06);
                    if (p == 0) {
                        OS_Terminate();
                    }
                    code = base + (p[4] - 0x40);
                    code = code > 0 ? (code >= 0x7f ? 0x7f : code) : 0;
                    self->fn2c(self, i, code);
                    st = 1;
                }
                func_020ef8d0(e, 1, 0);
            }
            if (st == 0) {
                st = (e->unk_09 & 1) ? 2 : 0;
            }
            if (st != 0 && e->unk_00 != 0) {
                if (started == 0) {
                    func_020efa6c(&ctx);
                    started = 1;
                }
                if (code == -1) {
                    u8 *p;
                    int base;
                    base = ctx.unk_1C;
                    p = NNS_SndArcGetSeqArcParam(e->unk_08, e->unk_06);
                    if (p == 0) {
                        OS_Terminate();
                    }
                    code = base + (p[4] - 0x40);
                    code = code > 0 ? (code >= 0x7f ? 0x7f : code) : 0;
                }
                if (started == 0) {
                    OS_Terminate();
                }
                NNS_SndPlayerSetVolume(e, ctx.unk_14);
                func_0210b734(e, code);
                func_0210b634(e, data_0213e858, ctx.unk_18);
                self->fn30(self, i, code);
            }
        next:
            e = e + 1;
            i = i + 1;
        } while (i < (int) self->count);
    }
    func_020ef874(self, 1, 1);
}

int func_020ef3ac(UnkStruct_020ef3ac_2 *self, int arg1, int arg2, int arg3, short arg5)
{
    int found = 0xff;
    int i;

    if ((self->flags & 1) == 0) {
        return -1;
    }

    for (i = 0; i < self->count; i++) {
        if (func_020ef968(&self->arr[i], arg1, arg2) != 0) {
            found = i;
            func_020ef1f8((UnkStruct_020ef498 *) self, i, 0);
            break;
        }
    }

    if (found == 0xff) {
        found = func_020ef7fc(self);
    }

    if (found == self->count) {
        return -1;
    }

    func_020ef9dc(&self->arr[found], arg1, arg2, arg3, arg5);
    return found;
}

int func_020ef2a4(Header *p1, int p2, int p3, int p4, short p5)
{
    int i;
    if ((p1->flag & 1) == 0) {
        return -1;
    }
    i = 0;
    if ((int) p1->count > 0) {
        UnkStruct_020ef2a4 *ptr = (UnkStruct_020ef2a4 *) ((char *) p1 + 8);
        do {
            if (func_020ef8bc((Elem *) ptr) != 0 && func_020ef968((struct UnkStruct_020ef3ac *) ptr, p2, p3) != 0) {
                func_020ef8d0((Elem *) ptr, 3, 1);
                func_020efa30(ptr, p4, p5);
                return i;
            }
            i++;
            ptr++;
        } while (i < p1->count);
    }
    i = func_020ef7fc((UnkStruct_020ef3ac_2 *) p1);
    if (i == p1->count) {
        return -1;
    }
    func_020ef998((UnkStruct_020ef2a4 *) ((char *) p1 + 8) + i, p2, p3, p4, p5);
    return i;
}
