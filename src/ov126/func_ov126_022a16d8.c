/* func_ov126_022a16d8 @ 0x022a16d8, 0x24 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov126_022a0be0(int a);

void func_ov126_022a16d8(int param)
{
    if (func_ov002_02207f48(param, -1)) {
        func_ov002_022080a0((void *) (param), 2);
        func_ov126_022a0be0(param);
    }
}
