/* func_ov104_0229ec0c @ 0x0229ec0c, 0x3e bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_0206fe60(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov104_0229eb88(int a);

void func_ov104_0229ec0c(int arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0((void *) (arg), 2);
        if (func_0206fe60()) {
            func_ov002_02208098((void *) (arg), 5);
        } else {
            func_ov002_02208098((void *) (arg), 9);
        }
    } else {
        func_ov104_0229eb88(arg);
    }
}
