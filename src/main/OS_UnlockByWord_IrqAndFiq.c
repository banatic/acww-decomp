/* OS_UnlockByWord_IrqAndFiq @ 0x0203cd1c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OSi_DoUnlockByWord__main_0203cd2c(int object, unsigned short *item, int mode, int set);

int OS_UnlockByWord_IrqAndFiq(int object, unsigned short *item, int mode)
{
    return OSi_DoUnlockByWord__main_0203cd2c(object, item, mode, 1);
}
