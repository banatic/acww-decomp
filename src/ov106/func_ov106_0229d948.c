/* func_ov106_0229d948 @ 0x0229d948, 0x2e bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int val);
extern int func_ov002_02207f60(void *p);
extern void func_ov106_0229d73c(void *p);

void func_ov106_0229d948(void *obj)
{
    int a;
    int b;
    char *p;

    a = func_ov002_02207f48(obj, -1);
    b = func_ov002_02207f60(obj);
    p = (char *) obj;
    p += 0xA0;
    *(int *) p = b;
    if (a != 0) {
        func_ov106_0229d73c(obj);
    }
}
