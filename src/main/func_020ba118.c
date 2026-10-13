/* func_020ba118 @ 0x020ba118, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020ba118(void *arg0);

unsigned char func_020ba118(void *arg0)
{
    unsigned int temp;
    unsigned char result;

    temp = *(unsigned int *) ((unsigned char *) arg0 + 8);
    temp >>= 11;
    result = (unsigned char) (temp & 0xFF);
    result = (unsigned char) (result + 1);
    return result;
}
