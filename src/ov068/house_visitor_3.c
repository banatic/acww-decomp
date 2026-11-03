/* house_visitor_3: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02275b1c @ 0x02275b1c, 0x70 bytes, Thumb
 * func_ov068_02275ad0 @ 0x02275ad0, 0x4c bytes, Thumb
 */

typedef struct {
    short a, b;
} UnkStruct_02275b1c;

typedef struct {
    int p, q;
} Pair;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x8e - 0x68];
    short unk_8E;
    char pad_90[2];
    UnkStruct_02275b1c unk_92;
    char pad_96[0x350 - 0x96];
    char sub[0xa44 - 0x350];
    Pair a44;
} UnkStruct_02275b1c_2;

extern int data_020ca0e4;
extern int data_020ca0e8;
extern Pair __ptmf_null;
extern void func_0201aff4(void *, int);
extern int func_ov068_022763e4(void *unused0);
extern void *func_020961a8(int);
extern int func_020ea990(void *, void *);
extern int func_0203e0a8(void *, int);

int func_ov068_02275b1c(UnkStruct_02275b1c_2 *p)
{
    UnkStruct_02275b1c *h;
    p->unk_5C = data_020ca0e4;
    p->unk_64 = data_020ca0e8 - 0x1000;
    h = &p->unk_92;
    h->b = -0x8000;
    p->unk_8E = h->b;
    func_0201aff4(p->sub, -32768);
    p->a44 = __ptmf_null;
    *((char *) p + 0x510) = 0;
    return 1;
}

void func_ov068_02275ad0(void *param)
{
    void *p;
    int result;
    int i;
    int *q;
    int local[4];

    if (func_ov068_022763e4(param)) {
        p = func_020961a8(4);
        if (p) {
            q = (int *) ((char *) p + 0x5c);
            local[0] = *(int *) ((char *) p + 0x5c);
            local[1] = q[1];
            local[2] = q[2];
            result = func_020ea990(local, (char *) param + 0x5c);
            if (result > 0x4e66) {
                func_0203e0a8(param, 0);
            }
        }
    }
}
