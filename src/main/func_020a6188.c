/* func_020a6188 @ 0x020a6188, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int v;
} UnkStruct_020a6188;

extern UnkStruct_020a6188 *data_020ccf94;

extern int func_02073dd4(UnkStruct_020a6188 *obj, int i);
extern int func_020a72d0(int i);
extern int func_020a6230(int arg0);
extern int func_02073918(UnkStruct_020a6188 *obj, int best);
extern int func_020a7300(int saved);
extern int func_020a7330(int best);
extern int func_020b65c4(void);
extern int func_020a6c98(void);
extern void func_02073820(UnkStruct_020a6188 *obj);
extern void func_02073770(UnkStruct_020a6188 *obj, int a, int b);
extern void func_020a6238(int arg0, int b);

void func_020a6188(int arg0)
{
    int best;
    int saved;
    int i;
    UnkStruct_020a6188 *obj;
    UnkStruct_020a6188 *p2;

    best = 4;
    obj = data_020ccf94;
    saved = obj->v;
    i = 3;

    while (i >= 0) {
        if (func_02073dd4(obj, i) != 0 && func_020a72d0(i) != 0) {
            best = i;
            break;
        }
        i--;
    }

    if (best == func_020a6230(arg0)) {
        return;
    }

    if (best < 4) {
        if (func_02073918(obj, best) == 0 && func_020a7300(saved) != 0) {
            i = func_020a7330(best);
            if (i == func_020b65c4()) {
                func_020b65c4();
                if (func_020a6c98() == 0) {
                    p2 = data_020ccf94;
                    func_02073820(p2);
                    func_02073770(p2, 0x11, best);
                }
            }
        }
        func_020a6238(arg0, best);
    } else {
        func_020a6238(arg0, 4);
    }
}
