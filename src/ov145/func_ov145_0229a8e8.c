/* func_ov145_0229a8e8 @ 0x0229a8e8, 0x3e bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *ptr, int a, int b, int c);
extern int func_ov002_02207f60(void *ptr);
extern void func_ov145_0229a134(void *ptr);

void func_ov145_0229a8e8(void *obj)
{
    int zero = 0;
    func_ov002_02207e80(obj, 6, zero, zero);
    func_ov002_02207e80(obj, 4, 0, 0x18 - *(int *) ((char *) obj + 0x9c));
    *(int *) ((char *) obj + 0x94) = func_ov002_02207f60(obj);
    func_ov145_0229a134(obj);
}
