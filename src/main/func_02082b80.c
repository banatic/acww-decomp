/* func_02082b80 @ 0x02082b80, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned short unk_04;
} UnkStruct_02082b80;

void func_02082b80(int unused, UnkStruct_02082b80 *ptr, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        ptr->unk_00 = 0;
        ptr->unk_04 = 0xfff1;
        ptr++;
    }
}
