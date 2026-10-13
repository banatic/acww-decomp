/* func_0201ca24 @ 0x0201ca24, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct GlobalData {
    unsigned int unk_00;
    unsigned int unk_04;
};

struct Object {
    unsigned char pad_00[0x48];
    unsigned char flag;
    struct GlobalData data;
};

extern struct GlobalData data_020d8f80;

int func_0201ca24(struct Object *obj)
{
    obj->flag = 0;
    obj->data = data_020d8f80;
    return 1;
}
