/* func_ov068_02267b3c @ 0x02267b3c, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e0a8(void *, int);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, unsigned short);
extern unsigned short data_020c80f8;

typedef struct {
    char pad_00[0x1c];
    unsigned char unk_1C;
    int unk_20;
} UnkStruct_02267b3c;

typedef struct {
    char pad_00[0x564];
    char unk_564;
} UnkStruct_02267b3c_2;

void func_ov068_02267b3c(UnkStruct_02267b3c *out, UnkStruct_02267b3c_2 *in)
{
    func_0203e0a8(in, 0);
    if (func_02019e00(&in->unk_564) == 3) {
        if (func_02019de8(&in->unk_564) != 0) {
            func_02019c6c(&in->unk_564, 1, data_020c80f8);
            out->unk_20 = 0x28;
            out->unk_1C = 2;
        }
    }
}
