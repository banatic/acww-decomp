/* func_ov066_0226997c @ 0x0226997c, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_0226760c(void);
extern void DC_InvalidateRange(void *addr, int n);

typedef struct UnkStruct_0226997c UnkStruct_0226997c;
typedef struct UnkStruct_0226997c_2 UnkStruct_0226997c_2;

typedef struct {
    void *unk_00;
    UnkStruct_0226997c *unk_04;
} UnkStruct_0226997c_3;

struct UnkStruct_0226997c {
    void *unk_00;
    UnkStruct_0226997c_2 *unk_04;
};

struct UnkStruct_0226997c_2 {
    unsigned char pad_00[0x17e];
    unsigned short value;
};

extern UnkStruct_0226997c_3 *data_ov066_0226bdf4;

unsigned short func_ov066_0226997c(void)
{
    UnkStruct_0226997c_3 *a;
    UnkStruct_0226997c *b;
    UnkStruct_0226997c_2 *c;

    if (func_ov066_0226760c() != 10) {
        return 0;
    }

    a = data_ov066_0226bdf4;
    b = a->unk_04;
    c = b->unk_04;

    DC_InvalidateRange(&c->value, 2);

    return c->value;
}
