/* func_0204886c @ 0x0204886c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021e5a2c[];
extern void *func_0207b3dc(void *);
extern void *func_0207cec0(void *, int);
extern int func_020405a8(void *, void *);
extern void *func_0207f1c8(void *);
extern void *func_0209b5ec(void *);
extern int func_0209c330(void *);
extern void *func_020800d0(void *);
extern int func_02081f80(void *);
extern void func_020488e4(void *, int, int *, int);

void func_0204886c(void *a0, int a1, int a2, int a3)
{
    void *saved;
    void *p;
    int i;
    int tmp[2];
    int b0;
    int b1;

    saved = func_0207b3dc(data_021e5a2c);

    for (i = 0; i < 8; i++) {
        p = func_0207cec0(data_021e5a2c, i);

        if (func_020405a8(p, saved) == 0) {
            continue;
        }

        if (a2 == 0) {
            if (func_0209c330((func_0209b5ec((void *) func_0207f1c8(p)))) != 5) {
                continue;
            }
        }

        p = func_020800d0(p);

        if (func_02081f80(p) == 0) {
            continue;
        }

        b1 = ((unsigned char *) p)[1];
        b0 = ((unsigned char *) p)[0];
        tmp[0] = b0;
        tmp[1] = b1;

        func_020488e4(a0, a1, tmp, a3);
    }
}
