/* func_0208ec14 @ 0x0208ec14, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2330;
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

struct UnkStruct_0208ec14 {
    void *unk_00;
};

struct UnkStruct_0208ec14 *func_0208ec14(struct UnkStruct_0208ec14 *obj)
{
    obj->unk_00 = &data_020e2330;
    func_0208a1f4((char *) obj + 0x28);
    func_0208a1f4((char *) obj + 0x14);
    func_0208af00(obj);
    return obj;
}
