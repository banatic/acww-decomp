/* transfer_queue: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b98dc @ 0x020b98dc, 0x10 bytes, Thumb
 * func_020b98c4 @ 0x020b98c4, 0x18 bytes, Thumb
 * func_020b98ac @ 0x020b98ac, 0x18 bytes, Thumb
 */

extern void func_02065c68(void *arg);
extern int func_02065c2c(void *ptr, void *arg);
extern unsigned char data_021f6c98[];
extern int func_020e8ce0(void *param1, void *param2);

void func_020b98dc(void)
{
    func_02065c68(((int *) data_021f6c98));
}

int func_020b98c4(void *arg)
{
    void *ptr;
    void *r1;

    r1 = arg;
    if (r1 != 0) {
        r1 = (char *) r1 + 4;
    }
    ptr = (void *) data_021f6c98;
    return func_02065c2c(ptr, r1);
}

void func_020b98ac(void *param1)
{
    void *r1 = param1;
    if (r1 != 0) {
        r1 = (char *) r1 + 4;
    }
    func_020e8ce0((void *) data_021f6c98, r1);
}
