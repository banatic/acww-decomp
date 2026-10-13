/* func_ov134_0229aa78 @ 0x0229aa78, 0x30 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov134_0229bf8c[];
extern int data_ov134_0229bfbc[];
extern int data_ov134_0229c004[];

struct UnkStruct_0229aa78 {
    char pad_00[0xA0];
    unsigned char type;
};

int func_ov134_0229aa78(struct UnkStruct_0229aa78 *self, int index)
{
    unsigned char t = self->type;
    if (t == 2) {
        return data_ov134_0229bf8c[index];
    } else if (t == 1) {
        return data_ov134_0229bfbc[index];
    } else {
        return data_ov134_0229c004[index];
    }
}
