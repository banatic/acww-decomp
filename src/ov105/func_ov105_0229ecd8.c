/* func_ov105_0229ecd8 @ 0x0229ecd8, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern void func_ov002_022080a0(void *p, int a);
extern int func_ov002_02207f60(void *p);
extern void func_ov105_0229da7c(void *p);

void func_ov105_0229ecd8(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov105_0229da7c(p);
    }
    *((int *) ((char *) p + 0x9c)) = func_ov002_02207f60(p);
}
