/* func_ov054_0226202c @ 0x0226202c, 0x9c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct GlobalStruc {
    unsigned char pad_00[0x64];
    int unk_64;
};
extern GlobalStruc *data_020ccf94;

struct UnkStruct_0226202c {
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

extern "C" {
int func_0201c0e0(void *);
int func_0201c040(void *, int *, int *);
void func_0201c054(void *, int, int, int);
int func_0201c2a4(void *, int);
void func_02016108(void *, int);
void func_ov054_02262528(void *, int);
int func_020a7278(void);
int func_ov054_0226202c(void *arg);
}

extern "C" int func_ov054_0226202c(void *arg)
{
    if (func_0201c0e0(arg) == 0) {
        goto end;
    }
    {
        int a = 4, b = 4;
        if (func_0201c040(arg, &a, &b) != 0) {
            if (a == data_020ccf94->unk_64 && a == b) {
                func_0201c054(arg, 1, data_020ccf94->unk_64, data_020ccf94->unk_64);
                ((UnkStruct_0226202c *) ((char *) arg + 0x658))->m2();
                {
                    int v = func_0201c2a4(arg, 4);
                    func_02016108((char *) arg + 0x658, v);
                }
                func_ov054_02262528(arg, 4);
                goto end;
            }
        }
        if (func_020a7278() != 0) {
            if (b == 4) {
                func_0201c054(arg, 1, data_020ccf94->unk_64, 4);
                func_ov054_02262528(arg, 2);
            }
        }
    }
end:
    return 1;
}
