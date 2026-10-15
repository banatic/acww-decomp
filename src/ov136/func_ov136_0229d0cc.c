/* func_ov136_0229d0cc @ 0x0229d0cc, 0x28 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *obj, int value);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov136_0229c974(void *obj);
extern void func_ov136_0229d044(void *obj);

void func_ov136_0229d0cc(void *obj)
{
    if (func_ov002_02207f48(obj, 0)) {
        func_ov002_022080a0((void *) (obj), 2);
        func_ov136_0229c974(obj);
    }
    func_ov136_0229d044(obj);
}
