/* func_02010ef4 @ 0x02010ef4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *ptr, int arg);
extern int func_020645e0(void *ptr);
extern int func_02056778(void *ptr);

void func_02010ef4(void *self)
{
    unsigned int field;

    field = *(unsigned int *) ((char *) self + 0x76c);
    if (field == 0x16f) {
        return;
    }
    if (field == 0) {
        if (func_02056f28((char *) self + 0x710, 0) == 0 || func_020645e0((char *) self + 0x768) != 0) {
            func_02056778((char *) self + 0x710);
        }
    } else {
        func_02056778((char *) self + 0x710);
        return;
    }
}
