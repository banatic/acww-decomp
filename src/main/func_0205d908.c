/* func_0205d908 @ 0x0205d908, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0205d908(void *param0, int param1, int param2);

unsigned short func_0205d908(void *param0, int param1, int param2)
{
    unsigned short *ptr;
    int offset;

    offset = param2 * 0x12;
    ptr = (unsigned short *) ((char *) param0 + offset);
    ptr += param1;
    return ptr[0x12];
}
