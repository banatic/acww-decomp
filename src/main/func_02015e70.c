/* func_02015e70 @ 0x02015e70, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020641c8(void *);
extern void func_02064210(unsigned int, void *);
extern void func_02068404(unsigned int, unsigned int, void *);
extern void func_020641b0(void *);

typedef struct {
    char pad_00[0x40];
    unsigned int unk_40;
} GUnknownStruct;

void func_02015e70(GUnknownStruct *param0, unsigned int param1, unsigned int param2)
{
    char buffer[0x20];
    func_020641c8(buffer);
    func_02064210(param1, buffer);
    func_02068404(param0->unk_40, param2, buffer);
    func_020641b0(buffer);
}
