/* func_0203f444 @ 0x0203f444, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OSiHeapInfo[];

int func_0203f444(int p0)
{
    *(int *) ((char *) OSiHeapInfo + ((p0 << 2))) = 0;
    return (int) OSiHeapInfo;
}
