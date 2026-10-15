/* func_ov099_0229c6dc @ 0x0229c6dc, 0x78 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229c2ac(void *p, int n);
extern int func_ov099_0229c788(void *p);
extern int func_ov099_0229c778(void *p);
extern void func_ov099_0229c28c(void *p, int n);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov099_0229c6dc(void *base)
{
    if (func_ov099_0229c2ac(base, 8)) {
        int first = func_ov099_0229c788(base);
        int second = func_ov099_0229c778(base);
        func_ov002_0220a0b4((void *) ((char *) base + 0x2274), first, second);
        func_ov099_0229c28c(base, 8);
    } else {
        int first = func_ov099_0229c788(base);
        int second = func_ov099_0229c778(base);
        func_ov002_0220a05c((void *) ((char *) base + 0x2274), first, second, 3, 1);
        *((unsigned char *) base + 0x290a) = *((unsigned char *) base + 0x8d);
        func_ov002_02208098(base, 8);
    }
}
