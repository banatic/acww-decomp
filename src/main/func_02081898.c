/* func_02081898 @ 0x02081898, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7C];
    unsigned short unk_7C;
} UnkStruct_02081898;

int func_02081898(UnkStruct_02081898 *p)
{
    if (((unsigned) p->unk_7C << 17) >> 31) {
        return 1;
    } else {
        return 0;
    }
}
