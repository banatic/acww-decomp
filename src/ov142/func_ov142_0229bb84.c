/* func_ov142_0229bb84 @ 0x0229bb84, 0x40 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int a);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern void func_ov002_0220ab84(void *p, int a);
extern int func_ov002_02207f60(void *p);

void func_ov142_0229bb84(void *p)
{
    if (func_ov002_02207f3c(p, -1) != 0) {
        func_ov002_02208090(p, 7);
        func_ov002_02207eb4(p, 0, 0);
        func_ov002_0220ab84((char *) p + 0x194, 0x65);
    }
    *(int *) ((char *) p + 0x98) = func_ov002_02207f60(p);
}
