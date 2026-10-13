/* func_02014fe8 @ 0x02014fe8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[0x8];
    unsigned int unk_4C;
    unsigned char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_02014fe8;

extern int func_02019e00(unsigned int);
extern int func_02019de8(unsigned int);
extern void func_02068434(unsigned int);
extern void func_02016004(UnkStruct_02014fe8 *);

int func_02014fe8(UnkStruct_02014fe8 *p)
{
    int result = 0;
    if (p->unk_4C == 0) {
        goto done;
    }
    if (p->unk_40 == 0) {
        goto done;
    }
    if (func_02019e00(p->unk_4C + 0x564) != 0x10) {
        goto done;
    }
    if (func_02019de8(p->unk_4C + 0x564) == 0) {
        goto done;
    }
    func_02068434(p->unk_40);
    func_02016004(p);
    p->unk_AC = 2;
    result = 1;
done:
    return result;
}
