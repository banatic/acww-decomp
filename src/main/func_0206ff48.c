/* func_0206ff48 @ 0x0206ff48, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021cfcb4[];

int func_0206ff48(int param)
{
    int ret = 1;
    if (!((1 << (param & 31)) & data_021cfcb4[param >> 5])) {
        ret = 0;
    }
    return ret;
}
