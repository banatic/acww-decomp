/* func_ov137_0229d028 @ 0x0229d028, 0x28 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern void func_ov002_022080a0(void *p, int a);
extern void func_ov137_0229c978(void *p);
extern void func_ov137_0229cfa0(void *p);

void func_ov137_0229d028(void *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0(p, 2);
        func_ov137_0229c978(p);
    }
    func_ov137_0229cfa0(p);
}
