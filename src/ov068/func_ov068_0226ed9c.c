/* func_ov068_0226ed9c @ 0x0226ed9c, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226ed9c {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0xa8 - 0x68];
    int unk_A8;
    char pad_AC[0x26c - 0xac];
    int unk_26C;
    int unk_270;
    char pad_274[0x314 - 0x274];
    int unk_314;
    int unk_318;
    char pad_31C[0x380 - 0x31c];
    int unk_380;
    char pad_384[0x399 - 0x384];
    unsigned char unk_399;
};

extern void func_ov003_0221a35c(struct UnkStruct_0226ed9c *obj, int val);

void func_ov068_0226ed9c(struct UnkStruct_0226ed9c *obj)
{
    unsigned char c;

    obj->unk_270 = obj->unk_26C;
    obj->unk_5C += obj->unk_314;
    obj->unk_64 += obj->unk_318;
    obj->unk_60 += obj->unk_A8;
    if (obj->unk_60 > obj->unk_380) {
        obj->unk_60 = obj->unk_380;
    }
    c = obj->unk_399;
    obj->unk_399 = c + 1;
    if (c >= 16) {
        obj->unk_60 = obj->unk_380;
        func_ov003_0221a35c(obj, 11);
    }
}
