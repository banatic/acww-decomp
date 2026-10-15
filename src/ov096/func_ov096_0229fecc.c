/* func_ov096_0229fecc @ 0x0229fecc, 0x88 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_02299d40(void *p);
extern void func_ov096_0229e6a0(void *p);
extern void func_ov094_02299e1c(void *p);
extern int func_ov096_0229c2fc(void *p, int val);
extern unsigned char *func_ov096_0229f8cc(void *p, int a, unsigned char b, unsigned short c, int d);
extern void func_ov096_0229e9f8(void *p, unsigned short c, int d);
extern void func_ov096_0229e82c(void *p, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229fe9c(void *p);

typedef struct {
    char pad_00[0xac];
    unsigned short unk_AC;
    char pad_AE[0xb4 - 0xac - 2];
    unsigned char unk_B4;
} UnkStruct_0229fecc;

void func_ov096_0229fecc(UnkStruct_0229fecc *p)
{
    if (func_ov094_02299d40((char *) p + 0xde0) == 0) {
        return;
    }
    func_ov096_0229e6a0(p);
    func_ov094_02299e1c((char *) p + 0xde0);
    if (p->unk_AC != 0xfff1) {
        if (func_ov096_0229c2fc(p, 0x8000)) {
            func_ov096_0229f8cc(p, 0x24, p->unk_B4, p->unk_AC, 0);
            return;
        }
        func_ov096_0229e9f8(p, p->unk_AC, 0);
        func_ov096_0229e82c(p, 1);
    }
    func_ov002_02208098((void *) (p), 0x27);
    func_ov096_0229fe9c(p);
}
