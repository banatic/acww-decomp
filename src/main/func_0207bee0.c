/* func_0207bee0 @ 0x0207bee0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208150c(char *p);
extern int func_02003704(void *p);
extern void *func_0207f1c8(char *p);
extern int func_0209b5ec(void *p);
extern int func_0209c2c0(void);
extern int func_0209c020(int a, int b);
extern void func_0207f414(char *p, int a, int b);

void func_0207bee0(char *p)
{
    int i = 0;
    volatile int local = 0;

    do {
        if (func_02003704(func_0208150c(p))) {
            int r6;
            int r7;
            int result;

            r6 = func_0209b5ec(func_0207f1c8(p));
            r7 = func_0209c2c0();
            result = func_0209c020(r6, local);
            if (result != 0xc) {
                func_0207f414(p, result, r7);
            }
        }
        p += 0x7ec;
        i++;
    } while (i < 8);
}
