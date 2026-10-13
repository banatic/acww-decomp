/* func_0205cf6c @ 0x0205cf6c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205cd60(void *);
extern void func_0205c7f8(void);

extern unsigned char data_021c9b58[];

void func_0205cf6c(void)
{
    void *ptr;
    ptr = (void *) data_021c9b58;
    func_0205cd60(ptr);
    func_0205c7f8();
}
