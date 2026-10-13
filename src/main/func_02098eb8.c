/* func_02098eb8 @ 0x02098eb8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02098f48(int, int);

int func_02098eb8(int id)
{
    unsigned short *list;
    int i;
    list = func_02098f48(id, 0);
    for (i = 0; i < 15; i++) {
        if (list[i] == 0xfff1) {
            return i;
        }
    }
    return -1;
}
