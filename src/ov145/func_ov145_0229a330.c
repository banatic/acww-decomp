/* func_ov145_0229a330 @ 0x0229a330, 0x28 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov145_02299f7c(void *p);
extern void func_ov002_02207fc0(void *p);
extern void func_ov002_02208098(void *p, int n);

typedef struct {
    unsigned char pad_00[0xC1];
    unsigned char c1;
    unsigned char c2;
} UnkStruct_0229a330;

void func_ov145_0229a330(UnkStruct_0229a330 *p)
{
    p->c2 = p->c1;
    func_ov145_02299f7c(p);
    func_ov002_02207fc0(p);
    func_ov002_02208098(p, 3);
}
