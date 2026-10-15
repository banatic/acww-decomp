/* func_020f9ea4 @ 0x020f9ea4, 0xa4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#pragma arm

extern void func_020f9d00(void *);
extern void func_020f9e00(void *);
extern void func_020f9b50(void *, int);
extern int func_020f9948(void *);
extern void func_020f9fcc(void *, int);
extern int NNS_SndPlayerReadGlobalVariable(int, short *);
extern short data_021fd26c;

struct UnkStruct_020f9ea4 {
    unsigned char pad_00[8];
    unsigned char mode;
    unsigned char pad_09[2];
    signed char sbyte;
};

int func_020f9ea4(struct UnkStruct_020f9ea4 *obj, int arg2)
{
    int result = -0x1000;

    switch (obj->mode) {
        case 0:
            break;

        case 1:
            func_020f9d00(obj);
            func_020f9e00(obj);
            func_020f9b50(obj, arg2);
            result = func_020f9948(obj);
            break;

        case 2: {
            short var;

            NNS_SndPlayerReadGlobalVariable(2, &var);
            data_021fd26c = var;
            if (var == obj->sbyte) {
                func_020f9fcc(obj, 1);
            }
            break;
        }
    }

    return result;
}
