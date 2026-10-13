/* func_02082ba0 @ 0x02082ba0, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02082b80(void *dst, void *src, int size);
extern void func_020828e0(void *dst, void *src, int size);

void func_02082ba0(void *arg0)
{
    void *p = arg0;
    func_02082b80(p, p, 8);
    func_020828e0(p, (char *) p + 0x40, 4);
}
