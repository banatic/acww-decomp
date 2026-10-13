/* func_ov004_02240944 @ 0x02240944, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_02240944;

extern void func_ov004_02240a18(void *self, int a, int b, int c, int d);
extern void func_ov004_02241008(void *self, UnkStruct_02240944 *p, UnkStruct_02240944 *q);

void func_ov004_02240944(void *self)
{
    UnkStruct_02240944 p, q;
    func_ov004_02240a18(self, 0x3c, 0x50, 8, 2);
    p.a = 0x104;
    p.b = 0xc2;
    q.a = 0x1be;
    q.b = 0x15a;
    func_ov004_02241008(self, &p, &q);
}
