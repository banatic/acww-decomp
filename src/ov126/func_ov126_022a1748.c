/* func_ov126_022a1748 @ 0x022a1748, 0x24 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int value);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov126_022a0b90(void *p);

void func_ov126_022a1748(void *p)
{
    if (func_ov002_02207f48(p, -1)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov126_022a0b90(p);
    }
}
