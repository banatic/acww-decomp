/* func_ov095_0229afac @ 0x0229afac, 0x44 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov095_0229e834[];
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_02088cf4(const void *a, unsigned char b, int c, int d, long long e);

typedef struct {
    unsigned char pad_00[0x17];
    unsigned char unk_17;
    unsigned char unk_18;
} UnkStruct_0229afac;

int func_ov095_0229afac(UnkStruct_0229afac *p)
{
    long long zero = 0;
    int res = func_02088cf4(data_ov095_0229e834, p->unk_18, data_021f6c58 - 0x80, data_021f6c54 - 0x60, zero);
    if (res == -1) {
        return 0;
    }
    p->unk_17 = (unsigned char) res;
    return 1;
}
