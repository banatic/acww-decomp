/* func_02060934 @ 0x02060934, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02060704(void *ptr);
extern void func_0205c3c8(void);

extern unsigned char data_021cad80[];

void func_02060934(void)
{
    void *ptr;

    ptr = (void *) data_021cad80;
    func_02060704(ptr);
    func_0205c3c8();
}
