/* func_ov131_0229af40 @ 0x0229af40, 0x34 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x94 - 0x8d - 1];
    unsigned char unk_94;
    unsigned char pad_95[0x1556 - 0x94 - 1];
    unsigned char unk_1556;
} UnkStruct_0229af40;

void func_ov131_0229af40(UnkStruct_0229af40 *obj, int a, int b)
{
    func_ov002_0220a05c(&obj->unk_94, a, b, 3, 1);
    obj->unk_1556 = obj->unk_8D;
    func_ov002_02208098((void *) (obj), 3);
}
