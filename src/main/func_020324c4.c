/* func_020324c4 @ 0x020324c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f2f0(void *);
extern void func_020012dc(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

typedef struct {
    unsigned int unk_00;
    char pad_04[0x30 - 0x4];
    char unk_30[0x30];
    char unk_60;
} UnkStruct_020324c4;

extern unsigned char data_020da1b4[];

UnkStruct_020324c4 *func_020324c4(UnkStruct_020324c4 *param)
{
    param->unk_00 = (unsigned int) data_020da1b4;
    __cxa_vec_cleanup((void *) (&param->unk_60), 4, 8, (void (*)(void *)) func_0202f2f0);
    __cxa_vec_cleanup((void *) (&param->unk_30), 4, 12, (void (*)(void *)) func_020012dc);
    return param;
}
