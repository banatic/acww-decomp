/* func_0207a964 @ 0x0207a964, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020791ec(void);
extern int func_0207aa08(void *obj, void *p);
extern void func_02079204(char c);
extern void func_020791d4(char c);
extern int func_020791bc(void);
extern int func_0207cec0(void *obj, int a);
extern int func_02080928(void);
extern int func_0207aa8c(void *obj, int a);
extern int func_0207b3dc(void *obj);
extern void func_0209a77c(void *p);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

void func_0207a964(void *obj)
{
    Pair p;
    int a;
    int b;

    p.unk_00 = 0;
    p.w1 = 0;
    b = func_020791ec();
    func_0209e474(&p);
    a = func_0207aa08(obj, &p);
    if (a == -1) {
        func_02079204(-1);
        func_020791d4(-1);
    } else if (a == b) {
        if (func_0207cec0(obj, func_020791bc()) != 0) {
            if (func_02080928() != 0) {
                return;
            }
        }
        func_020791d4((char) func_0207aa8c(obj, b));
    } else if (a != b) {
        b = func_0207aa8c(obj, a);
        func_02079204((char) a);
        func_020791d4((char) b);
        if (a == func_0207b3dc(obj)) {
            func_0209a77c((char *) obj + 0x3f90);
        }
    }
}
