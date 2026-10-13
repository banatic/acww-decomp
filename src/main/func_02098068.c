/* func_02098068 @ 0x02098068, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066650(void *);

void func_02098068(void *param)
{
    int i;
    for (i = 0; i < 10; i++) {
        func_02066650((char *) param + (i << 8));
    }
    *(unsigned short *) ((char *) param + 0xa00) = 0;
}
