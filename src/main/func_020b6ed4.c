/* func_020b6ed4 @ 0x020b6ed4, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b68f8(void);
extern void func_02041a9c(void);
extern void func_0208f8fc(void);
extern void func_0200471c(void);

typedef struct {
    char pad_00[0x64];
    int unk_64;
    int unk_68;
} UnkStruct_020b6ed4;

extern UnkStruct_020b6ed4 *data_020ccf94;

extern int func_02073dd4(UnkStruct_020b6ed4 *p, int arg);
extern void func_020961f0(int a, int b);
extern int func_020b6788(void);
extern void func_020738f4(UnkStruct_020b6ed4 *p, int arg);
extern int func_020b65c4(void);
extern void func_020962a4(int a, int b);
extern int func_02096284(int a);
extern void func_02096294(int a);

int func_020b6ed4(void)
{
    UnkStruct_020b6ed4 *p, *q;
    int r5, r6, r7, i;

    func_020b68f8();
    func_02041a9c();
    func_0208f8fc();
    func_0200471c();

    p = data_020ccf94;

    if (func_02073dd4(p, p->unk_64) != 0) {
        for (r5 = 0; r5 < 4; r5++) {
            func_020961f0(r5, 4);
        }
    } else {
        if (func_020b6788() != 0) {
            func_020738f4(p, 4);
            for (r5 = 0; r5 < 4; r5++) {
                func_020961f0(r5, r5);
            }
        } else {
            func_020738f4(p, 1);
            for (r5 = 0; r5 < 4; r5++) {
                func_020961f0(r5, 4);
            }
        }
    }

    if (func_020b6788() != 0) {
        if (func_020b65c4() == 6) {
            p->unk_68 = 4;
            for (i = 3; i >= 0; i--) {
                func_020962a4(i, i);
            }
        } else if (func_020b65c4() == 7) {
            r6 = p->unk_68;
            r7 = func_02096284(r6);
            r5 = 0;
            for (i = 3; i >= 0; i--) {
                if (i != r6) {
                    if (r5 == r7) {
                        r5++;
                    }
                    func_020962a4(i, r5);
                    r5++;
                }
            }
        }
    } else {
        if (func_020b65c4() == 44) {
            q = data_020ccf94;
            q->unk_64 = 4;
            q->unk_68 = 4;
            for (i = 3; i >= 0; i--) {
                func_02096294(i);
            }
        }
    }
    return 1;
}
