/* func_ov107_0229dcdc @ 0x0229dcdc, 0x4c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov107_0229c294(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

void func_ov107_0229dcdc(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (param), 5);
        func_ov107_0229c294(param, 1);
        func_ov107_0229c294(param, 2);
    } else {
        func_ov002_02207e80(param, 6, 0, -16);
    }
    *(int *) ((char *) param + 0x98) = func_ov002_02207f60(param);
}
