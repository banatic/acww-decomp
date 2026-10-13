/* func_ov094_0229a634 @ 0x0229a634, 0x34 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov094_0229bf98[];
extern void func_020896b8(int, int *, int, int, int, int, int);

typedef struct {
    char pad_00[0xA50];
    int unk_A50;
} GameStruct;

void func_ov094_0229a634(GameStruct *obj, int a, int b, int c)
{
    func_020896b8(1, data_ov094_0229bf98, a - 8, b - 8, c, obj->unk_A50, 0);
}
