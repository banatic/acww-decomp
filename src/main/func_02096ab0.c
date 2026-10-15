/* func_02096ab0 @ 0x02096ab0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096a90(void *);
extern void *func_020edf70(unsigned int);

void func_02096ab0(void)
{
    unsigned int sp;
    void *result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_02096a90(result);
}
