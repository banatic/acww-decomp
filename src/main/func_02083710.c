/* func_02083710 @ 0x02083710, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1ae4;
extern int func_020837d0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083c78(void *ptr);
extern void func_020edb3c(void *ptr);

typedef struct UnkStruct_02083710 {
    void *unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02083710;

UnkStruct_02083710 *func_02083710(UnkStruct_02083710 *this)
{
    this->unk_00 = &data_020e1ae4;
    __cxa_vec_cleanup((void *) (&this->unk_08), 5, 2, (((void (*)(void *)) func_020837d0)));
    func_02083c78(this);
    func_020edb3c(this);
    return this;
}
