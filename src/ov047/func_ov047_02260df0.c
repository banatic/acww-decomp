/* func_ov047_02260df0 @ 0x02260df0, 0x28 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070fa0(void *ptr);
extern int data_021f38f8;

void func_ov047_02260df0(void *self)
{
    if (func_02070fa0(&data_021f38f8) != 0) {
        *(int *) ((char *) self + 0xd0) = 0x2a;
    } else {
        *(int *) ((char *) self + 0xd0) = 0x2b;
    }
}
