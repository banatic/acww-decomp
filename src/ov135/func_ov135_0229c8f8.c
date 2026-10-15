/* func_ov135_0229c8f8 @ 0x0229c8f8, 0x2c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov135_0229c738(void *p);
extern void func_ov135_0229c554(void *p, int n);
extern void func_ov134_0229a3e4(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov135_0229c8f8(void *obj)
{
    func_ov135_0229c738(obj);
    func_ov135_0229c554(obj, 2);
    func_ov134_0229a3e4((char *) obj + 0x2c8);
    func_ov002_02208098((void *) (obj), 15);
}
