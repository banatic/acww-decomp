/* func_0204a370 @ 0x0204a370, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204a848(void *ptr, int a, int i, int j);

void func_0204a370(void *base, int a, int i, int j)
{
    char *ptr = (char *) base + 0x44 + i * 144 + j * 36;
    i++;
    j++;
    func_0204a848(ptr, a, i, j);
}
