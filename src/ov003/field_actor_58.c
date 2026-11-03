/* field_actor_58: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02219874 @ 0x02219874, 0x3c bytes, Thumb
 * func_ov003_02219840 @ 0x02219840, 0x34 bytes, Thumb
 * func_ov003_022197c4 @ 0x022197c4, 0x7c bytes, Thumb
 * func_ov003_02219774 @ 0x02219774, 0x50 bytes, Thumb
 */

struct UnkStruct_02219874 {
    char pad_00[0x7f0];
    int a;
    char pad_7F4[8];
    int b;
};

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
} UnkStruct_02219840;

struct UnkStruct_022197c4_2 {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

struct UnkStruct_022197c4 {
    char pad_00[0x68];
    int unk_68;
};

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_02219774;

extern int func_ov003_02218fac(struct UnkStruct_02219874 *, int, int, int);
extern int func_ov003_0220d69c(UnkStruct_02219840 *ptr, int a, int b);
extern void *func_02096718(int);
extern int func_02073908(void *, int);
extern int func_02008258(void *, int);
extern int func_0203e140(void);
extern int func_0200d4e8(void *, int, int, int);
extern int func_ov003_02210154(void *, int, int);
extern struct UnkStruct_022197c4 *data_020ccf94;
extern int func_02095518(int, int, int);

int func_ov003_02219874(void)
{
    struct UnkStruct_02219874 *p = (struct UnkStruct_02219874 *) func_02096718(4);
    if (p) {
        p->b = func_02008258((void *) p, p->a);
        return func_ov003_02218fac(p, 3, 5, -1);
    } else {
        return 0;
    }
}

int func_ov003_02219840(void)
{
    UnkStruct_02219840 *ptr = (UnkStruct_02219840 *) func_02096718(4);
    if (ptr != 0) {
        if (ptr->unk_7F0 == 0x89) {
            return 0;
        }
        return func_ov003_0220d69c(ptr, 6, -1);
    } else {
        return 0;
    }
}

int func_ov003_022197c4(int a, int b)
{
    struct UnkStruct_022197c4_2 *o = (struct UnkStruct_022197c4_2 *) func_02096718(b);
    if (b == 4) {
        b = data_020ccf94->unk_68;
    }
    if (o != 0) {
        if (func_02073908(data_020ccf94, b) != 0) {
            o->unk_7FC = func_02008258(o, o->unk_7F0);
            switch (a) {
                case 0:
                    func_0203e140();
                    func_0200d4e8(o, 3, 1, -1);
                    break;
                case 1:
                    func_ov003_02210154(o, 6, -1);
                    break;
            }
        }
        return 1;
    }
    return 0;
}

int func_ov003_02219774(void)
{
    UnkStruct_02219774 *x = (UnkStruct_02219774 *) func_02096718(4);
    int v;
    if (x != 0) {
        func_0203e140();
        v = x->unk_7F0;
        if (v != 0x77) {
            x->unk_7FC = func_02008258(x, v);
            func_0200d4e8(x, 3, 1, -1);
        }
        func_02095518(0, 0, 4);
        return 1;
    }
    return 0;
}
