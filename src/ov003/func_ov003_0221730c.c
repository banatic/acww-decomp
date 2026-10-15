/* func_ov003_0221730c @ 0x0221730c, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02008258(void *, unsigned int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_02073908(void *, unsigned int);
extern int func_ov003_0220d268(void *);
extern void *data_020ccf94;

void func_ov003_0221730c(void *self)
{
    if (func_02056f94((void *) ((char *) self + 0x2d0))) {
        *(unsigned int *) ((char *) self + 0x7fc) = func_02008258(self, *(unsigned int *) ((char *) self + 0x7f0));
        func_0200d4e8(self, 3, 1, -1);
    }
    if (((*(unsigned int *) ((char *) self + 0x2d8) << 4) >> 16) >= 14) {
        if (func_02073908(data_020ccf94, *(unsigned int *) ((char *) self + 0x800)) != 0) {
            func_ov003_0220d268(self);
        }
    }
}
