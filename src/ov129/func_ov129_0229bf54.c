/* func_ov129_0229bf54 @ 0x0229bf54, 0x34 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
} UnkStruct_0229bf54;

extern void func_ov129_0229be04(UnkStruct_0229bf54 *s, unsigned char val);

void func_ov129_0229bf54(UnkStruct_0229bf54 *s)
{
    unsigned char flag = s->b1;
    switch (flag) {
        case 0:
            break;
        case 1:
            func_ov129_0229be04(s, s->b2);
            break;
        case 2:
            func_ov129_0229be04(s, s->b3);
            break;
    }
}
