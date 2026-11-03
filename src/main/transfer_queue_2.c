/* transfer_queue_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9990 @ 0x020b9990, 0x10 bytes, Thumb
 * func_020b9978 @ 0x020b9978, 0x18 bytes, Thumb
 * func_020b9960 @ 0x020b9960, 0x18 bytes, Thumb
 */

extern void func_02065c68(void *ptr);
extern unsigned char data_021f6ca0[];
extern int func_02065c2c(void *a, void *b);
extern int func_020e8ce0(void *a, void *b);

void func_020b9990(void)
{
    func_02065c68((void *) data_021f6ca0);
}

int func_020b9978(void *p)
{
    void *q;
    q = p;
    if (q) {
        q = (char *) q + 4;
    }
    return func_02065c2c(((char *) data_021f6ca0), q);
}

int func_020b9960(void *arg0)
{
    void *ptr = arg0;
    if (ptr != 0) {
        ptr = (char *) ptr + 4;
    }
    return func_020e8ce0((void *) data_021f6ca0, ptr);
}
