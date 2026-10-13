/* func_0203fda0 @ 0x0203fda0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short id;
    char data[10];
} UnkStruct_0203fda0;

UnkStruct_0203fda0 *func_0203fda0(unsigned short key, UnkStruct_0203fda0 *arr)
{
    UnkStruct_0203fda0 *result = 0;
    int i = 0;
    while (i < 7) {
        if (arr->id == key) {
            result = arr;
            break;
        }
        arr++;
        i++;
    }
    return result;
}
