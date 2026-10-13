/* func_ov103_0229d99c @ 0x0229d99c, 0x84 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);
extern void func_0206e2ec(void *p, int a);

void func_ov103_0229d99c(void *self)
{
    *(int *) ((char *) self + 0x2b88) = 0;
    func_ov094_0229af40((char *) self + 0xcc, 2);
    func_ov094_0229bbd8((char *) self + 0xb2c, 2);
    func_ov094_0229a2b0((char *) self + 0xb54, 6);
    *(char *) ((char *) self + 0x2da2) = 0x15;
    func_ov002_02209e18((char *) self + 0x225c);
    *(char *) ((char *) self + 0x2da0) = 0;
    *(char *) ((char *) self + 0x2da4) = 0xb;
    func_ov002_02209984((char *) self + 0x22d8, 3, 1, 0);
    func_0206e2ec((char *) self + 0x27e8, 3);
}