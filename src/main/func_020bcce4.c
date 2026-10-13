/* func_020bcce4 @ 0x020bcce4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020644cc(int);
extern int func_020bce60(void *, void *);
extern void func_020bcda0(void *, void *, int, int);
extern void func_020bcd7c(void *, void *);

void func_020bcce4(unsigned char *self)
{
    int *count;
    void *p;

    count = (int *) (self + 0x2f34);
    *count -= 1;
    if (*count > 0) {
        return;
    }

    p = func_020644cc(4);
    if (func_020bce60(self, p) == 0) {
        return;
    }

    func_020bcda0(self, p, 1, 1);
    func_020bcd7c(self, self + 0x2f34);
}
