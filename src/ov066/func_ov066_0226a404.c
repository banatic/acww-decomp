/* func_ov066_0226a404 @ 0x0226a404, 0x14 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern void OS_CancelAlarms(unsigned int);

void func_ov066_0226a404(const unsigned char *p)
{
    OS_CancelAlarms(*p + 0x80);
}
