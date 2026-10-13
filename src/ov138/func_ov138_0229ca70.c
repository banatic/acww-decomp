/* func_ov138_0229ca70 @ 0x0229ca70, 0x62 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(const void *);
extern int func_0208e4bc(const void *);
extern int func_ov002_0220a6e0(const void *);
extern int func_ov002_0220a768(const void *, int);
extern int func_ov002_0220a72c(const void *, int);
extern void func_ov002_0220a0b4(const void *, int, int);
extern void func_ov138_0229c738(const void *);
extern void func_ov002_022080a0(const void *, int);

void func_ov138_0229ca70(void *p)
{
    if (func_ov002_0220a700((char *) p + 0xfc)) {
        if (func_0208e4bc((char *) p + 0x98)) {
            int a = func_ov002_0220a6e0((char *) p + 0xfc);
            int b = func_ov002_0220a768((char *) p + 0xfc, -1);
            int c = func_ov002_0220a72c((char *) p + 0xfc, -1);
            func_ov002_0220a0b4((char *) p + 0x98, a + b, a + c);
        }
    } else {
        func_ov138_0229c738(p);
        func_ov002_022080a0(p, 1);
    }
}
