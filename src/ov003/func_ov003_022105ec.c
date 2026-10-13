/* func_ov003_022105ec @ 0x022105ec, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209129c(int param);
extern void func_0200fa6c(int *dest, void *src);
extern unsigned char data_ov003_02260540;
extern int data_ov003_02260558[3];

void func_ov003_022105ec(void *arg)
{
    int field;
    int local[3];

    field = *(int *) ((char *) arg + 0x7d4);
    if (field != -1) {
        func_0209129c(field);
    }
    func_0200fa6c(local, arg);
    data_ov003_02260540 = 0;
    data_ov003_02260558[0] = local[0];
    data_ov003_02260558[1] = local[1];
    data_ov003_02260558[2] = local[2];
}
