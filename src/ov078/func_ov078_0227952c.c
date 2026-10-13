/* func_ov078_0227952c @ 0x0227952c, 0x38 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c67a4;
extern int data_021c67d0[3];
extern int func_ov078_02279564(void *self, void *data, void *offset, int second);

int func_ov078_0227952c(void *self)
{
    void *p;
    int result;
    int local[3];

    p = (char *) self + 0x5c;
    result = 0;
    if (data_021c67a4 != 0) {
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        result = func_ov078_02279564(self, local, p, local[1]);
    }
    return result;
}
