/* func_02091278 @ 0x02091278, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020913f0(void *a, void *b, void *c, void *d, void *e);

extern unsigned char data_021d52d8[];

void func_02091278(void *a, void *b, void *c, void *d)
{
    void *sp[2];
    sp[0] = d;
    func_020913f0((void *) data_021d52d8, a, b, c, sp[0]);
}
