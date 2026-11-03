/* time_screen_2: 2 functions, module ov136
 * mwccarm 1.2/base -O4,s
 * func_ov136_0229c6e4 @ 0x0229c6e4, 0x50 bytes, Thumb
 * func_ov136_0229c684 @ 0x0229c684, 0x60 bytes, Thumb
 */

typedef struct {
    char pad_00[0x94];
    char sub_94;
    char pad_95[0x2b77 - 0x95];
    unsigned char flag;
} UnkStruct_0229c6e4;

typedef struct {
    char pad_00[0x8D];
    unsigned char unk_8D;
    char pad_8E[0x94 - 0x8D - 1];
    char unk_94;
    char pad_95[0x2B76 - 0x94 - 1];
    unsigned char unk_2B76;
} UnkStruct_0229c684;

extern int func_ov136_0229c574(UnkStruct_0229c6e4 *p, int n);
extern void func_ov002_0220a2b4(void *ptr);
extern void func_ov002_0220a314(void *ptr);
extern int func_ov136_0229c794(UnkStruct_0229c6e4 *p);
extern int func_ov136_0229c750(UnkStruct_0229c6e4 *p);
extern void func_ov002_0220a05c(void *, void *, void *, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov136_0229c554(void *, int);

void func_ov136_0229c684(UnkStruct_0229c684 *arg0, void *arg1, void *arg2);

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
    func_ov136_0229c684((UnkStruct_0229c684 *) p, (void *) a, (void *) b);
}

void func_ov136_0229c684(UnkStruct_0229c684 *arg0, void *arg1, void *arg2)
{
    if (func_ov136_0229c574((UnkStruct_0229c6e4 *) arg0, 4)) {
        func_ov002_0220a05c(&arg0->unk_94, arg1, arg2, 2, 1);
    } else {
        func_ov002_0220a05c(&arg0->unk_94, arg1, arg2, 3, 1);
    }
    arg0->unk_2B76 = arg0->unk_8D;
    func_ov002_02208098((void *) (arg0), 0xa);
    func_ov136_0229c554(arg0, 4);
}
