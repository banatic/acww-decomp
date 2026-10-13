/* func_02090710 @ 0x02090710, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090664(void *ptr);
extern void func_02090418(void *ptr);

void func_02090710(void *arg)
{
    void *p;
    int i;
    int j;

    p = (void *) ((char *) arg + 0x524);
    func_02090664(p);

    for (i = 0; i < 4; i++) {
        j = i * 0x148;
        func_02090418((void *) ((char *) arg + 4 + j));
    }
}
