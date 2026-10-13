/* func_020a7684 @ 0x020a7684, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7684(unsigned char *arg0, unsigned int *arg1, unsigned int *arg2, unsigned int *arg3);

void func_020a7684(unsigned char *arg0, unsigned int *arg1, unsigned int *arg2, unsigned int *arg3)
{
    unsigned char local_0;
    unsigned int local_1;
    unsigned int local_2;
    unsigned int local_3;

    local_0 = *arg0;
    local_1 = local_0 & 7;
    *arg1 = local_1;
    local_2 = (*arg0 >> 5) & 7;
    *arg2 = local_2;
    local_3 = (*arg0 >> 3) & 3;
    *arg3 = local_3;
}
