/* func_ov126_022a17d8 @ 0x022a17d8, 0x84 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov126_0229f7a8(void *, int);
extern void func_ov002_022080a0(void *, int);
extern int func_ov126_0229f7c8(void *, int);
extern void func_0206fc4c(int);
extern void func_ov126_0229f83c(void *);
extern void func_0206fc1c(void *, unsigned char);
extern int func_0206fca4(void);
extern void func_020ee45c(void *);
extern void func_ov090_02298fa4(void);
extern void func_ov126_022a16ac(void *);

struct UnkStruct_022a17d8 {
    char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7[0x41a1];
    int unk_4248;
};

void func_ov126_022a17d8(struct UnkStruct_022a17d8 *obj)
{
    if (func_ov002_02207f3c(obj, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov126_0229f7a8(obj, 1);
        func_ov002_022080a0(obj, 5);
        if (func_ov126_0229f7c8(obj, 0x40)) {
            func_0206fc4c(0);
        } else {
            int state;
            func_0206fc4c(1);
            func_ov126_0229f83c(obj);
            func_0206fc1c(&obj->unk_4248, obj->unk_A6);
            state = func_0206fca4();
            if (state == 0x18) {
                goto body;
            }
            if (state == 0x19) {
                goto body;
            }
            if (state == 0x1a) {
                goto body;
            }
            goto end;
        body:
            func_020ee45c(obj);
            func_ov090_02298fa4();
        end:;
        }
    } else {
        func_ov126_022a16ac(obj);
    }
}
