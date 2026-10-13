/* func_ov068_022751c4 @ 0x022751c4, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c87c(void *p);
extern void func_02055210(void *p);
extern void func_ov004_0222c548(void *p);
extern void func_ov004_0222c398(void *p);
extern int data_ov068_02277f3c;
extern int data_ov068_022788b0;

void *func_ov068_022751c4(void *p)
{
    func_ov004_0222c87c(p);
    *(int **) p = &data_ov068_02277f3c;
    func_02055210((char *) p + 0x29c);
    func_ov004_0222c548((char *) p + 0x354);
    func_ov004_0222c398((char *) p + 0x3f8);
    data_ov068_022788b0 = 0;
    return p;
}
