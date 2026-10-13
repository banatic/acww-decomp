/* func_ov120_0229aacc @ 0x0229aacc, 0x54 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(void *p, int n);
extern int func_ov002_0220a58c(void *p, unsigned char a, unsigned char b);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229aacc {
    char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char unk_A5;
    unsigned char unk_A6;
    char pad_A7[0x5cd];
    unsigned int unk_674;
};

int func_ov120_0229aacc(struct UnkStruct_0229aacc *obj)
{
    if (func_ov120_0229a448(obj, 8) == 0) {
        return 0;
    } else {
        if (func_ov002_0220a58c(&obj->unk_674, data_021f6c58, data_021f6c54) != 0) {
            obj->unk_A5 = data_021f6c54;
            obj->unk_A6 = obj->unk_A4;
            return 1;
        } else {
            return 0;
        }
    }
}
