/* func_0208bccc @ 0x0208bccc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0208bccc(void *arg0)
{
    extern void func_0208a1f0(void *, void *);
    extern void func_0208a1ec(void *, int);
    extern void func_0208a144(void *);
    extern unsigned char data_020d5c4c[];

    *(int *) ((char *) arg0 + 0x20) = 4;
    func_0208a1f0((char *) arg0 + 0xc, data_020d5c4c);
    func_0208a1ec((char *) arg0 + 0xc, 1);
    func_0208a144((char *) arg0 + 0xc);
}
