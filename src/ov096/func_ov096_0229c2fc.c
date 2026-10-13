/* func_ov096_0229c2fc @ 0x0229c2fc, 0x12 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x94];
    unsigned int flag;
} Struct_ov096_0229c2fc;

int func_ov096_0229c2fc(Struct_ov096_0229c2fc *p, unsigned int mask)
{
    if (p->flag & mask) {
        return 1;
    }
    return 0;
}
