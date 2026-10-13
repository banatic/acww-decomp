/* func_ov068_0226e604 @ 0x0226e604, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035624(int);
extern void func_02035684(int, int, int);
extern int func_020e8858(void *);
extern void func_020ee470(void *);

int func_ov068_0226e604(void *arg0)
{
    if (func_020e8858((char *) arg0 + 0x724) == 0) {
        func_02035624(0x13);
        func_02035684(0x12, 5, 5);
        func_020ee470(arg0);
    }
    return 1;
}
