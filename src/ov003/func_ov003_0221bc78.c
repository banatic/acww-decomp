/* func_ov003_0221bc78 @ 0x0221bc78, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbc0(void *);
extern int func_0206fc6c(int);
extern void func_020ae270(void);
extern void func_0206844c(void *, char *, char *);
extern void func_ov003_0221bfa8(void *, int);
extern int func_020b23ec(unsigned short, int);
extern char data_ov003_02238778;

struct ObjStruct {
    int pad_00[2];
    int unk_08;
};

struct UnkStruct_0221bc78 {
    char pad_00[0x12C];
    struct ObjStruct *unk_12C;
    char pad_130[0x136 - 0x130];
    unsigned short unk_136;
};

void func_ov003_0221bc78(struct UnkStruct_0221bc78 *p)
{
    char buf[8];
    int ret;
    ret = func_0206fbc0(p);
    if (ret == 0) {
        return;
    }
    if (func_0206fc6c(ret) != 0) {
        func_020ae270();
        buf[0] = 3;
        func_0206844c(p->unk_12C, buf, &data_ov003_02238778);
        p->unk_12C->unk_08 = 1;
        func_ov003_0221bfa8(p, 3);
    } else {
        buf[1] = 4;
        func_0206844c(p->unk_12C, buf + 1, &data_ov003_02238778);
        p->unk_12C->unk_08 = 1;
        func_ov003_0221bfa8(p, 3);
        func_020b23ec(p->unk_136, 0);
    }
}
