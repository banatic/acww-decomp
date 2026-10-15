/* func_ov105_0229ec3c @ 0x0229ec3c, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *a, int b);
extern unsigned char *func_ov002_022080a0(void *a, unsigned char value);
extern int func_ov002_02207f60(void *a);
extern void func_ov105_0229db14(void *a);

void func_ov105_0229ec3c(void *obj)
{
    if (func_ov002_02207f48(obj, 0)) {
        func_ov002_022080a0(obj, 2);
        func_ov105_0229db14(obj);
    }
    *(int *) ((char *) obj + 0x9c) = func_ov002_02207f60(obj);
}
