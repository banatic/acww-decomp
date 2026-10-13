/* func_020ab354 @ 0x020ab354, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab51c(void *arg0);

void func_020ab354(void *arg0, void *arg1)
{
    func_020ab51c(arg1);
    *(void **) ((unsigned char *) arg0 + 0x20) = arg1;
}
