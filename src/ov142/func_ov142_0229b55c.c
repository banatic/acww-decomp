/* func_ov142_0229b55c @ 0x0229b55c, 0x3e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_02299ae0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_0229aec4(void *);
extern int func_ov142_0229b04c(void *);
extern int func_ov142_0229afb0(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov142_0229b55c(void *arg)
{
    int a, b;
    if (func_ov142_02299ae0(arg) != 0) {
        func_ov002_02208098((void *) (arg), 4);
        func_ov142_0229aec4(arg);
    }
    a = func_ov142_0229b04c(arg);
    b = func_ov142_0229afb0(arg);
    func_ov002_0220a0b4((char *) arg + 0xe8, a, b);
}
