/* func_02083aa8 @ 0x02083aa8, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int count;
    unsigned int data[1];
} MyArray;

unsigned int *func_02083aa8(MyArray *self, unsigned int index)
{
    unsigned int *ret = 0;
    if (index < self->count) {
        ret = &self->data[index];
    }
    return ret;
}
