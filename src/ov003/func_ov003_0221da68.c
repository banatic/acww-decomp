/* func_ov003_0221da68 @ 0x0221da68, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b3220(int arg);
extern void func_020b3188(int arg);

typedef struct {
    char pad_00[0x2b4];
    signed char unk_2B4;
    signed char unk_2B5;
} UnkStruct_0221da68;

void func_ov003_0221da68(UnkStruct_0221da68 *p, int value, int arg)
{
    if (value == p->unk_2B4) {
        func_020b3220(arg);
    } else if (value == p->unk_2B5) {
        func_020b3188(arg);
    }
}
