/* func_02054f68 @ 0x02054f68, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad0[0x4C];
    unsigned int unk_4C;
    unsigned int unk_50;
    unsigned int unk_54;
} UnkStruct_02054f68;
typedef struct {
    void *unk_00;
    char pad0[0xB0];
    UnkStruct_02054f68 *t;
    char pad_B8[0x1C];
    void *u;
} UnkStruct_02054f68_2;
void func_02054f68(UnkStruct_02054f68_2 *s, int arg2)
{
    unsigned char *ptr;
    unsigned int val2;
    unsigned int val;
    unsigned int mode = ((unsigned char *) s->unk_00)[1];
    if (mode >= 2) {
        unsigned char *u;
        unsigned int a;
        unsigned int b;
        unsigned int w;
        unsigned char *q;
        unsigned char *q4;
        UnkStruct_02054f68 *t;
        u = (unsigned char *) s->u;
        a = *((unsigned short *) (u + 6));
        b = *((unsigned short *) (u + a));
        b = b * mode;
        q = (u + a) + b;
        w = *((unsigned int *) (q + 4));
        val = w;
        q = u + val;
        ptr = q + 4;
        q4 = ptr;
        t = s->t;
        t->unk_4C = *((unsigned int *) ptr);
        t->unk_50 = *((unsigned int *) (q4 + 4));
        t->unk_54 = *((unsigned int *) (q4 + 8));
    } else if ((mode == 1) && (arg2 != 0)) {
        unsigned char *base;
        unsigned char *p;
        unsigned int a;
        unsigned int b;
        unsigned int w;
        unsigned int cur;
        UnkStruct_02054f68 *t;
        base = (unsigned char *) s->u;
        a = *((unsigned short *) (base + 6));
        val2 = a;
        p = base + val2;
        t = s->t;
        cur = t->unk_50;
        b = *((unsigned short *) p);
        b = b * mode;
        p = p + b;
        w = *((unsigned int *) (p + 4));
        p = base + w;
        cur += (*((unsigned int *) (p + 8))) - arg2;
        t->unk_50 = cur;
    }
}
