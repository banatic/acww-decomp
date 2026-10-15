/* func_02083328 @ 0x02083328, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1b38;
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083c78(void *ptr);
extern void func_020edb3c(void *ptr);
extern int func_020833d4(void *);

struct UnkStruct_02083328 {
    void *unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned char unk_08;
};

struct UnkStruct_02083328 *func_02083328(struct UnkStruct_02083328 *obj)
{
    obj->unk_00 = (void *) &data_020e1b38;
    __cxa_vec_cleanup((void *) (&obj->unk_08), 5, 2, (((void (*)(void *)) func_020833d4)));
    func_02083c78(obj);
    func_020edb3c(obj);
    return obj;
}
