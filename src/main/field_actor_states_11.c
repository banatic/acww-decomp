/* field_actor_states_11: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200a6a0 @ 0x0200a6a0, 0x4e bytes, Thumb
 * func_0200a694 @ 0x0200a694, 0xc bytes, Thumb
 * func_0200a684 @ 0x0200a684, 0xe bytes, Thumb
 * func_0200a5f8 @ 0x0200a5f8, 0x8c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int a;
    unsigned int b;
} Src;

typedef struct {
    u32 a;
    u32 b;
} Src_0200a5f8;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200a6f0(void *, void *, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int func_0200f328(void *self, int a);
extern void func_020109a0(void *self, int a, int b, unsigned short c);
extern int func_0200fbe0(void *self);
extern void func_0205eae0(void *ptr, int a, int b, int c);

int func_0200a6a0(void *a, int *b, void *c, int d, short e)
{
    int local0[2];
    char local1[12];
    char local2[16];
    func_0200e92c(&local1);
    func_0200e90c(&local1, 0x1b, d, e);
    local0[0] = b[0];
    local0[1] = b[1];
    func_0200a6f0(&local2, local0, c);
    {
        int result = func_0200e894(a, &local1);
        func_0200e91c(&local1);
        return result;
    }
}

void func_0200a694(unsigned char *out, const Src *src, unsigned char val)
{
    out[1] = (unsigned char) src->a;
    out[2] = (unsigned char) src->b;
    out[0] = val;
}

void func_0200a684(unsigned char *a, unsigned int *b, unsigned char *c)
{
    b[0] = a[1];
    b[1] = a[2];
    c[0] = a[0];
}

void func_0200a5f8(void *selfv, u8 *param2, int previous)
{
    u8 *self = (u8 *) selfv;
    u8 *p;
    u8 b0d, b0e, b0c;
    u8 *field7d4;
    Src_0200a5f8 local;

    p = &param2[0xc];
    b0d = p[1];
    b0e = p[2];
    b0c = param2[0xc];

    field7d4 = self + 0x7d4;
    field7d4[1] = 0;
    field7d4[2] = b0d;
    field7d4[3] = b0e;
    field7d4[0] = b0c;

    local.a = b0d;
    local.b = b0e;
    func_0200a694((unsigned char *) (self + 0x8f0), (const Src *) (&local), (u8) b0c);

    *(u32 *) (self + 0x830) = 0x1000;
    *(u32 *) (self + 0x834) = 0x1000;
    *(u32 *) (self + 0x838) = 0x1000;

    func_0200f328(self, 0x4f);
    func_020109a0(self, 0x18, 3, 0);

    if (func_0200fbe0(self) == 4) {
        func_0205eae0(self + 0x5a0, 6, 3, 1);
    }
}
