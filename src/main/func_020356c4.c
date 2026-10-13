/* func_020356c4 @ 0x020356c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020374d0(void *p, int a, int b, int c);
extern void func_02035198(unsigned int val, void *p);
extern void func_020374cc(void *p);
extern unsigned int data_021c526c;

void func_020356c4(int a, int b, int c, int d)
{
    struct {
        int field0;
        int field1;
        unsigned char buf[32];
    } local;

    local.field0 = 0;
    local.field1 = d;
    func_020374d0(local.buf, a, b, c);
    func_02035198(data_021c526c, local.buf);
    func_020374cc(local.buf);
}
