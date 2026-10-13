/* func_02049384 @ 0x02049384, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    int x;
    int y;
};
struct UnkStruct_02049384 {
    unsigned int header;
    unsigned int count;
    struct Entry entries[64];
    unsigned short shorts[1];
};

void func_02049384(struct UnkStruct_02049384 *obj, unsigned short value, int a, int b)
{
    obj->shorts[obj->count] = value;
    obj->entries[obj->count].x = a;
    obj->entries[obj->count].y = b;
    obj->count++;
}
