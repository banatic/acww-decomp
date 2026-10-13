/* func_ov088_02279574 @ 0x02279574, 0x3a bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(int *dest, void *src, int arg, short val);
extern int func_0201ae8c(int *buf);

struct UnkStruct_02279574 {
    char pad_00[0x5c];
    char unk_5C[0x38];
    short unk_94;
};

int func_ov088_02279574(struct UnkStruct_02279574 *a, int *out, int arg)
{
    int buf[4];
    int result = 0;

    func_0201af58(buf, a->unk_5C, arg, a->unk_94);
    if (func_0201ae8c(buf) == 1) {
        // nothing
    } else {
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
        result = 1;
    }
    return result;
}
