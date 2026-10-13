/* func_ov120_0229bdac @ 0x0229bdac, 0x54 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov120_0229a7a8(void *self);
extern void func_ov002_02207f04(void *self, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int a);
extern void *func_ov002_02207f60(void *self);

void func_ov120_0229bdac(void *self)
{
    func_ov120_0229a7a8(self);
    func_ov002_02207f04(self, 10, 0, 0, 0x30);
    func_ov002_02207e80(self, 4, 0, 0);
    func_ov002_02207e80(self, 6, 0, 0x50 - *(unsigned short *) ((char *) self + 0x98));
    func_ov002_02208090(self, 6);
    *(void **) ((char *) self + 0x94) = func_ov002_02207f60(self);
}
