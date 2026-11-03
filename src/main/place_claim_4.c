/* place_claim_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205349c @ 0x0205349c, 0x10 bytes, Thumb
 * func_02053498 @ 0x02053498, 0x2 bytes, Thumb
 * func_0205347c @ 0x0205347c, 0x1c bytes, Thumb
 * func_0205346c @ 0x0205346c, 0xe bytes, Thumb
 * func_02053450 @ 0x02053450, 0x1c bytes, Thumb
 * func_02053448 @ 0x02053448, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned char unk_10;
} UnkStruct_0205346c;

struct UnkStruct_02053450 {
    unsigned char flag;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned char val;
};

struct In {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

extern void __cxa_vec_cleanup(void *a, int b, int c, void (*dtor)(void *));

void func_0205346c(UnkStruct_0205346c *arg0);

int func_0205349c(int a)
{
    func_0205346c((UnkStruct_0205346c *) a);
    return a;
}

void func_02053498(void *object) {}

void *func_0205347c(void *a)
{
    __cxa_vec_cleanup(a, 4, 20, func_02053498);
    return a;
}

void func_0205346c(UnkStruct_0205346c *arg0)
{
    arg0->unk_00 = 0;
    arg0->unk_04 = 0;
    arg0->unk_08 = 0;
    arg0->unk_0C = 0;
    arg0->unk_10 = 0;
}

int func_02053450(struct UnkStruct_02053450 *out, unsigned char val, struct In *in)
{
    out->flag = 1;
    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    out->val = val;
    return 1;
}

int func_02053448(unsigned char *p0)
{
    p0[0] = 0;
    return 1;
}
