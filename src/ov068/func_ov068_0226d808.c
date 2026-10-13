/* func_ov068_0226d808 @ 0x0226d808, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b790(void *p);
extern void func_02012214(void *a, void *b);

typedef struct {
    unsigned int d[12];
} UnkStruct_0226d808_2;

extern UnkStruct_0226d808_2 data_021cfe68;

typedef struct {
    unsigned char pad_00[0x150];
    UnkStruct_0226d808_2 unk_150;
} UnkStruct_0226d808;

int func_ov068_0226d808(UnkStruct_0226d808 *p)
{
    data_021cfe68 = p->unk_150;
    if (func_0201b790(p) == 0) {
        return 0;
    }
    func_02012214((char *) p + 0x9b4, p);
    return 1;
}
