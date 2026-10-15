/* func_ov004_02227764 @ 0x02227764, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(int a, int b, int c, int d);
extern int func_02073908(void *argument0, int argument1);
extern void *data_020ccf94;

void func_ov004_02227764(char *self, void *message, int previous)
{
    // DECLS
    int v3;
    // ENDDECLS
    v3 = func_02073908((void *) (*(int *) ((char *) &data_020ccf94)), (int) (*(int *) (self + 0x800)));
    if (v3 == 0x0) {
        func_020109fc((int) (self), (int) (0x0), (int) (0x3), (int) (0x3));
    }
    return;
}
