/* func_02001910 @ 0x02001910, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *OS_GetDTCMAddress(void);
extern int OSi_MainExArenaEnabled;

int func_02001910(void *ptr, unsigned int len)
{
    char *p = (char *) ptr;
    char *end = p + len;
    char *A = (char *) OS_GetDTCMAddress();
    char *B = A + 0x4000;
    unsigned int C = OSi_MainExArenaEnabled ? 0x027e0000 : 0x023ff000;
    if ((unsigned int) p < 0x02000000) {
        goto L1;
    }
    if ((unsigned int) end <= C) {
        goto success;
    }
L1:
    if (A > p) {
        goto fail;
    }
    if (end > B) {
        goto fail;
    }
success:
    return 1;
fail:
    return 0;
}
