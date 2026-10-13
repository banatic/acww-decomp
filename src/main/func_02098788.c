/* func_02098788 @ 0x02098788, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02099a38(void *);

void func_02098788(void *arg0)
{
    int i;
    void *ptr;

    for (i = 0; i < 4; i++) {
        ptr = (void *) ((int) arg0 + i * 0x249c);
        func_02099a38(ptr);
    }
}
