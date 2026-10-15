/* func_ov068_02268c30 @ 0x02268c30, 0x54 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(const unsigned char *p);
extern int func_02019de8(const unsigned char *p);
extern int func_0203e020(const unsigned char *p);
extern int func_02019c6c(const unsigned char *p, int a, unsigned short b);
extern void func_0203e2e0(void);
extern unsigned short data_020c80f8;

typedef struct {
    unsigned char unk_00[0x1c];
    unsigned char unk_1C;
    unsigned char unk_1D[3];
    unsigned int unk_20;
} UnkStruct_02268c30;

void func_ov068_02268c30(UnkStruct_02268c30 *self, const unsigned char *other)
{
    if ((func_02019e00(other + 0x564) == 2 && func_02019de8(other + 0x564) != 0) || self->unk_20 == 0) {
        func_0203e020(other);
        func_02019c6c(other + 0x564, 1, data_020c80f8);
        func_0203e2e0();
        self->unk_1C = 3;
    }
}
