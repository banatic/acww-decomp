/* func_02083820 @ 0x02083820, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} UnkStruct_02083820;

typedef struct {
    unsigned int unk_00;
    unsigned int count;
    UnkStruct_02083820 array[1];
} Header;

UnkStruct_02083820 *func_02083820(Header *header, unsigned int index)
{
    UnkStruct_02083820 *result = 0;
    if (index < header->count) {
        result = &header->array[index];
    }
    return result;
}
