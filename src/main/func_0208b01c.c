/* func_0208b01c @ 0x0208b01c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208affc(void *);
extern void *func_020edf70(unsigned int);

void func_0208b01c(void)
{
    unsigned int r0;
    void *ptr;

    r0 = (unsigned int) func_020edf70(0x50);
    if (r0 == 0) {
        return;
    }
    func_0208affc((void *) r0);
}
