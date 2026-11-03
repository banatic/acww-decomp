/* villager_talk_object_5: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020257f0 @ 0x020257f0, 0x88 bytes, Thumb
 * func_020257c0 @ 0x020257c0, 0x30 bytes, Thumb
 * func_02025738 @ 0x02025738, 0x88 bytes, Thumb
 * func_020255d8 @ 0x020255d8, 0x160 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

struct Table {
    int word;
    unsigned char unk_04;
};

struct Pair {
    int a;
    int b;
};

typedef struct {
    int n;
    unsigned char b;
} UnkStruct_020255d8;

typedef void (*Fn)(void *self, UnkStruct_020255d8 *out);

typedef struct {
    int fn;
    int adj;
} Pmf;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x164 - 0xb8];
    int unk_164;
} UnkStruct_020255d8_2;

typedef struct {
    int a;
    int b;
} Pair_020255d8;

extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(char *, char *, char *, int, int, int, int, int, int);
extern char data_020c8b58;
extern char data_020c8a58;
extern Pair data_020d9398;
extern int func_02014f60(void *);
extern void func_0209ba7c(int);
extern void func_0207863c(int);
extern struct Table data_020c8ce0;
extern struct Table data_020c8ad8;
extern struct Pair data_020d8f90;
extern Pair_020255d8 data_020d8f38;
extern Pair_020255d8 data_020d8fd0;
extern u16 *func_0209b8c4(int a);
extern void func_0202da88(UnkStruct_020255d8_2 *self, void *tbl);
extern void func_0206844c(int a, void *b, int c);
extern int func_0209bb70(void *a);
extern int func_02029a18(int a);
extern void func_02015800(UnkStruct_020255d8_2 *self, int b, int c, int d);
extern int func_02015828(UnkStruct_020255d8_2 *self, int b);
extern void func_0202dbf0(UnkStruct_020255d8_2 *self, Pair_020255d8 p);
extern unsigned char data_021c2d94[];

void func_020257f0(char *a, char *b)
{
    char *p;
    int local0;
    int val;
    p = &data_020c8b58;
    if (func_0209bc40(func_0202d9c4(a)) == 1) {
        p = &data_020c8a58;
    }
    local0 = func_020036e8(func_0208150c(*((int *) ((*((char **) (a + 0x100))) + 0x830))));
    val = 0x122;
    func_0202da38(a, a + 0x104, a + val, 0x1e, local0, *((int *) p), *((unsigned char *) (p + 4)), 0, 0);
    *((void **) b) = a + 0x104;
    *((unsigned char *) (b + 4)) = *((unsigned char *) (a + val));
    *(Pair *) (a + 0xc8) = data_020d9398;
}

void func_020257c0(void *arg0)
{
    func_02014f60(arg0);
    func_0209ba7c(*(int *) ((char *) arg0 + 0x164));
    func_0207863c(*(int *) (*(char **) ((char *) arg0 + 0x100) + 0x830));
}

void func_02025738(char *a, char *b)
{
    struct Table *t;
    void *p;
    int val;
    int temp;
    int v;

    t = &data_020c8ce0;
    if (func_0209bc40((int) ((unsigned char *) (unsigned int) func_0202d9c4((void *) a))) == 1) {
        t = &data_020c8ad8;
    }

    p = *(void **) (a + 0x100);
    val = *(int *) ((char *) p + 0x830);
    temp = func_0208150c(val);
    v = func_020036e8(temp);

    func_0202da38(a, a + 0x104, a + 0x122, 0x1e, v, t->word, t->unk_04, 0, 0);

    *(char **) b = a + 0x104;
    *(unsigned char *) (b + 4) = *(unsigned char *) (a + 0x122);

    *(struct Pair *) (a + 0xc8) = data_020d8f90;
}

void func_020255d8(UnkStruct_020255d8_2 *self)
{
    UnkStruct_020255d8 out;

    switch (func_0209bc40((int) ((void *) func_0202d9c4((void *) self)))) {
        case 0: {
            unsigned char arg;
            int ok;
            u16 h;
            u16 *p;
            p = func_0209b8c4(self->unk_164);
            ok = 0;
            h = *p;
            if (h >= 0x12b0 && h <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                func_0202da88(self, (void *) data_021c2d94);
                if (((volatile Pmf *) &self->pmf)->fn != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn fp;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        fp = (Fn) * (int *) (*(char **) t + pm->fn);
                    } else {
                        fp = (Fn) pm->fn;
                    }
                    fp(t, &out);
                }
                arg = out.b;
                func_0206844c(self->unk_40, &arg, out.n);
            } else {
                func_02015800(self, func_02029a18(func_0209bb70((void *) func_0202d9c4((void *) self))), 0xd, 1);
                func_02015828(self, 0);
                func_0202dbf0(self, data_020d8f38);
            }
            break;
        }
        case 1: {
            unsigned char arg2;
            int ok;
            u16 h;
            u16 *p;
            p = func_0209b8c4(self->unk_164);
            ok = 0;
            h = *p;
            if (h >= 0x12e8 && h <= 0x131f) {
                ok = 1;
            }
            if (ok != 0) {
                func_0202da88(self, (void *) data_021c2d94);
                if (((volatile Pmf *) &self->pmf)->fn != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn fp;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        fp = (Fn) * (int *) (*(char **) t + pm->fn);
                    } else {
                        fp = (Fn) pm->fn;
                    }
                    fp(t, &out);
                }
                arg2 = out.b;
                func_0206844c(self->unk_40, &arg2, out.n);
            } else {
                func_02015800(self, func_02029a18(func_0209bb70((void *) func_0202d9c4((void *) self))), 0xd, 1);
                func_02015828(self, 0);
                func_0202dbf0(self, data_020d8fd0);
            }
            break;
        }
    }
}
