/* keyboard_entry_states_2: 9 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a1228 @ 0x022a1228, 0xac bytes, Thumb
 * func_ov126_022a11d8 @ 0x022a11d8, 0x50 bytes, Thumb
 * func_ov126_022a117c @ 0x022a117c, 0x5c bytes, Thumb
 * func_ov126_022a1108 @ 0x022a1108, 0x74 bytes, Thumb
 * func_ov126_022a1038 @ 0x022a1038, 0xd0 bytes, Thumb
 * func_ov126_022a1020 @ 0x022a1020, 0x18 bytes, Thumb
 * func_ov126_022a0f40 @ 0x022a0f40, 0xe0 bytes, Thumb
 * func_ov126_022a0f20 @ 0x022a0f20, 0x1e bytes, Thumb
 * func_ov126_022a0ec4 @ 0x022a0ec4, 0x5c bytes, Thumb
 */

typedef struct {
    char pad_00[0xA8];
    unsigned char unk_A8;
} UnkStruct_022a11d8;

typedef struct {
    unsigned char pad_00[0x19c];
    int unk_19C;
} UnkStruct_022a117c;

typedef struct {
    char unk_00[0x3dc8];
} Context;

typedef struct UnkStruct_022a0f40 {
    unsigned char pad_00[0xa8];
    unsigned char unk_A8;
    unsigned char pad_A9[0x19c - 0xa8 - 1];
    unsigned char unk_19C[1];
    unsigned char pad_19D[0x3f90 - 0x19c - 1];
    unsigned char unk_3F90[1];
} UnkStruct_022a0f40;

extern int func_ov002_02208054(void *p, int x);
extern unsigned char *func_ov126_022a0c00(void *p);
extern int func_ov095_0229bf48(void *p);
extern int func_ov126_022a00a4(void *p);
extern int func_ov126_022a07e8(void *p);
extern int func_ov095_0229aff0(void *p);
extern void func_ov095_0229c22c(void *p, int a, int b, int c);
extern void func_ov126_022a0168(void *p);
extern int func_ov126_022a04e8(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern void func_ov126_022a0854(void *, unsigned char);
extern void func_ov126_022a0680(void *);
extern void func_0200467c(int);
extern int func_ov095_0229bf0c(void *p);
extern int func_ov095_0229c548(void *p);
extern int func_ov095_0229c448(void *p, int a, int b);
extern void func_ov095_0229c8e4(void *p, int a);
extern int func_ov126_022a03dc(void *p, int arg);
extern int func_ov002_0220a784(void *p, int a);
extern int func_ov002_0220a720(void *p, int a);
extern int func_ov126_022a0bb0(void *p);
extern int func_ov002_02208014(void *receiver);
extern unsigned char *func_ov126_022a0c1c(void *);
extern int func_ov002_02208008(void *);
extern int func_ov095_02299a54(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a254(void *);
extern void func_ov002_0220a314(void *);
extern void func_ov126_0229ff68(void *);
extern void func_ov126_0229f7b8(void *, int);
extern int func_ov126_0229fe28(void *);
extern int func_ov126_0229fdd4(void *);
extern int func_ov126_0229fcfc(void *);
extern int func_ov126_0229fd64(void *);
extern int func_ov126_0229fcd8(void *);
extern int func_ov126_022a0bc8(int);
extern int func_ov126_022a0768(UnkStruct_022a0f40 *self, int val);
extern void func_ov095_0229b3ec(unsigned char *ptr);
extern void func_ov126_022a0728(UnkStruct_022a0f40 *self);
extern void func_ov126_022a08c4(UnkStruct_022a0f40 *self);
extern void func_ov126_0229ff0c(UnkStruct_022a0f40 *self);
extern int func_ov002_02209f00(unsigned char *ptr);
extern void func_ov095_0229a134(unsigned char *ptr, int val);
extern void func_ov126_022a06b4(UnkStruct_022a0f40 *self);
extern struct {
    unsigned short pad;
    unsigned short flag;
} data_021fbe40;
extern void func_ov126_0229f7a8(void *p, int n);

void func_ov126_022a0f20(void *p);

void func_ov126_022a1228(void *self)
{
    int r4;
    unsigned int ok;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov126_022a0c00(self);
        return;
    }
    r4 = func_ov095_0229bf48((char *) self + 0x19c);
    ok = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (ok > 0) {
        if (func_ov126_022a00a4(self) != 0) {
            return;
        }
        if (func_ov126_022a07e8(self) != 0) {
            return;
        }
        if (func_ov095_0229aff0((char *) self + 0x19c) != 0) {
            func_ov095_0229c22c((char *) self + 0x19c, 9, 6, 1);
            func_ov126_022a0168(self);
            return;
        } else {
            int t;
            if (data_021f6c54 < 0x48) {
                return;
            }
            if (r4 != 0) {
                return;
            }
            t = func_ov126_022a04e8(self);
            if (t == 0) {
                return;
            }
            if (t != 1) {
                return;
            }
            func_ov002_02208098((void *) (self), 2);
        }
    }
}

void func_ov126_022a11d8(UnkStruct_022a11d8 *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (s), 0);
        return;
    }
    {
        unsigned char old = s->unk_A8;
        func_ov126_022a0854(s, data_021f6c58);
        if (old == s->unk_A8) {
            return;
        }
        func_ov126_022a0680(s);
        func_ov126_022a0168(s);
        func_0200467c(0x15);
    }
}

