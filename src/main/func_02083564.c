/* func_02083564 @ 0x02083564, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[8];
} UnkStruct_02083564;

typedef struct {
    int unk_00;
    unsigned int count;
    UnkStruct_02083564 array[1];
} Container;

void *func_02083564(Container *c, unsigned int index)
{
    void *result = 0;
    if (index < c->count) {
        result = &c->array[index];
    }
    return result;
}
