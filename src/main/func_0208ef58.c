/* func_0208ef58 @ 0x0208ef58, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *obj);
extern void func_0208a1f8(void *sub);
extern unsigned char data_020e236c[];

struct Func0208ef58Obj {
    void *unk_00;
    unsigned char pad_04[8];
    unsigned char sub[8];
    unsigned char pad_14[12];
    int unk_20;
};

void *func_0208ef58(struct Func0208ef58Obj *obj)
{
    func_0208af30(obj);
    obj->unk_00 = data_020e236c;
    func_0208a1f8(obj->sub);
    obj->unk_20 = 0;
    return obj;
}
