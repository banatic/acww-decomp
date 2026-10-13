/* func_ov094_0229a1c0 @ 0x0229a1c0, 0x44 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a1c0 {
    char pad_00[14];
    unsigned char flag;
} UnkStruct_0229a1c0;

extern char data_ov094_0229bec0[];
extern int data_021fbe94;
extern void func_02002c6c(char *p1, int p2, int p3, int p4, int p5, int p6);
extern void func_ov094_0229a110(UnkStruct_0229a1c0 *s);
extern void func_ov094_02299c40(UnkStruct_0229a1c0 *s);
extern void func_ov094_02299e1c(UnkStruct_0229a1c0 *s);

void func_ov094_0229a1c0(UnkStruct_0229a1c0 *s)
{
    func_02002c6c(data_ov094_0229bec0, data_021fbe94, s->flag, 0x200, 0x200, 0x2ff);
    func_ov094_0229a110(s);
    func_ov094_02299c40(s);
    func_ov094_02299e1c(s);
}
