/* func_ov086_02279020 @ 0x02279020, 0x68 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279020;

extern int func_0202ec58(void);
extern void func_ov086_02278f80(struct UnkStruct_02279020 *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);

int func_ov086_02279020(struct UnkStruct_02279020 *self)
{
    if (func_0202ec58() == 0) {
        return 0;
    }

    func_ov086_02278f80(self, 0);

    func_02016764((char *) self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);

    func_02054188((char *) self + 0xec, 0xc, 0xe);

    *(unsigned int *) ((char *) self + 0x4e8) |= 2;

    return 1;
}
