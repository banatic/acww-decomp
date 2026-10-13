/* func_0206e904 @ 0x0206e904, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020041a4(void *);
extern void func_0206ea28(void);
extern unsigned int data_020df2a0;

extern unsigned char data_021cfbcc[];

void func_0206e904(void)
{
    unsigned int *p;
    unsigned int val;

    func_020041a4((void *) data_021cfbcc);
    val = 0;
    val = ~val;
    p = &data_020df2a0;
    *p = val;
    func_0206ea28();
}
