/* func_ov107_0229c740 @ 0x0229c740, 0x70 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_020431c8(int);
extern void func_020431b8(int);
extern void func_ov107_0229c2c8(void *, int);
extern void func_ov107_0229caa8(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov107_0229d480(void *);
extern void func_ov107_0229d3a0(void *, int, int);

typedef struct {
    char pad_00[0xAC];
    int unk_AC;
    char pad_B0[0xBE - 0xAC - 4];
    char unk_BE;
} UnkStruct_0229c740;

void func_ov107_0229c740(UnkStruct_0229c740 *p)
{
    int ret = func_020431c8(p->unk_AC);
    switch (ret) {
        case 1:
            func_ov107_0229c2c8(p, 0);
            func_ov107_0229caa8(p);
            func_020431b8(p->unk_AC);
            p->unk_BE = 0xa;
            func_ov002_02208098((void *) (p), 0x13);
            p->unk_AC = -1;
            break;
        case 2:
            func_020431b8(p->unk_AC);
            func_ov107_0229d480(p);
            func_ov107_0229d3a0(p, 3, 0xff);
            p->unk_AC = -1;
            break;
        default:
            break;
    }
}
