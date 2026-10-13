/* func_ov068_0226d770 @ 0x0226d770, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} SrcData;

class UnkStruct_0226d770 {
  public:
    char pad_00[0x5c];
    SrcData src;
    char pad_68[0x478 - 0x68];
    SrcData dst[3];
    char pad_49C[0x8b0 - 0x49c];
    int (UnkStruct_0226d770::*pmf)();
};

extern "C" int func_ov068_0226d770(UnkStruct_0226d770 *obj)
{
    int result = 1;
    if (obj->pmf != 0) {
        result = (obj->*obj->pmf)();
    } else {
        SrcData *src = &obj->src;
        obj->dst[0].a = obj->src.a;
        obj->dst[0].b = src->b;
        obj->dst[0].c = src->c;
        obj->dst[1].a = obj->src.a;
        obj->dst[1].b = src->b;
        obj->dst[1].c = src->c;
        obj->dst[2].a = obj->src.a;
        obj->dst[2].b = src->b;
        obj->dst[2].c = src->c;
    }
    return result;
}
