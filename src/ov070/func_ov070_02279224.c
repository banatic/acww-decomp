/* func_ov070_02279224 @ 0x02279224, 0x14 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

int func_ov070_02279224(void *arg0)
{
    unsigned short val;
    val = *(unsigned short *) arg0;
    if (val == 0xfff1) {
        return 1;
    }
    return 0;
}
