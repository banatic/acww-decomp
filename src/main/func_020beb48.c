/* func_020beb48 @ 0x020beb48, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022197c4(int param, void *ptr);
extern void func_020be9f8(void);

typedef struct {
    int unk_00;
    void *unk_04;
} UnkStruct_020beb48;

void func_020beb48(UnkStruct_020beb48 *p)
{
    p->unk_00 = 4;
    func_ov003_022197c4(1, p->unk_04);
    func_020be9f8();
}
