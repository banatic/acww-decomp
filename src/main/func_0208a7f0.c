/* func_0208a7f0 @ 0x0208a7f0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1cc(void *ptr);

int func_0208a7f0(void *ptr)
{
    int result;
    result = func_0208a1cc((char *) ptr + 0xc);
    return (result << 3) + 0x18;
}
