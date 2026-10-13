/* func_0208ed40 @ 0x0208ed40, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);
extern int func_0208a160(void *);

void func_0208ed40(void *param)
{
    func_0208a0c8((char *) param + 0xc);
    if (func_0208a160((char *) param + 0xc) != 0) {
        *(int *) ((char *) param + 0x20) = 0;
    }
}
