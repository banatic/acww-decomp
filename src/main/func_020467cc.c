/* func_020467cc @ 0x020467cc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
} UnkStruct_020467cc;

extern int data_021c79c4[];
extern int data_021c779c[];

extern UnkStruct_020467cc *func_0204e414(void);
extern void func_0204a5d4(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02048418(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_020483c4(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02048a80(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02048238(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02046650(void);

void func_020467cc(void)
{
    UnkStruct_020467cc *obj;
    int x, y;

    obj = func_0204e414();
    if (obj != 0) {
        x = obj->unk_04 - 2;
        y = obj->unk_08 - 2;
        func_0204a5d4(data_021c79c4, obj, x, y);
        func_02048418(data_021c779c, obj, x, y);
        func_020483c4(data_021c779c, obj, x, y);
        func_02048a80(data_021c779c, obj, x, y);
        func_02048238(data_021c779c, obj, x, y);
        func_02046650();
    }
}
