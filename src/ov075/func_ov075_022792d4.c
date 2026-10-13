/* func_ov075_022792d4 @ 0x022792d4, 0x38 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_ov075_0227930c(void *self, int *data, void *p);

int func_ov075_022792d4(void *self)
{
    int local[3];
    void *p = (char *) self + 0x5c;
    int result = 0;
    if (data_021c67a4) {
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        result = func_ov075_0227930c(self, local, p);
    }
    return result;
}
