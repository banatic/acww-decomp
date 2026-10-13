/* func_0205d034 @ 0x0205d034, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205cfd4(void *p);
extern int func_021077e8(void);
extern void *func_0205cfc0(void *p);
extern void func_02055b50(void *p, int x);

void func_0205d034(void *p)
{
    int x;
    void *q;
    func_0205cfd4(p);
    x = func_021077e8();
    q = func_0205cfc0(p);
    func_02055b50(q, x);
}
