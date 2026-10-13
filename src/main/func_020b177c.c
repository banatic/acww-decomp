/* func_020b177c @ 0x020b177c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void);
extern int func_020644cc(int);
extern void func_02064af4(int, void *, int);
extern void MI_CpuCopy8(void *, const void *, int);
extern void func_02002bd0(void *, int, int, int, int);
extern int data_020e4220[5];

typedef struct {
    char pad_00[0x24];
    char block0[128];
    char blocks[5][128];
    char arr1[4];
    char arr2[4];
    char unk_32C;
} UnkStruct_020b177c;

void func_020b177c(UnkStruct_020b177c *obj, int param1)
{
    int i;

    func_020b9ccc();

    for (i = 0; i < 5; i++) {
        obj->arr1[i] = (char) (func_020644cc(0x5a) + 10);
        obj->arr2[i] = 0;
    }

    obj->unk_32C = (char) param1;

    for (i = 0; i < 5; i++) {
        func_02064af4(data_020e4220[i], &obj->blocks[i], 128);
    }

    MI_CpuCopy8(obj->blocks, &obj->block0, 128);
    func_02002bd0(&obj->block0, param1, 4, 4, 7);
}
