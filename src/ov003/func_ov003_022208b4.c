/* func_ov003_022208b4 @ 0x022208b4, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_02220890(void *argument0);
extern void *func_020edf70(unsigned int size);

void func_ov003_022208b4(void)
{
    void *p;

    p = func_020edf70(0x50);
    if (p != 0) {
        func_ov003_02220890(p);
    }
}
