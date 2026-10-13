/* func_020790a8 @ 0x020790a8, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(char *);
extern int func_02003704(int);
extern int func_0207f150(char *);
extern void func_0207d634(char *);
extern char *func_020807c0(char *, int);
extern int func_02081edc(char *);
extern void func_020819d0(char *);
extern void func_0208199c(char *);
extern void func_02081960(char *);
extern void func_02081924(char *);
extern void func_020818e8(char *);
extern void func_020818ac(char *);
extern void func_02081878(char *);
extern void func_02080fc0(char *, int);
extern void func_02080e5c(char *, int);

void func_020790a8(char *p, int q)
{
    int x = q;
    int y = 0;
    int z = 0;
    int i, j;
    char *r4;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) != 0) {
            if (func_0207f150(p) == 3) {
                func_0207d634(p);
            }
            r4 = func_020807c0(p, y);
            for (j = z; j < 8; j++) {
                if (func_02081edc(r4) != 0) {
                    func_020819d0(r4);
                    func_0208199c(r4);
                    func_02081960(r4);
                    func_02081924(r4);
                    func_020818e8(r4);
                    func_020818ac(r4);
                    func_02081878(r4);
                }
                r4 += 0x80;
            }
            func_02080fc0(p, x);
            func_02080e5c(p, x);
        }
        p += 0x7ec;
    }
}
