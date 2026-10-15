/* func_02083898 @ 0x02083898, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020e1b1c;
extern void *func_02083910(void *);
extern void func_02083c78(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02083898;

UnkStruct_02083898 *func_02083898(UnkStruct_02083898 *param)
{
    param->unk_00 = (unsigned int) &data_020e1b1c;
    __cxa_vec_cleanup((void *) (&param->unk_08), 4, 8, (((void (*)(void *)) func_02083910)));
    func_02083c78(param);
    return param;
}
