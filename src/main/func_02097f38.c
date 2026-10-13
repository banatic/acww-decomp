/* func_02097f38 @ 0x02097f38, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066650(void *);

void func_02097f38(void *param)
{
    int i;
    void *p;

    for (i = 0; i < 50; i++) {
        p = (void *) ((unsigned int) param + (i << 8));
        func_02066650(p);
    }
}
