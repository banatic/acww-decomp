/* func_0208b954 @ 0x0208b954, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *sub, void *data);
extern void func_0208a1ec(void *sub, int value);
extern void func_0208a144(void *sub);
extern void func_0208b800(void *obj);
extern void func_0208b83c(void *obj);
extern int data_020d5c54;

typedef struct {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
} UnkStruct_0208b954;

void func_0208b954(UnkStruct_0208b954 *obj)
{
    obj->unk_20 = 1;
    func_0208a1f0(obj->sub, &data_020d5c54);
    func_0208a1ec(obj->sub, 1);
    func_0208a144(obj->sub);
    func_0208b800(obj);
    func_0208b83c(obj);
}
