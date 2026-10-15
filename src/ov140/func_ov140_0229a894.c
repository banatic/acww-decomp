/* func_ov140_0229a894 @ 0x0229a894, 0x2c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8db];
    unsigned char unk_8DB;
} UnkStruct_0229a894;

extern void func_ov140_0229a638(UnkStruct_0229a894 *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

int func_ov140_0229a894(UnkStruct_0229a894 *p)
{
    if (p->unk_8DB != 0) {
        int v = p->unk_8DB - 1;
        p->unk_8DB = v;
        return v;
    } else {
        func_ov140_0229a638(p);
        return (int) func_ov002_022080a0((void *) (p), 1);
    }
}
