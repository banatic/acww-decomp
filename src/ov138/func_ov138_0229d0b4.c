/* func_ov138_0229d0b4 @ 0x0229d0b4, 0x28 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov138_0229c9c0(void *p);
extern void func_ov138_0229d02c(void *p);

void func_ov138_0229d0b4(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov138_0229c9c0(param);
    }
    func_ov138_0229d02c(param);
}
