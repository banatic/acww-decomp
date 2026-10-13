/* func_ov068_02273510 @ 0x02273510, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov068_022787fc;
extern void func_ov004_0222c598(void *p);
extern void func_ov004_0222c5b4(void *a, void *b);
extern void func_02004644(void *addr, int val);

int func_ov068_02273510(void *p)
{
    data_ov068_022787fc = 0;
    func_ov004_0222c598(p);
    func_ov004_0222c5b4((char *) p + 0x388, (char *) p + 0x42c);
    func_ov004_0222c5b4((char *) p + 0x4ec, (char *) p + 0x590);
    func_02004644((char *) 0x884, 1);
    func_02004644((char *) 0x885, 1);
    return 1;
}
