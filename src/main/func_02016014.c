/* func_02016014 @ 0x02016014, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char unk_54;
} UnkStruct_02016014;

extern int func_02016024(UnkStruct_02016014 *self, int arg2, unsigned char byte);

int func_02016014(UnkStruct_02016014 *self, int arg2)
{
    return func_02016024(self, arg2, self->unk_54);
}
