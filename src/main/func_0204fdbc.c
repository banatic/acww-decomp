/* func_0204fdbc @ 0x0204fdbc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *data_021c8184;
extern int data_020dcd78;

void func_0204fdbc(int param)
{
    if (data_021c8184 == 0) {
        return;
    }
    if (param < 0) {
        return;
    }
    if (param >= data_020dcd78) {
        return;
    }
    *(int *) (data_021c8184 + param * 0x16c + 0x94) = 4;
}
