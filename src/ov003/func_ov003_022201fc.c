/* func_ov003_022201fc @ 0x022201fc, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022201fc {
    unsigned char pad_00[0x22c];
    unsigned int unk_22C;
    unsigned int unk_230;
};

extern struct UnkStruct_022201fc *data_ov003_0223cef0[32];

struct UnkStruct_022201fc *func_ov003_022201fc(unsigned int a, unsigned int b)
{
    unsigned int i = 0;
    while (i < 32) {
        struct UnkStruct_022201fc *p = data_ov003_0223cef0[i];
        if (p != 0 && p->unk_22C == a && p->unk_230 == b) {
            return p;
        }
        i++;
    }
    return 0;
}
