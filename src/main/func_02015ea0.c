/* func_02015ea0 @ 0x02015ea0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8228(void *);
extern void func_020b44a4(void *, int);
extern void func_02068404(int, int, void *);
extern void func_020a8210(void *);

struct UnkStruct_02015ea0 {
    char pad_00[0x40];
    int unk_40;
};

void func_02015ea0(struct UnkStruct_02015ea0 *arg0, int arg1, int arg2)
{
    char buffer[0x60];

    func_020a8228(buffer);
    func_020b44a4(buffer, arg1);
    func_02068404(arg0->unk_40, arg2, buffer);
    func_020a8210(buffer);
}
