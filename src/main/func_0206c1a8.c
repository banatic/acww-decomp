/* func_0206c1a8 @ 0x0206c1a8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x410];
    unsigned int count;
    int array[3];
} UnkStruct_0206c1a8;

void func_0206c1a8(UnkStruct_0206c1a8 *obj, int value)
{
    unsigned int i = obj->count;
    while (i < 3) {
        obj->array[i] = value;
        i++;
    }
}
