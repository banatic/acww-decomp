/* func_0206e928 @ 0x0206e928, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02004118(void *);
extern void func_0206ea84(void *, void *);

extern unsigned char data_021cfbcc[];
extern unsigned char data_021f3b68[];

void func_0206e928(void)
{
    void *ptr = func_02004118((void *) data_021cfbcc);
    if (ptr != 0) {
        func_0206ea84((void *) data_021f3b68, ptr);
    }
}
