/* func_02083b3c @ 0x02083b3c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02083b3c;

extern unsigned int data_020e1b54;
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02083bac(void);
extern void func_02083c78(void *);

UnkStruct_02083b3c *func_02083b3c(UnkStruct_02083b3c *obj)
{
    obj->unk_00 = &data_020e1b54;
    __cxa_vec_cleanup(&obj->unk_08, 5, 4, func_02083bac);
    func_02083c78(obj);
    return obj;
}
