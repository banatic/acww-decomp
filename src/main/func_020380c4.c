/* func_020380c4 @ 0x020380c4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203864c(void *arg);
extern void func_02038368(void *arg);
extern void func_02038bfc(void);
extern void func_020508a0(void);
extern void func_020740a0(void);

typedef struct {
    unsigned char pad_00[0xBC];
    int unk_BC;
    unsigned char pad_C0[8];
    unsigned char unk_C8;
} UnkStruct_020380c4;

void func_020380c4(UnkStruct_020380c4 *obj)
{
    obj->unk_BC = 5;
    obj->unk_C8 = 1;
    func_0203864c(obj);
    func_02038368(obj);
    func_02038bfc();
    func_020508a0();
    func_020740a0();
}
