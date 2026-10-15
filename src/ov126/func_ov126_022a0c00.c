/* func_ov126_022a0c00 @ 0x022a0c00, 0x1c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207fc0(void *p);
extern void func_ov126_022a0000(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

unsigned char *func_ov126_022a0c00(void *p)
{
    func_ov002_02207fc0(p);
    func_ov126_022a0000(p);
    return func_ov002_02208098((void *) (p), 4);
}
