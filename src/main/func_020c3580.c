/* func_020c3580 @ 0x020c3580, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(void *a, int b, int c, int d, void *e, int f, void *g, int h);
extern void func_020c3690(void *a, int b);
extern int *data_020c814c;

extern unsigned char data_021fbee8[];

void func_020c3580(char *p)
{
    func_0201ad18(p + 0x3b0, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_020c3690(p, 0);
}
