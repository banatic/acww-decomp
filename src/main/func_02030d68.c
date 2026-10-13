/* func_02030d68 @ 0x02030d68, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    unsigned char *data;
} UnkStruct_02030d68;

extern UnkStruct_02030d68 *func_01ffcb5c(int, int);

void func_02030d68(int a, int b, int c)
{
    UnkStruct_02030d68 *ret = func_01ffcb5c(a >> 4, b >> 4);
    if (ret) {
        int idx = (a & 0xf) + ((b & 0xf) << 4);
        unsigned char *p = ret->data + (idx >> 1);
        if (idx & 1) {
            *p &= ~0xf0;
            *p |= (c << 4);
        } else {
            *p &= ~0x0f;
            *p |= c;
        }
    }
}
