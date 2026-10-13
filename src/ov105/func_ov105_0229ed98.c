/* func_ov105_0229ed98 @ 0x0229ed98, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

void func_ov105_0229ed98(void *self)
{
    int *p1;
    int *p2;
    func_ov002_02207e80(self, 6, 0, ~0xf);
    p1 = (int *) ((char *) self + 0x98);
    *p1 = func_ov002_02207f60(self);
    p2 = (int *) ((char *) self + 0x9c);
    *p2 = func_ov002_02207f60(self);
}
