/* func_020b3340 @ 0x020b3340, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b36c8(void *);
extern int func_020b3658(void *);
extern void func_020b3438(void *, void *, int);
extern void func_020b3598(void *, void *, int);
extern void func_020b35e8(void *, void *, int);

void func_020b3340(void *p1, void *p2)
{
    char *base;
    int r6;

    base = (char *) p1;
    func_020b36c8(p1);
    r6 = func_020b3658(p1);
    if (p2 != 0) {
        func_020b3438(base + 0x18, p2, r6);
        func_020b3598(base + 0x34, p2, r6);
        base += 0x14;
        func_020b35e8(base, p2, r6);
    }
}
