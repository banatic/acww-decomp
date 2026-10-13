/* func_02098554 @ 0x02098554, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02099a38(void *);

void func_02098554(void *arg0)
{
    int i;
    void *p;

    for (i = 0; i < 3; i++) {
        p = (void *) ((unsigned int) arg0 + (unsigned int) i * 0x249c);
        func_02099a38(p);
    }
}
