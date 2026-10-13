/* func_020668d8 @ 0x020668d8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066934(void *self);
extern void func_02067e84(void *ptr);
extern void func_02068b64(void *ptr);

struct UnkStruct_020668d8;
struct UnkStruct_020668d8_2 {
    unsigned char pad[0x40];
    struct UnkStruct_020668d8 *unk_40;
};

struct UnkStruct_020668d8 {
    int unk_00;
    int unk_04;
    unsigned char pad[0x1a24];
    unsigned char unk_1A2C;
};

void func_020668d8(struct UnkStruct_020668d8_2 *self)
{
    int type;
    int flag;

    type = self->unk_40->unk_04;
    flag = (type == 5);
    func_02066934(self);
    if (type != 0 && !flag) {
        func_02067e84(self->unk_40);
        func_02068b64(&self->unk_40->unk_1A2C);
    }
}
