/* func_ov048_02262444 @ 0x02262444, 0x108 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov048_0226472c;
extern int data_ov048_02263d20;
typedef struct {
    int a;
    unsigned char b;
} UnkStruct_02262444;
extern UnkStruct_02262444 data_ov048_022641a8[11];

extern int func_020984e8(void);
extern int func_020a12e8(void);
extern int func_ov048_02262670(void *);
extern void func_ov048_02262678(void *, int);
extern int func_0202e9fc(void);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_0209dcac(void);
extern int func_ov004_0222d4d4(void);
extern void func_ov004_0222d518(void);

void func_ov048_02262444(void *a, void *b)
{
    int saved;
    int v;
    int idx;

    if (!(data_ov048_0226472c & 1)) {
        v = data_ov048_02263d20;
        data_ov048_022641a8[0].a = v;
        data_ov048_022641a8[1].a = v;
        data_ov048_022641a8[2].a = v;
        data_ov048_022641a8[3].a = v;
        data_ov048_022641a8[4].a = v;
        data_ov048_022641a8[5].a = v;
        data_ov048_022641a8[6].a = v;
        data_ov048_022641a8[7].a = v;
        data_ov048_022641a8[9].a = v;
        data_ov048_022641a8[10].a = v;
        data_ov048_0226472c |= 1;
    }

    ((unsigned char *) a)[0x811] = 0;
    ((unsigned char *) a)[0x810] = 0;

    saved = func_020984e8();

    if (func_020a12e8() != 0) {
        func_ov048_02262678(a, 8);
    } else {
        if (func_ov048_02262670(a) == 6) {
            if (func_ov004_0222d4d4() == 0) {
                func_ov004_0222d518();
            }
        } else if (func_ov048_02262670(a) == 7 || func_ov048_02262670(a) == 9 || func_ov048_02262670(a) == 10) {
            // empty
        } else {
            if (func_0202e9fc() == 0) {
                func_ov048_02262678(a, 5);
            } else {
                if (func_02099020(saved, 5) == 0) {
                    func_ov048_02262678(a, 0);
                    func_02098ff8(saved, 5);
                } else {
                    v = func_0209dcac() + 1;
                    func_ov048_02262678(a, v);
                }
            }
        }
    }

    idx = *(int *) ((unsigned char *) a + 0xb0);
    if (idx >= 0 && idx < 11) {
        ((unsigned char *) b)[4] = data_ov048_022641a8[idx].b;
        *(int *) b = data_ov048_022641a8[*(int *) ((unsigned char *) a + 0xb0)].a;
    }
}
