/* func_ov091_0229914c @ 0x0229914c, 0x64 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b57c(void *);
extern int func_0208e4bc(void *);
extern int func_ov002_0220b5ec(void *, int);
extern int func_ov002_0220b59c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);
extern void func_ov002_02208090(void *, int);

void func_ov091_0229914c(void *p)
{
    if (func_ov002_0220b57c((char *) p + 0x3bc)) {
        if (func_0208e4bc((char *) p + 0x434)) {
            int a, b;
            a = func_ov002_0220b5ec((char *) p + 0x3bc, 1);
            b = func_ov002_0220b59c((char *) p + 0x3bc, 1);
            func_ov002_0220a0b4((char *) p + 0x434, a, b);
        }
    } else {
        func_ov002_0220a374((char *) p + 0x434, 0);
        func_ov002_02208090(p, 4);
    }
}
