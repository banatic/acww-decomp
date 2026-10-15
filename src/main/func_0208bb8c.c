/* func_0208bb8c @ 0x0208bb8c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e21fc;

typedef struct {
    void *unk_00;
    char pad_04[8];
    char unk_0C[0x30];
    char unk_3C;
} UnkStruct_0208bb8c;

extern void func_0208ba10(void *obj);
extern void *func_020b5618(void *p);
extern void func_0208a1f4(void *p);
extern void func_0208af00(void *obj);

UnkStruct_0208bb8c *func_0208bb8c(UnkStruct_0208bb8c *obj)
{
    obj->unk_00 = &data_020e21fc;
    func_0208ba10(obj);
    func_020b5618(&obj->unk_3C);
    func_0208a1f4(&obj->unk_0C);
    func_0208af00(obj);
    return obj;
}
