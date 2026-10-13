/* func_020b52dc @ 0x020b52dc, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x3c];
    unsigned int unk_3C;
    char pad_40[4];
    unsigned char flag44;
    unsigned char flag45;
    char pad_46;
    unsigned char flag47;
    unsigned char flag48;
} UnkStruct_020b52dc;

extern unsigned int func_02050bdc_unk(unsigned int);
extern int func_020b4d60(UnkStruct_020b52dc *p, unsigned int x);
extern void func_020b512c(UnkStruct_020b52dc *p);

void func_020b52dc(UnkStruct_020b52dc *p, unsigned int x)
{
    if (p->flag48) {
        x = func_02050bdc_unk(x);
        p->flag48 = 0;
    }
    if (p->flag47 && p->flag44) {
        if (func_020b4d60(p, x) == 0) {
            p->flag45 = 0;
        }
        p->flag44 = 0;
    }
    if (p->flag45) {
        p->unk_3C = x;
        func_020b512c(p);
    }
}
