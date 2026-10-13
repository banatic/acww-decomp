/* func_020aba3c @ 0x020aba3c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern int RtcSendPxiCommand(int cmd);
extern void func_020aba24(void *ptr);

void func_020aba3c(void *ptr)
{
    if (func_0208e484((char *) ptr + 0x20)) {
        RtcSendPxiCommand(0x27);
        func_020aba24(ptr);
    }
}
