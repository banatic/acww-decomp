/* villager_talk_scene: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202d794 @ 0x0202d794, 0x72 bytes, Thumb
 * func_0202d754 @ 0x0202d754, 0x40 bytes, Thumb
 * func_0202d730 @ 0x0202d730, 0x24 bytes, Thumb
 */

typedef struct {
    char pad_00[0x100];
    int unk_100;
} UnkStruct_0202d730;

extern unsigned short *func_02098f48(int a, int b);
extern int func_02098e8c(int a, int i);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);
extern void *func_02098e44(void *a, int b);
extern int func_02065ec0(void *p);
extern int func_02019c6c(int arg0, int arg1, unsigned short arg2);
extern unsigned short data_020c80f8;

int func_0202d794(int a, unsigned short *ptr)
{
    unsigned short *p;
    int i;
    int flag1 = 0;
    int flag2 = 0;

    p = func_02098f48(a, 0);
    for (i = 0; i < 15; p++, i++) {
        if (func_02098e8c(a, i) == 2) {
            int result;
            if (func_0204bcdc(p)) {
                int t = func_0204bc64(p);
                result = (t == func_0204bc64(ptr)) ? 1 : flag1;
            } else {
                result = (*p == *ptr) ? 1 : flag2;
            }
            if (result) {
                return i;
            }
        }
    }
    return -1;
}

void *func_0202d754(void *arg)
{
    void *p;
    void *result;
    int i;

    p = func_02098e44(arg, 0);
    result = 0;
    i = (int) result;
    for (; i < 10; i++) {
        if ((unsigned char) (func_02065ec0(p) + 0xf9) <= 1) {
            result = p;
            break;
        }
        p = (char *) p + 0x100;
    }
    return result;
}

int func_0202d730(UnkStruct_0202d730 *param)
{
    return func_02019c6c(param->unk_100 + 0x564, 2, data_020c80f8);
}
