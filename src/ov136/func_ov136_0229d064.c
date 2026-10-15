/* func_ov136_0229d064 @ 0x0229d064, 0x30 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int n);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov136_0229d044(void *a);

void func_ov136_0229d064(void *a)
{
    if (func_ov002_02207f3c(a, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (a), 5);
    } else {
        func_ov136_0229d044(a);
    }
}
