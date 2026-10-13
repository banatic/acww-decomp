/* func_ov118_0229a450 @ 0x0229a450, 0xe bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    unsigned short unk_9C;
} UnkStruct_0229a450;

void func_ov118_0229a450(UnkStruct_0229a450 *obj, unsigned short mask)
{
    obj->unk_9C |= mask;
}
