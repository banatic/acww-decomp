/* func_0203248c @ 0x0203248c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x2c];
    int unk_30;
    unsigned char pad_34[0x2c];
    int unk_60;
} UnkStruct_0203248c;

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern void func_0202f2f0(void *);
extern void func_020012dc(void *);

extern unsigned char data_020da1b4[];

UnkStruct_0203248c *func_0203248c(UnkStruct_0203248c *param)
{
    param->unk_00 = (void *) data_020da1b4;
    __cxa_vec_cleanup((void *) (&param->unk_60), 4, 8, (void (*)(void *)) func_0202f2f0);
    __cxa_vec_cleanup((void *) (&param->unk_30), 4, 0xc, (void (*)(void *)) func_020012dc);
    return param;
}
