/* func_02035a70 @ 0x02035a70, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int, int, int);
extern void func_02035638(int);
extern void func_02035624(int);

void func_02035a70(void *arg)
{
    unsigned short *p = (unsigned short *) arg;
    unsigned char *q = (unsigned char *) arg;
    if (p[4] != 0xffff) {
        func_02035684(10, 5, 5);
        func_02035638(p[4]);
        p[4] = 0xffff;
    }
    if (q[10] != 0) {
        func_02035624(10);
        func_02035684(10, 5, 5);
        q[10] = 0;
    }
}
