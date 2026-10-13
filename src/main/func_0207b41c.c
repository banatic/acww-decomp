/* func_0207b41c @ 0x0207b41c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void *);
extern int func_02003704(void);
extern int func_02071efc(int, int);
extern void func_02080cd8(void *, short *);
extern void func_0207d71c(void *);
extern void func_0207f1c8(void *);
extern int func_0209b5e8(void);
extern int func_0209b91c(void);
extern int func_0209bd44(void);
extern int func_0209bba0(int);
extern void func_0209b908(int);
extern void func_02095238(void);
extern void func_0207f454(void *);

void func_0207b41c(void *p, int flag)
{
    int i;
    int j;
    int a;
    int b;
    int c;
    short s;

    i = 0;
    j = 0;
    for (i = 0; i < 8; i++) {
        func_0208150c(p);
        if (func_02003704() != 0) {
            if (flag == 0) {
                if (func_02071efc(i, j) != 0) {
                    s = 0x12a8;
                    func_02080cd8(p, &s);
                }
            }
            func_0207d71c(p);
            func_0207f1c8(p);
            a = func_0209b5e8();
            b = func_0209b91c();
            c = func_0209bd44();
            if (c != 0) {
                if (func_0209bba0(b) == 0) {
                    func_0209b908(a);
                    func_02095238();
                }
            }
            func_0207f454(p);
        }
        p = (char *) p + 0x7ec;
    }
}
