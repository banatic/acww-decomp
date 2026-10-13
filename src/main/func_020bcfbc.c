/* func_020bcfbc @ 0x020bcfbc, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020bcfbc_2 {
    int unk_00;
    unsigned char pad_04[12];
    unsigned char unk_10;
    unsigned char unk_11;
} UnkStruct_020bcfbc_2;

typedef struct UnkStruct_020bcfbc {
    char pad_00[0x2f58];
    UnkStruct_020bcfbc_2 elem[4];
    int unk_2FA8;
} UnkStruct_020bcfbc;

extern int func_020bdc50(UnkStruct_020bcfbc *obj, int a, int b, int c, int d);
extern void func_020beb98(int *ptr, int val);
extern void func_020bebd8(UnkStruct_020bcfbc_2 *p);

void func_020bcfbc(UnkStruct_020bcfbc *obj)
{
    UnkStruct_020bcfbc_2 *p;
    UnkStruct_020bcfbc_2 *end;
    int i;
    int r6;
    int zero1, zero2, zero3;
    int byte10;

    p = obj->elem;
    end = p + 4;
    r6 = 0x21;
    i = 0;
    zero1 = i;
    zero2 = i;
    zero3 = i;

    while (p < end) {
        if (p->unk_11) {
            byte10 = p->unk_10;
            if (func_020bdc50(obj, 0xB, r6, zero1, i)) {
                if (byte10) {
                    func_020bdc50(obj, 0xB, r6 + 1, zero2, i | 0x10);
                    func_020bdc50(obj, 0xB, r6 + 2, zero3, i | 0x20);
                }
            } else {
                func_020beb98(&obj->unk_2FA8, p->unk_00);
            }
            func_020bebd8(p);
        }
        p++;
        r6 += 3;
        i++;
    }
}
