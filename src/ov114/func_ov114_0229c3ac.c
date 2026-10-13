/* func_ov114_0229c3ac @ 0x0229c3ac, 0x64 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c3ac {
    unsigned char pad_00[0x128c];
    int word_field;
    unsigned char pad_1290[0x2c];
    unsigned char byte_field;
};

extern int func_ov114_0229c690(struct UnkStruct_0229c3ac *p);

void func_ov114_0229c3ac(struct UnkStruct_0229c3ac *p)
{
    int r;
    if (p->byte_field < 0x0d) {
        return;
    }
    r = func_ov114_0229c690(p);
    if (r < 0x20) {
        p->byte_field = (unsigned char) (p->word_field + 0x0d);
        r = func_ov114_0229c690(p);
        if (r < 0x20) {
            p->byte_field = p->byte_field + 1;
        }
    } else if (r > 0xe0) {
        p->byte_field = (unsigned char) (p->word_field + 0x14);
        r = func_ov114_0229c690(p);
        if (r > 0xe0) {
            p->byte_field = p->byte_field - 1;
        }
    }
}
