/* func_ov045_02261034 @ 0x02261034, 0x5c bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov045_02260c94(void *, void *);
extern void func_0201c3f4(void *, int);
extern void func_0203edf4(void *, int);

int func_ov045_02261034(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x68c);
    func_ov045_02260c94((char *) self + 0x68c, self);
    func_0201c3f4(self, 0x100);
    func_0203edf4(self, 0x5000);
    *(int *) ((char *) self + 0x654) = -1;
    *(unsigned char *) ((char *) self + 0x758) = 0;
    return 1;
}
