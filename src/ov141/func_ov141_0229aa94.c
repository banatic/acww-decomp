/* func_ov141_0229aa94 @ 0x0229aa94, 0x2e bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *param, int arg);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov141_0229a560(void *param);
extern void func_ov141_02299fcc(void *receiver);
extern void func_ov141_0229aa04(void *param);

void func_ov141_0229aa94(void *param)
{
    if (func_ov002_02207f48(param, 0)) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov141_0229a560(param);
        func_ov141_02299fcc(param);
    }
    func_ov141_0229aa04(param);
}
