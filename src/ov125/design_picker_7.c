/* design_picker_7: 3 functions, module ov125
 * mwccarm 1.2/base -O4,s
 * func_ov125_022a09a4 @ 0x022a09a4, 0x60 bytes, Thumb
 * func_ov125_022a0984 @ 0x022a0984, 0x1e bytes, Thumb
 * func_ov125_022a0968 @ 0x022a0968, 0x1a bytes, Thumb
 */

typedef struct {
    char pad_00[0x8c];
    char unk_8C;
} UnkStruct_022a0984;

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *obj);
extern void *func_ov124_0229f460(void *obj);
extern void *func_ov002_02209b14(void *obj);
extern void *func_ov002_02207e40(void *obj);
extern void *func_ov002_02209ccc(void *obj);
extern void *func_ov002_0220b008(void *obj);
extern char data_ov125_022a0ab8;
extern void func_ov125_022a0510(UnkStruct_022a0984 *p);
extern unsigned char *func_ov002_022080a0(UnkStruct_022a0984 *p, unsigned char arg1);
extern void func_ov125_022a04e4(int a1);
extern int func_020ee45c(void *arg0);
extern void func_ov092_0229929c(void *);

void *func_ov125_022a09a4(void)
{
    void *obj = func_ov002_02207f80(0x880);
    if (obj) {
        func_ov002_0220830c(obj);
        *(void **) obj = (void *) &data_ov125_022a0ab8;
        func_ov124_0229f460((char *) obj + 0x94);
        func_ov002_02209b14((char *) obj + 0x180);
        func_ov002_02207e40((char *) obj + 0x574);
        func_ov002_02209ccc((char *) obj + 0x644);
        func_ov002_0220b008((char *) obj + 0x6a8);
    }
    return obj;
}

int func_ov125_022a0984(UnkStruct_022a0984 *p)
{
    func_ov125_022a0510(p);
    p->unk_8C = 0;
    func_ov002_022080a0(p, 0);
    return 1;
}

int func_ov125_022a0968(int a1)
{
    func_ov092_0229929c((void *) func_020ee45c((void *) a1));
    func_ov125_022a04e4(a1);
    return 1;
}
