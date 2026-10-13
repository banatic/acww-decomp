/* func_0208aa48 @ 0x0208aa48, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051a78(void *ptr);

void func_0208aa48(void *arg)
{
    void *p = arg;
    func_02051a78((char *) p + 0x60);
    *(unsigned int *) ((char *) p + 0xc8) = 1;
}
