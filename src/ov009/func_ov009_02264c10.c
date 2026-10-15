/* func_ov009_02264c10 @ 0x02264c10, 0x30 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02264c10 {
    unsigned char pad_00[0x138];
    int unk_138;
};

extern int func_ov003_022203dc(void);
extern int func_02064328(int *a, int *b, int c, int d, int e);
extern int data_ov009_02265b54[];
extern int data_ov009_02265af0[];

int *func_ov009_02264c10(struct UnkStruct_02264c10 *param)
{
    int field = param->unk_138;
    int local = func_ov003_022203dc();
    func_02064328(data_ov009_02265b54, data_ov009_02265af0, field, field, local);
    return data_ov009_02265b54;
}
