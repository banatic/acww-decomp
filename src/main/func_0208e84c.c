/* func_0208e84c @ 0x0208e84c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int *unk_00;
    unsigned char pad_04[8];
    unsigned char unk_0C[0x20];
    unsigned char unk_2C[4];
} UnkStruct_0208e84c;

extern int data_020e2314;
extern void func_0208a1f4(void *);
extern void func_0208af00(UnkStruct_0208e84c *);

UnkStruct_0208e84c *func_0208e84c(UnkStruct_0208e84c *obj)
{
    obj->unk_00 = &data_020e2314;
    func_0208a1f4(obj->unk_2C);
    func_0208a1f4(obj->unk_0C);
    func_0208af00(obj);
    return obj;
}
