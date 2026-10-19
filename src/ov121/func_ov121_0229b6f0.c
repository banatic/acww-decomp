/* func_ov121_0229b6f0 @ 0x0229b6f0, 0x74 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *s, unsigned char value);
extern void func_ov002_02207ce4(void *p, int a);
extern int func_ov121_0229ad68(void);
extern void func_ov121_02299a4c(void *s, int a);
extern int func_ov002_02207d24(void *p, int a);
extern void func_0200467c(int a);
extern void func_ov002_02207d00(void *p);

typedef struct {
    char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char unk_AE;
    unsigned char unk_AF;
} UnkStruct_0229b6f0;

void func_ov121_0229b6f0(UnkStruct_0229b6f0 *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(s, 0);
        func_ov002_02207ce4((char *) s + 0x2d8, 0x3c);
    } else {
        if (func_ov121_0229ad68()) {
            s->unk_AE = s->unk_AD;
            func_ov121_02299a4c(s, 4);
            s->unk_AF = 0x18;
            func_ov002_02208098(s, 2);
            func_ov002_02207d24((char *) s + 0x2d8, 1);
            func_0200467c(0xd);
        } else {
            func_ov002_02207d00((char *) s + 0x2d8);
        }
    }
}
