/* func_02036754 @ 0x02036754, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Entry {
    unsigned char id;
    unsigned char pad_01;
    unsigned short val;
} data_020c9f58[], data_020c9fcc;

unsigned short func_02036754(unsigned char key)
{
    const struct Entry *end = &data_020c9fcc;
    unsigned short result = 0xffff;
    const struct Entry *p = data_020c9f58;
    while (p < end) {
        if (p->id == key) {
            result = p->val;
            break;
        }
        p++;
    }
    return result;
}
