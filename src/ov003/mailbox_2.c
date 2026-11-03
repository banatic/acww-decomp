/* mailbox_2: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221e424 @ 0x0221e424, 0x12 bytes, Thumb
 * func_ov003_0221e404 @ 0x0221e404, 0x20 bytes, Thumb
 */

extern int func_020b2800(void *arg, int n);
extern int func_0203e020(unsigned char *);

int func_ov003_0221e424(void *arg)
{
    func_020b2800(arg, 5);
    return 1;
}

void func_ov003_0221e404(unsigned char *data)
{
    if (data[0x134] == 0 || data[0x134] == 2) {
        func_0203e020(data);
    }
}
