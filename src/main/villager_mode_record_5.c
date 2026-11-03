/* villager_mode_record_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209bee8 @ 0x0209bee8, 0x40 bytes, Thumb
 * func_0209beb0 @ 0x0209beb0, 0x36 bytes, Thumb
 */

extern int func_0209c38c(void *b);
extern int func_0209c410(void *p, void *b);
extern void func_0209c42c(void *a, void *b, unsigned char r);
extern int func_0209c4a8(char *);
extern void func_0209c448(char *, int, unsigned char);

void func_0209bee8(char *a, void *b, int c)
{
    if (func_0209c38c(b)) {
        char *p;
        int r;
        p = a;
        p += 0x19;
        r = c + func_0209c410(p, b);
        if (r < 0) {
            r = 0;
        } else if (r > 10) {
            r = 10;
        }
        a += 0x19;
        func_0209c42c(a, b, r);
    }
}

void func_0209beb0(char *a, char *b, short *arr)
{
    int id;
    id = func_0209c4a8(b + 0x11);
    if (func_0209c38c((void *) id)) {
        func_0209c448(a + 0x11, id, (unsigned char) (arr[id] * 10 >> 12));
    }
}
