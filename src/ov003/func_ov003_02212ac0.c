/* func_ov003_02212ac0 @ 0x02212ac0, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02212bd8(void *, char *, char *, char *);
extern int func_ov003_02212c10(void *, char *, char *, char *, int, int);

void func_ov003_02212ac0(void *p, int n)
{
    char buf[3];
    func_ov003_02212bd8((char *) p + 0x8f0, buf, buf + 1, buf + 2);
    func_ov003_02212c10(p, buf, buf + 1, buf + 2, 6, n);
}
