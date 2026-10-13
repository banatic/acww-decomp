/* func_ov054_02261bb4 @ 0x02261bb4, 0x4c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov054_02262fac[];
extern int func_0206fc6c(void *, int);
extern void func_0206844c(void *, char *, int);
extern void func_ov054_02261cc4(void *, int);

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x6c];
    void *unk_B0;
} UnkStruct_02261bb4;

void func_ov054_02261bb4(UnkStruct_02261bb4 *obj)
{
    char c;
    int offset;
    int value;
    void *field40 = obj->unk_40;

    value = *(int *) ((char *) obj->unk_B0 + 0x808) * 12;
    offset = value;
    value = *(int *) ((char *) data_ov054_02262fac + offset);
    c = func_0206fc6c(data_ov054_02262fac, offset) != 0 ? 'T' : 'S';
    func_0206844c(field40, &c, value);
    func_ov054_02261cc4(obj, 0);
}
