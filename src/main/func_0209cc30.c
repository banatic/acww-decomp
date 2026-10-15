/* func_0209cc30 @ 0x0209cc30, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021dc584;
extern unsigned char data_021dc58c;
extern unsigned char data_021dc594;
extern unsigned int func_0209d014(unsigned int, unsigned int);
extern void func_0209d03c(unsigned char *);
extern void func_0209d038(void *);
extern void __register_global_object(void *, void *, void *);

unsigned char *func_0209cc30(unsigned char *base, unsigned int a1, unsigned int a2)
{
    unsigned int ret;

    ret = func_0209d014(a1, a2);
    if (ret < 0x24) {
        return base + (ret << 3);
    }
    if ((data_021dc584 & 1) == 0) {
        func_0209d03c(&data_021dc58c);
        __register_global_object((void *) (&data_021dc58c), (((void *) func_0209d038)), (void *) (&data_021dc594));
        data_021dc584 |= 1;
    }
    return &data_021dc58c;
}
