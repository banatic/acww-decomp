/* func_ov079_02278ac4 @ 0x02278ac4, 0x68 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_020160b4(void *arg);
extern int func_020ab504(int value);
extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *arg, int);
extern void func_ov079_02279518(void *arg, int);
extern void func_0206844c(void *, char *, void *);
extern int func_ov079_022794fc(int argument0, int argument1);
extern char data_ov079_0227a1b0;

typedef struct {
    char pad_00[0x1E];
    unsigned char unk_1E;
    char pad_1F[0x21];
    void *unk_40;
} UnkStruct_02278ac4;

void func_ov079_02278ac4(UnkStruct_02278ac4 *arg)
{
    int result;
    void *p;
    int r4;
    unsigned char field;
    char local;

    result = func_020ab504(func_020160b4(arg));
    p = &data_ov079_0227a1b0;
    r4 = 0xFF;
    field = arg->unk_1E;

    switch (field) {
        case 0:
            if (result == 0) {
                func_020157d4(arg, (unsigned int) func_ov079_022794fc, 0xD, 1);
                func_02015828(arg, 0);
                func_ov079_02279518(arg, 0);
            }
            break;
        case 4:
            if (result == 0) {
                r4 = 0x0E;
            }
            break;
    }

    if (r4 != 0xFF) {
        local = (char) r4;
        func_0206844c(arg->unk_40, &local, p);
    }
}
