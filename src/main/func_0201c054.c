/* func_0201c054 @ 0x0201c054, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02085174(void *a, int b, int c);
extern int func_02073dd4(int g, int field);
extern int data_020ccf94;
extern int func_0201c0e0(void *self);
extern unsigned char *func_0201c444(void *self);
extern void func_020771cc(void *a, void *buf, int c, int d);

void func_0201c054(void *selfv, int p1, int p2, int p3)
{
    unsigned char *self = (unsigned char *) selfv;
    unsigned char *rec;

    func_02085174(self + 0xea, p2, p3);

    if (func_02073dd4(data_020ccf94, *(int *) ((unsigned char *) data_020ccf94 + 0x64)) != 0) {
        if (func_0201c0e0(self) != 0) {
            int type = (*(unsigned short *) (self + 0xea) & 0xf000) >> 12;
            if (type == 0xe) {
                rec = func_0201c444(self);
                func_020771cc(rec + 0xc, &p1, 0, 0);
            } else if (type == 0xd) {
                rec = func_0201c444(self);
                func_020771cc(rec + 0x20, &p1, 0, 0);
            }
        }
    }
}
