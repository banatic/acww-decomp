/* func_ov049_0226256c @ 0x0226256c, 0x54 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov049_0226048c(void *);
extern int func_ov049_02260500(void *);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov049_02262a94(void *, int);

int func_ov049_0226256c(void *self)
{
    if (func_ov049_0226048c(self)) {
        return 1;
    }
    if (func_ov049_02260500(self)) {
        return 1;
    }
    if (func_02019e00((char *) self + 0x564) == 0xa) {
        if (func_02019de8((char *) self + 0x564)) {
            *(unsigned short *) ((char *) self + 0x972) = 0x18;
            func_ov049_02262a94(self, 1);
        }
    }
    return 1;
}
