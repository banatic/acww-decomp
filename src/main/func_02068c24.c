/* func_02068c24 @ 0x02068c24, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fdc0(void *ptr, int);

void func_02068c24(void *ptr, int argument1)
{
    func_0208fdc0((char *) ptr + 0x50, (int) argument1);
    *(unsigned int *) ((char *) ptr + 0x7c) = 0xFFFFFFFF;
}
