/* func_020b98c4 @ 0x020b98c4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065c2c(void *ptr, void *arg);

extern unsigned char data_021f6c98[];

void func_020b98c4(void *arg)
{
    void *ptr;
    void *r1;

    r1 = arg;
    if (r1 != 0) {
        r1 = (char *) r1 + 4;
    }
    ptr = (void *) data_021f6c98;
    func_02065c2c(ptr, r1);
}
