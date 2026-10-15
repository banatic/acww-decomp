/* func_020837a8 @ 0x020837a8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d4e8(void *);

int func_020837a8(void *arg0)
{
    int result = 0;
    func_0205d4e8((char *) arg0 + 1);
    *(unsigned char *) arg0 = result;
    return result;
}
