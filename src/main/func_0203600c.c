/* func_0203600c @ 0x0203600c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[5];
    char unk_05;
    char pad_06[10];
} UnkStruct_0203600c;

void func_0203600c(UnkStruct_0203600c *arr)
{
    int i = 0;
    char v = (char) i;
    do {
        arr[i].unk_05 = v;
        i++;
    } while (i < 8);
}
