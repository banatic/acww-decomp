/* func_ov004_02240900 @ 0x02240900, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_02240900;

extern void func_ov004_02240a18(void *self, int a, int b, int c, int d);
extern void func_ov004_02241008(void *self, UnkStruct_02240900 *p, UnkStruct_02240900 *q);

void func_ov004_02240900(void *self)
{
    UnkStruct_02240900 p, q;
    func_ov004_02240a18(self, 0x3c, 0x50, 8, 3);
    p.a = 0x104;
    p.b = 0xc2;
    q.a = 0x1be;
    q.b = 0x15a;
    func_ov004_02241008(self, &p, &q);
}
