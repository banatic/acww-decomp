/* func_020b1b48 @ 0x020b1b48, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void OS_SetProtectionRegion2(unsigned int);
extern void OS_SetArenaHi(int, unsigned int);

void func_020b1b48(void)
{
    OS_SetProtectionRegion2(0x023ff017);
    OS_SetArenaHi(0, 0x023ff000);
}
