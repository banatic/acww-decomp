/* func_ov121_0229a480 @ 0x0229a480, 0x8c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_0229af40(void *obj, unsigned char byte);
extern int func_ov121_0229af58(void *obj, unsigned char byte);
extern int func_0206fe54(int x);
extern void func_0208aa60(void *dst, int value, int offset);
extern int func_02062e50(void *buf);
extern int func_020984e8(int a);
extern int func_020996b8(int b);
extern int func_02072bb0(int c, unsigned char byte);
extern int func_02072d4c(int d);
extern void func_02072ea4(int e, void *buf);
extern void func_0208aecc(void *buf);
extern void func_02051984(void *dst, void *src);
extern void func_0208aa48(void *dst, void *src);
extern void func_0208aeb8(void *buf);
extern void func_02062e00(void *buf);

typedef struct {
    unsigned char pad_00[0xAD];
    unsigned char unk_AD;
    unsigned char pad_AE[0x22A];
    unsigned char unk_2D8[1];
} UnkStruct_0229a480;

void func_ov121_0229a480(UnkStruct_0229a480 *obj)
{
    int res1;
    int offset;
    int raw;
    int a, b, c, d, e;
    char buf1[0x24];
    char buf2[0x30];

    res1 = func_ov121_0229af40(obj, obj->unk_AD);
    offset = res1 - 0x84;
    if (func_0206fe54(res1)) {
        offset -= 0xA;
    }

    raw = func_ov121_0229af58(obj, obj->unk_AD);
    func_0208aa60(obj->unk_2D8, raw - 0x78, offset);

    a = func_02062e50(buf1);
    b = func_020984e8(a);
    c = func_020996b8(b);
    d = func_02072bb0(c, obj->unk_AD);
    e = func_02072d4c(d);
    func_02072ea4(e, buf1);
    func_0208aecc(buf2);
    func_02051984(buf2, buf1);
    func_0208aa48(obj->unk_2D8, buf2);
    func_0208aeb8(buf2);
    func_02062e00(buf1);
}
