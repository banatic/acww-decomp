/* func_020832e4 @ 0x020832e4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020832e4 {
    int unk_00;
    unsigned int size;
    unsigned short data[1];
};

unsigned short *func_020832e4(struct UnkStruct_020832e4 *self, unsigned int index)
{
    unsigned short *result = 0;
    if (index < self->size) {
        result = &self->data[index];
    }
    return result;
}
