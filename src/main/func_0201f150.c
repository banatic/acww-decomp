/* func_0201f150 @ 0x0201f150, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0201f150;

extern void func_0201f520(void);
extern void func_020157d4(void *obj, void (*cb)(void), int a, int b);
extern void func_02015828(void *obj, int a);
extern void func_0202dbf0(void *obj, UnkStruct_0201f150 arg);
extern UnkStruct_0201f150 data_020d8e28;

void func_0201f150(void *obj)
{
    func_020157d4(obj, func_0201f520, 13, 1);
    func_02015828(obj, 0);
    func_0202dbf0(obj, data_020d8e28);
}
