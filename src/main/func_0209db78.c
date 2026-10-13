/* func_0209db78 @ 0x0209db78, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df04(unsigned long long *out, unsigned long long *in);
extern int func_0209e350(unsigned long long *a, unsigned long long *b);

int func_0209db78(int unused, unsigned long long *p)
{
    unsigned long long local = 0;

    func_0209df04(&local, p);
    if (local < *p) {
        return func_0209e350(&local, p);
    } else {
        return -func_0209e350(p, &local);
    }
}
