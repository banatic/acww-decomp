/* func_ov071_02279b2c @ 0x02279b2c, 0x40 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02279b2c {
    unsigned char pad_00[0x734];
    int unk_734;
};

extern int func_0201c390(struct UnkStruct_02279b2c *obj, int value);
extern int func_0201c2b0(struct UnkStruct_02279b2c *obj, int value);
extern signed short data_ov071_0227a340[];

int func_ov071_02279b2c(struct UnkStruct_02279b2c *obj, int param2)
{
    int i = 0;
    if (func_0201c390(obj, obj->unk_734) > param2) {
        goto out;
    }
    {
        int r = func_0201c2b0(obj, obj->unk_734);
        int t = data_ov071_0227a340[i];
        if (r < -t) {
            goto out;
        }
        if (r > t) {
            goto out;
        }
    }
    i = 1;
out:
    return i;
}
