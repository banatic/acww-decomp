/* func_02038264 @ 0x02038264, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02038264(void *param);

void func_02038264(void *param)
{
    unsigned char *ptr;
    unsigned int *ptr2;
    unsigned int *ptr3;

    ptr2 = (unsigned int *) ((unsigned char *) param + 0xbc);
    *ptr2 = 2;
    ptr3 = (unsigned int *) ((unsigned char *) param + 0xc0);
    *ptr3 = 0x14;
    ptr = (unsigned char *) param + 0xc8;
    *ptr = 0;
}
