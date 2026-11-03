/* villager_residents_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207c5e4 @ 0x0207c5e4, 0xc0 bytes, Thumb
 * func_0207c598 @ 0x0207c598, 0x4c bytes, Thumb
 * func_0207c4e8 @ 0x0207c4e8, 0xb0 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x4050];
    long long a;
    long long b;
} UnkStruct_0207c5e4;

typedef struct {
    char pad_00[0x4050];
    long long unk_4050;
    long long unk_4058;
    char unk_4060[1];
} UnkStruct_0207c4e8;

extern int func_0207cad4(void *);
extern int func_0209dffc(long long *v);
extern int func_0209e3ac(void *p1, long long *v, int k);
extern int func_0209e380(long long *v, void *p1);
extern int func_020644cc(int n);
extern unsigned int func_0207c818(void *p, unsigned char mask);
extern int func_0207c8c8(void *p, unsigned int index, int arg);
extern char data_021d1554[];
extern int func_0207cd40(UnkStruct_0207c4e8 *self);
extern void *func_0207cec0(UnkStruct_0207c4e8 *self, int t);
extern void func_02081660(void *p);
extern void func_0207c9b8(char *p, UnkStruct_0207c4e8 *self);
extern void func_02081518(char *g, int id, int a, int b, int c);
extern void func_0207c3b0(UnkStruct_0207c4e8 *self, void *o, int t, char *g, int one, void *a1);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);

int func_0207c5e4(UnkStruct_0207c5e4 *s, void *p1)
{
    int n;
    int ok;

    if (func_0207cad4(s) < 8) {
        if (s->b == 0) {
            if (s->a == 0 || func_0209dffc(&s->a) != 0) {
                return 1;
            }
            if (func_0209e3ac(p1, &s->a, 0x3f) == 1) {
                if (func_0209e380(&s->a, p1) >= 1) {
                    return 1;
                }
            }
        } else if (func_0209e3ac(p1, &s->b, 0x3f) == 1) {
            n = func_0209e380(&s->b, p1);
            if (n > 0) {
                if (n >= 8) {
                    ok = 1;
                } else if (func_020644cc(8 - n) == 0) {
                    ok = 1;
                } else {
                    ok = 0;
                }
                if (ok != 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}

int func_0207c598(void *p)
{
    unsigned char mask = 0;
    int i;
    int a = 0;
    int b = 0;
    for (i = 0; i < 6; i++) {
        unsigned int result;
        int chk;
        result = func_0207c818(p, mask);
        if (result >= 6) {
            goto out;
        }
        chk = func_0207c8c8(p, result, a);
        if (chk != ~b) {
            return chk;
        }
        mask = (unsigned char) (mask | (1U << result));
    }
out:
    return -1;
}

void func_0207c4e8(UnkStruct_0207c4e8 *self, void *a1)
{
    int t;
    void *o;
    int id;

    if (func_0207c5e4((UnkStruct_0207c5e4 *) self, a1) == 0) {
        return;
    }
    t = func_0207cd40(self);
    o = func_0207cec0(self, t);
    if (o != 0) {
        func_02081660(o);
        func_0207c9b8(self->unk_4060, self);
        id = func_0207c598((void *) self);
        if (id != -1) {
            func_02081660(data_021d1554);
            func_02081518(data_021d1554, (unsigned char) id, 1, 0, 0);
            func_0207c3b0(self, o, t, data_021d1554, 1, a1);
        }
    }
    MI_CpuCopy8(a1, &self->unk_4050, 8);
    if (self->unk_4058 != 0) {
        MI_CpuCopy8(a1, &self->unk_4058, 8);
    }
}
