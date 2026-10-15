/* func_020367cc @ 0x020367cc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020367cc {
    unsigned char pad_00[0xF];
    unsigned char flag;
};

extern void func_0203668c(struct UnkStruct_020367cc *);
extern void func_02036584(struct UnkStruct_020367cc *);

void func_020367cc(struct UnkStruct_020367cc *obj)
{
    obj->flag = 1;
    func_0203668c(obj);
    func_02036584(obj);
}
