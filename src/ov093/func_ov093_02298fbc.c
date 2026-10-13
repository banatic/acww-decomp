/* func_ov093_02298fbc @ 0x02298fbc, 0x18 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov093_02298fa4(void *s, int arg);

struct UnkStruct_02298fbc {
    short unk_00;
    short unk_02;
    char unk_04;
    char unk_05;
    char unk_06;
};

void func_ov093_02298fbc(struct UnkStruct_02298fbc *s)
{
    s->unk_00 = -1;
    s->unk_02 = -1;
    s->unk_05 = 0;
    s->unk_06 = 0;
    func_ov093_02298fa4(s, 3);
}
