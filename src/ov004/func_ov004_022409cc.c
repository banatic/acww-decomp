/* func_ov004_022409cc @ 0x022409cc, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_022409cc;

extern void func_ov004_02240a18(void *self, int a, int b, int c, int d);
extern void func_ov004_02241008(void *self, UnkStruct_022409cc *p, UnkStruct_022409cc *q);

void func_ov004_022409cc(void *self)
{
    UnkStruct_022409cc p, q;
    func_ov004_02240a18(self, 0x3c, 0x46, 6, 1);
    p.a = 0x104;
    p.b = 0xc2;
    q.a = 0x1be;
    q.b = 0x15a;
    func_ov004_02241008(self, &p, &q);
}
