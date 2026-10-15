/* func_ov132_0229b608 @ 0x0229b608, 0x28 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *arg, int val);
extern unsigned char *func_ov002_022080a0(void *arg, unsigned char value);
extern void func_ov132_0229b104(void *arg);
extern void func_ov132_0229b578(void *arg);

void func_ov132_0229b608(void *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0(arg, 2);
        func_ov132_0229b104(arg);
    }
    func_ov132_0229b578(arg);
}
