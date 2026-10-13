/* func_ov136_0229c6e4 @ 0x0229c6e4, 0x50 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    char sub_94;
    char pad_95[0x2b77 - 0x95];
    unsigned char flag;
} UnkStruct_0229c6e4;

extern int func_ov136_0229c574(UnkStruct_0229c6e4 *p, int n);
extern void func_ov002_0220a2b4(void *ptr);
extern void func_ov002_0220a314(void *ptr);
extern int func_ov136_0229c794(UnkStruct_0229c6e4 *p);
extern int func_ov136_0229c750(UnkStruct_0229c6e4 *p);
extern void func_ov136_0229c684(UnkStruct_0229c6e4 *p, int a, int b);

void func_ov136_0229c6e4(UnkStruct_0229c6e4 *p)
{
    int a, b;
    if (func_ov136_0229c574(p, 2) != 0) {
        goto L_else;
    }
    if (p->flag == 2) {
        goto L_then;
    }
L_else:
    func_ov002_0220a2b4(&p->sub_94);
    goto L_done;
L_then:
    func_ov002_0220a314(&p->sub_94);
L_done:
    a = func_ov136_0229c794(p);
    b = func_ov136_0229c750(p);
    func_ov136_0229c684(p, a, b);
}
