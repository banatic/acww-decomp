/* func_0208f708 @ 0x0208f708, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208f6e8(void *);
extern int func_020edf70(int);

void func_0208f708(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result != 0) {
        func_0208f6e8((void *) result);
    }
}
