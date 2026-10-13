/* func_02050edc @ 0x02050edc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050edc(void *self);

int func_02050edc(void *self)
{
    int result;
    unsigned int field_48;
    unsigned int field_78;
    unsigned int field_4c;

    result = 0;
    field_48 = *(unsigned int *) ((char *) self + 0x48);
    field_78 = *(unsigned int *) ((char *) self + 0x78);
    if (field_78 >= field_48) {
        field_4c = *(unsigned int *) ((char *) self + 0x4c);
        if (field_78 < field_48 + field_4c) {
            result = 1;
        }
    }
    return result;
}
