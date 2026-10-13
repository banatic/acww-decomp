/* func_0206cc2c @ 0x0206cc2c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020679fc(void *state);
extern void func_020a9334(void *self, int result);
extern void func_020a7994(void *addr, int result);

typedef int (*Method)(void *);

typedef struct {
    void *vptr;
} Obj1;

typedef struct {
    unsigned char pad_00[0x1a58];
    unsigned char unk_1A58[4];
    unsigned char pad_mid[4];
    int unk_1A60;
    unsigned char pad_1A64[0x1cac - (0x1a60 + 4)];
    Obj1 obj_1cac;
} State;

typedef struct {
    unsigned char pad_00[0x2c];
    State *state;
} SelfType;

void func_0206cc2c(SelfType *self)
{
    int result1;
    int result2;
    func_020679fc(self->state);
    result1 = ((Method *) self->state->obj_1cac.vptr)[3](&self->state->obj_1cac);
    func_020a9334(self, result1);
    result2 = ((Method *) self->state->obj_1cac.vptr)[3](&self->state->obj_1cac);
    func_020a7994(&self->state->unk_1A58, result2);
    self->state->unk_1A60 = 0;
}
