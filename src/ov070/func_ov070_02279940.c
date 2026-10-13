/* func_ov070_02279940 @ 0x02279940, 0x34 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(void *, int, int, int);

int func_ov070_02279940(void *arg0)
{
    volatile int local[7];

    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    local[3] = 0;
    local[4] = 0;
    local[5] = data_020c80f8;
    local[6] = 0;

    func_02019d0c((char *) arg0 + 0x564, 0, 1, 0);
    return 1;
}
