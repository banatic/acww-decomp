/* func_020b5a18 @ 0x020b5a18, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(void *, void *);

typedef struct {
    char pad_00[0x60];
    void *unk_60;
    void *unk_64;
    void *unk_68;
} UnkStruct_020b5a18;

int func_020b5a18(UnkStruct_020b5a18 *obj)
{
    func_020e993c(obj->unk_60, obj->unk_64);
    func_020e993c(obj->unk_60, obj->unk_68);
    return 1;
}
