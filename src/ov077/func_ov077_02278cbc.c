/* func_ov077_02278cbc @ 0x02278cbc, 0x42 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(int);
extern void func_02035684(int, int, int);

struct UnkStruct_02278cbc {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

void func_ov077_02278cbc(struct UnkStruct_02278cbc *p)
{
    switch (p->unk_1E) {
        case 3:
        case 8:
        case 18:
        case 26:
        case 35:
            func_02035638(0x43);
            func_02035684(0x17, 0x16, 0x20);
            break;
        default:
            break;
    }
}
