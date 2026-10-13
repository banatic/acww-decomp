/* func_02034ebc @ 0x02034ebc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x13];
    unsigned char flag;
    char pad_14[0x08];
} UnkStruct_02034ebc;

UnkStruct_02034ebc *func_02034ebc(UnkStruct_02034ebc *array, int count)
{
    UnkStruct_02034ebc *result = 0;
    int i = 0;
    while (i < count) {
        if (array[i].flag == 0) {
            result = &array[i];
            break;
        }
        i++;
    }
    return result;
}