void func_ov126_022a117c(UnkStruct_022a117c *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (self), 0);
    } else {
        if (func_ov095_0229bf0c((void *) &self->unk_19C) != 0) {
            int ret;
            int tmp;
            ret = func_ov095_0229c548((void *) &self->unk_19C);
            tmp = func_ov095_0229c448((void *) &self->unk_19C, ret, 9);
            func_ov126_022a03dc(self, tmp);
            func_ov095_0229c8e4((void *) &self->unk_19C, ret);
        }
    }
}

void func_ov126_022a1108(Context *p)
{
    if (func_ov002_02208054(p, 1) != 0) {
        func_ov126_022a0bb0(p);
        return;
    }
    if (func_ov002_0220a784(&p->unk_00[0x3dc4], 3) != 0) {
        func_ov002_0220a720(&p->unk_00[0x3dc4], 3);
        p->unk_00[0x8c] = 3;
        func_ov002_02208098((void *) (p), 0xf);
        return;
    }
    if (func_ov002_0220a784(&p->unk_00[0x3dc4], 4) != 0) {
        func_ov002_0220a720(&p->unk_00[0x3dc4], 4);
        p->unk_00[0x8c] = 9;
        func_ov002_02208098((void *) (p), 0xf);
    }
}

void func_ov126_022a1038(char *arg)
{
    int v;

    if (func_ov002_02208014(arg)) {
        func_ov126_022a0c1c(arg);
        return;
    }

    v = func_ov002_02208008(arg);

    switch (func_ov095_02299a54(arg + 0x19c, v)) {
        case 1:
            func_ov002_0220a2b4(arg + 0x3f90);
            func_ov126_0229ff68(arg);
            break;
        case 2:
            func_ov002_0220a254(arg + 0x3f90);
            func_ov126_0229ff68(arg);
            break;
        case 3:
            func_ov002_0220a314(arg + 0x3f90);
            func_ov126_0229ff68(arg);
            break;
        case 4:
            func_ov002_0220a2b4(arg + 0x3f90);
            func_ov126_0229f7b8(arg, 0x80);
            func_ov002_02208098((void *) (arg), 6);
            func_ov126_0229ff68(arg);
            break;
        default:
            if (func_ov126_0229fe28(arg)) {
                return;
            }
            if (func_ov126_0229fdd4(arg)) {
                return;
            }
            if (func_ov126_0229fcfc(arg)) {
                return;
            }
            if (func_ov126_0229fd64(arg)) {
                return;
            }
            if (func_ov126_0229fcd8(arg)) {
                return;
            }
            break;
    }
}

void func_ov126_022a1020(int r0)
{
    int r4 = r0;
    if (func_ov002_02208014((void *) r0) != 0) {
        func_ov126_022a0bc8(r4);
    }
}

void func_ov126_022a0f40(UnkStruct_022a0f40 *self)
{
    int stat;
    int val;
    unsigned char prev;

    if (func_ov002_02208014(self) != 0) {
        func_ov126_022a0c1c((void *) self);
        return;
    }
    stat = func_ov126_022a0768(self, func_ov002_02208008((void *) self));
    switch (stat) {
        case 1:
            func_ov095_0229b3ec(self->unk_19C);
            func_ov126_022a0728(self);
            func_ov126_022a08c4(self);
            func_ov126_022a0168((void *) self);
            func_ov126_0229ff0c(self);
            func_0200467c(0xb);
            break;
        case 2:
            val = func_ov002_02209f00(self->unk_3F90);
            func_ov095_0229a134(self->unk_19C, val);
            func_ov126_022a0f20((void *) self);
            break;
        default:
            prev = self->unk_A8;
            if (func_ov126_0229fdd4((void *) self) != 0) {
                if (prev != self->unk_A8) {
                    func_ov126_0229ff0c(self);
                }
                break;
            }
            if (func_ov126_0229fcfc((void *) self) == 0 && func_ov126_0229fd64((void *) self) == 0 &&
                func_ov126_0229fcd8((void *) self) == 0 && (data_021fbe40.flag & 1) != 0) {
                func_ov002_02208098((void *) (self), 7);
                func_ov126_022a06b4(self);
            }
            break;
    }
}

void func_ov126_022a0f20(void *p)
{
    func_ov126_0229f7a8(p, 0x80);
    func_ov002_02208098((void *) (p), 4);
    func_ov126_0229ff68(p);
}

void func_ov126_022a0ec4(void *self)
{
    if (((*(unsigned short *) &data_021fbe40) & 1) == 0) {
        func_ov002_02208098((void *) (self), 6);
    } else {
        int ret = func_ov002_02208008(self);
        if (func_ov126_022a0768((UnkStruct_022a0f40 *) self, ret) == 1) {
            func_ov095_0229b3ec((unsigned char *) ((unsigned char *) self + 0x19c));
            func_ov126_022a0680(self);
            func_ov126_022a08c4((UnkStruct_022a0f40 *) self);
            func_ov126_022a0168(self);
            func_ov126_0229ff0c((UnkStruct_022a0f40 *) self);
            func_0200467c(0x15);
        }
    }
}
