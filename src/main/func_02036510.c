/* func_02036510 @ 0x02036510, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *dst, int a, int b, void *p);

extern void func_02036570(void);

void *func_02036510(void *ptr)
{
    func_02138c48((void *) ((unsigned char *) ptr + 4), 8, 16, (void *) func_02036570);
    return ptr;
}
