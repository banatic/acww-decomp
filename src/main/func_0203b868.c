/* func_0203b868 @ 0x0203b868, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xfc];
    short unk_FC;
    short unk_FE;
    int unk_100;
    int unk_104;
    int unk_108;
    int unk_10C;
    int unk_110;
    int unk_114;
    int unk_118;
    short unk_11C;
    short unk_11E;
    int unk_120;
    int unk_124;
    int unk_128;
    int unk_12C;
    int unk_130;
    int unk_134;
    int unk_138;
    int unk_13C;
    int unk_140;
    int unk_144;
    char pad_148[0x168 - 0x148];
    int unk_168;
    int unk_16C;
    int unk_170;
    char pad_174[0x1f4 - 0x174];
    char unk_1F4;
    char pad_1F5[0x204 - 0x1f5];
    int unk_204;
    int unk_208;
    int unk_20C;
    int unk_210;
    int unk_214;
    int unk_218;
} UnkStruct_0203b868;

extern int func_0203b7d0(void *);
extern void func_0203ad58(void);
extern void func_0203c99c(void *, int);

void func_0203b868(UnkStruct_0203b868 *p)
{
    int *q110;
    int *q114;
    int *q118;
    int *q168;
    int *q16c;
    int *q170;

    p->unk_1F4 = 0;
    func_0203b7d0(p);
    p->unk_FC = p->unk_11C;
    p->unk_FE = p->unk_11E;
    p->unk_100 = p->unk_120;
    p->unk_104 = p->unk_124;
    p->unk_108 = p->unk_128;
    p->unk_10C = p->unk_12C;
    q110 = &p->unk_110;
    *q110 = p->unk_130;
    q114 = &p->unk_114;
    *q114 = p->unk_134;
    q118 = &p->unk_118;
    *q118 = p->unk_138;
    q168 = &p->unk_168;
    *q168 = p->unk_13C;
    q16c = &p->unk_16C;
    *q16c = p->unk_140;
    q170 = &p->unk_170;
    *q170 = p->unk_144;
    p->unk_204 = *q110;
    p->unk_208 = *q114;
    p->unk_20C = *q118;
    p->unk_210 = *q168;
    p->unk_214 = *q16c;
    p->unk_218 = *q170;
    func_0203ad58();
    func_0203c99c(p, 2);
}
