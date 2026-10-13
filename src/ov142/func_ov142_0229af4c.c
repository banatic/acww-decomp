/* func_ov142_0229af4c @ 0x0229af4c, 0x48 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a2b4(void *);
extern int func_ov142_0229b04c(void *);
extern int func_ov142_0229afb0(void *);
extern void func_ov142_0229af1c(void *, int, int);

void func_ov142_0229af4c(void *p)
{
    unsigned char c;
    int a, b;

    c = *(unsigned char *) ((char *) p + 0xc0);
    if (c == 0x13 || (c >= 9 && c <= 0x11)) {
        func_ov002_0220a314((char *) p + 0xe8);
    } else {
        func_ov002_0220a2b4((char *) p + 0xe8);
    }
    a = func_ov142_0229b04c(p);
    b = func_ov142_0229afb0(p);
    func_ov142_0229af1c(p, a, b);
}
