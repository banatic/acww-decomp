/* func_0208dbd8 @ 0x0208dbd8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern void func_0208d7b8(void *);
extern void func_0208dcf8(void *);

void func_0208dbd8(void *arg0)
{
    void *ptr = arg0;
    func_0208a0c8((char *) ptr + 0xc);
    if (func_0208a160((char *) ptr + 0xc) != 0) {
        func_0208d7b8(ptr);
        func_0208dcf8(ptr);
    }
}
