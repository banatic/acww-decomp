/* func_020ab758 @ 0x020ab758, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void strncpy(void *arg0, int arg1, int arg2);

void func_020ab758(void *arg0, int arg1)
{
    ((unsigned char *) arg0)[0x8a] = 0;
    strncpy((unsigned char *) arg0 + 0x71, arg1, 0x19);
}
