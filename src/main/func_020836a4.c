/* func_020836a4 @ 0x020836a4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020836a4 {
    int pad_00;
    unsigned int count;
    unsigned short array[1];
};

unsigned short *func_020836a4(struct UnkStruct_020836a4 *s, unsigned int index)
{
    unsigned short *result = 0;
    if (index < s->count) {
        result = &s->array[index];
    }
    return result;
}
