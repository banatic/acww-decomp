/* func_0208dc00 @ 0x0208dc00, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[8];
} Entry8;

typedef struct {
    unsigned char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    unsigned char pad_to_4f[0x2b];
    unsigned char unk_4F;
} UnkStruct_0208dc00;

extern Entry8 data_020d5b3c[];
extern void func_0208a1f0(void *dst, const Entry8 *src);
extern void func_0208a1ec(void *dst, int value);
extern void func_0208a144(void *obj);

void func_0208dc00(UnkStruct_0208dc00 *obj)
{
    int idx;

    obj->unk_20 = 3;
    if (obj->unk_4F) {
        idx = 42;
    } else {
        idx = 5;
    }
    func_0208a1f0(obj->sub, &data_020d5b3c[idx]);
    func_0208a1ec(obj->sub, 1);
    func_0208a144(obj->sub);
}
