/* func_ov106_0229ebcc @ 0x0229ebcc, 0x3e bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_0206fe60(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov106_0229eb28(int a);

void func_ov106_0229ebcc(int arg0)
{
    if (func_ov002_02207f48(arg0, 0) != 0) {
        if (((void) ((int) func_ov002_022080a0((void *) (arg0), 2)), func_0206fe60()) != 0) {
            func_ov002_02208098((void *) (arg0), 5);
        } else {
            func_ov002_02208098((void *) (arg0), 9);
        }
    } else {
        func_ov106_0229eb28(arg0);
    }
}
