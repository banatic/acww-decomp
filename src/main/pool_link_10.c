/* pool_link_10: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02083050 @ 0x02083050, 0x18 bytes, Thumb
 * func_02083038 @ 0x02083038, 0x18 bytes, Thumb
 * func_02083018 @ 0x02083018, 0x20 bytes, Thumb
 */

typedef struct UnkStruct_02083038 UnkStruct_02083038;

struct UnkStruct_02083038 {
    void *unk_00;
};

typedef struct {
    void *unk_00;
} UnkStruct_02083018;

extern void func_02083100(void *arg);
extern char data_020e1a18;
extern void func_020830d0(UnkStruct_02083038 *p);
extern void func_020edb3c(UnkStruct_02083018 *);

void *func_02083050(void *arg)
{
    func_02083100(arg);
    *((void **) arg) = (void *) ((int *) &data_020e1a18);
    return arg;
}

UnkStruct_02083038 *func_02083038(UnkStruct_02083038 *p)
{
    p->unk_00 = &data_020e1a18;
    func_020830d0(p);
    return p;
}

UnkStruct_02083018 *func_02083018(UnkStruct_02083018 *self)
{
    self->unk_00 = &data_020e1a18;
    func_020830d0((UnkStruct_02083038 *) self);
    func_020edb3c(self);
    return self;
}
