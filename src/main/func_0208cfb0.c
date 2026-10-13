/* func_0208cfb0 @ 0x0208cfb0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020d5b3c[];
extern void func_0208c890(void *obj, int val);
extern void func_0208a1f0(void *sub, void *src);
extern void func_0208a1ec(void *sub, int val);
extern void func_0208a144(void *sub);
extern void func_0208ce68(void *obj);

typedef struct {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    char pad_24[0x85];
    unsigned char unk_A9;
} UnkStruct_0208cfb0;

void func_0208cfb0(UnkStruct_0208cfb0 *obj)
{
    int idx;
    obj->unk_20 = 1;
    func_0208c890(obj, 1);
    if (obj->unk_A9) {
        idx = 0x2b;
    } else {
        idx = 0x26;
    }
    func_0208a1f0(&obj->sub, &data_020d5b3c[idx * 8]);
    func_0208a1ec(&obj->sub, 1);
    func_0208a144(&obj->sub);
    func_0208ce68(obj);
}
