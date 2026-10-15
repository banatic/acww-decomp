/* func_020f3414 @ 0x020f3414, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_020f3414;

extern UnkStruct_020f3414 data_0213eba4;
extern void *func_020f4514(UnkStruct_020f3414 *p);
extern void func_020edb3c(UnkStruct_020f3414 *p);

UnkStruct_020f3414 *func_020f3414(UnkStruct_020f3414 *p)
{
    p->unk_00 = &data_0213eba4;
    func_020f4514(p);
    func_020edb3c(p);
    return p;
}
