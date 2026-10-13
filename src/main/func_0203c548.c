/* func_0203c548 @ 0x0203c548, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203c548(void *self);

int func_0203c548(void *self)
{
    unsigned int offset = 0x14c;
    int value1 = *(int *) ((char *) self + offset);
    int value2 = *(int *) ((char *) self + 0x80);
    return value1 + value2;
}
