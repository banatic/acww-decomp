/* func_ov004_0223ac34 @ 0x0223ac34, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057538(void *);
extern int func_02056f28(void *, int);
typedef struct {
    unsigned char pad_00[8];
    long unk_08, unk_0C;
    unsigned char unk_10[0x96];
} UnkStruct_0223ac34;
void func_ov004_0223ac34(UnkStruct_0223ac34 *self)
{
    int v;
    if (self->unk_08 != 0 && self->unk_0C != 0) {
        func_02057538(self->unk_10);
        if (func_02056f28(self->unk_10, 0) != 0) {
            v = *(unsigned short *) ((char *) self + 0xa6) + 1;
            if (v > 0xffff) {
                *(unsigned short *) ((char *) self + 0xa6) = 0xffff;
            } else {
                *(unsigned short *) ((char *) self + 0xa6) = (unsigned short) v;
            }
        }
    }
}
