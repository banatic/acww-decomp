/* UTi_PutString @ 0x020edacc, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int (*OS_PutString)(int);

int UTi_PutString(int arg)
{
    return OS_PutString(arg);
}
