/* func_0208c3c0 @ 0x0208c3c0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d0a84[];
extern unsigned char data_020d0a85[];

void func_0208c3c0(void *arg0)
{
    int val;
    int val2;
    int *piVar3;
    int *piVar4;

    piVar3 = (int *) ((int) arg0 + 0xc4);
    val = *piVar3;
    val2 = (int) (char) data_020d0a84[val * 2];
    piVar4 = (int *) ((int) arg0 + 0xc8);
    *piVar4 = val2;
    piVar3 = (int *) ((int) arg0 + 0xc4);
    val = *piVar3;
    val2 = (int) (char) data_020d0a85[val * 2];
    *(int *) ((int) arg0 + 0xcc) = val2;
    return;
}
