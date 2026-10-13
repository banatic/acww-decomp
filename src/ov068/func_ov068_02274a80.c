/* func_ov068_02274a80 @ 0x02274a80, 0x14 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov068_02277d10[];

int func_ov068_02274a80(void *ptr)
{
    return data_ov068_02277d10[*(int *) ((char *) ptr + 0x730)];
}
