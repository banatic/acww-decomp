/* func_020962dc @ 0x020962dc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void *);
extern void func_020012dc(void);

void *func_020962dc(void *p)
{
    func_02138c48((char *) p + 0x34, 4, 12, func_020012dc);
    return p;
}
