/* func_020bf26c @ 0x020bf26c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf2a0(void *, void *);
extern void func_020be5d0(void *, int, void *, void *);

extern unsigned char data_021fbb14[];

void func_020bf26c(void *arg0, void *arg1)
{
    int local[4];
    func_020bf2a0(arg0, local);
    func_020be5d0((void *) data_021fbb14, 0, arg1, local);
}
