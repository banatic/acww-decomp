/* func_02080078 @ 0x02080078, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

func_02080078(unsigned char *param1)
{
    unsigned short local_4;
    unsigned char *arg0;
    int val;
    int val2;
    unsigned char *puVar3;

    arg0 = param1;
    val = func_0204e414();
    if (val != 0) {
        if (func_020800dc(arg0) != 0) {
            puVar3 = (unsigned char *) func_020800d0(arg0);
            local_4 = 0x500a;
            func_0204e3f4(val, *puVar3, puVar3[1], &local_4);
        }
    }
    return;
}
