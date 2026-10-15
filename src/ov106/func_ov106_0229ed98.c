/* func_ov106_0229ed98 @ 0x0229ed98, 0x4c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov106_0229c364(void *p, int a);
extern void func_ov106_0229c344(void *p, int a);
extern void func_ov106_0229d73c(void *p);
extern void func_ov106_0229eadc(void *p);

void func_ov106_0229ed98(void *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0((void *) (p), 2);
        if (func_ov106_0229c364(p, 0x4000) != 0) {
            func_ov106_0229c344(p, 0x4000);
            func_ov002_02208098((void *) (p), 0x24);
        } else {
            func_ov106_0229d73c(p);
        }
    }
    func_ov106_0229eadc(p);
}
