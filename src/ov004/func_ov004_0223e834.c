/* func_ov004_0223e834 @ 0x0223e834, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_02073d90(void *);
extern int func_ov004_0223e5f0(void *receiver);
extern int func_ov004_0223e618(void *);
extern void *data_020ccf94;
extern void *data_ov004_02259a10;

int func_ov004_0223e834(void *self)
{
    if (func_020b67d4() == 0 || func_02073d90(data_020ccf94) != 0) {
        return 1;
    }
    data_ov004_02259a10 = self;
    if (func_ov004_0223e5f0(self) == 0) {
        return 1;
    }
    func_ov004_0223e618(self);
    return 1;
}
