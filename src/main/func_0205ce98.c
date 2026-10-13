/* func_0205ce98 @ 0x0205ce98, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    unsigned short arr[25];
} UnkStruct_0205ce98;

void func_0205ce98(UnkStruct_0205ce98 *p)
{
    int i;
    for (i = 0; i < 25; i++) {
        p->arr[i] = 0x144;
    }
}
