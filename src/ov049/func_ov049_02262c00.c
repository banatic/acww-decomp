/* func_ov049_02262c00 @ 0x02262c00, 0x80 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(unsigned char *);
extern void func_0201c280(unsigned char *, unsigned char *);
extern void func_ov049_02262094(unsigned char *, unsigned char *);
extern void func_0202edfc(unsigned char *, int, int);
extern void func_0201c3f4(unsigned char *, int);
extern void func_0201af28(unsigned char *, int, int, int, int);
extern unsigned short data_020c80f8;

int func_ov049_02262c00(unsigned char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov049_02262094(self + 0x658, self);
    func_0202edfc(self, 0x119a, 0x2000);
    func_0201c3f4(self, 0xf00);
    *(unsigned short *) (self + 0x972) = data_020c80f8;
    func_0201af28(self + 0x350, 2, 0x333, 0xcc, 0x133);
    return 1;
}
