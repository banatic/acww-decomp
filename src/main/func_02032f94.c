/* func_02032f94 @ 0x02032f94, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020330e8(void *);
extern void *func_02033100(void *);

typedef struct {
    int unk_00;
    char unk_04;
} UnkStruct_02032f94;

UnkStruct_02032f94 *func_02032f94(UnkStruct_02032f94 *obj)
{
    __cxa_vec_ctor((void *) (&obj->unk_04), 0x10, 0x24, (((void (*)(void *)) func_02033100)),
                   (((void (*)(void *)) func_020330e8)));
    obj->unk_00 = 0;
    return obj;
}
