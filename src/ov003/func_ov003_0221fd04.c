/* func_ov003_0221fd04 @ 0x0221fd04, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02239a58[];
extern char data_020da13c[];

extern void func_ov003_0221ef78(void *);
extern void *func_02057694(void *);
extern int func_ov003_0221f1f4(void *);
extern void *func_ov003_0221f5f4(void *);
extern void func_020ee62c(void *);

struct UnkStruct_0221fd04 {
    void *head;
};

struct UnkStruct_0221fd04 *func_ov003_0221fd04(struct UnkStruct_0221fd04 *self)
{
    self->head = data_ov003_02239a58;
    func_ov003_0221ef78((char *) self + 0x310);
    func_02057694((char *) self + 0x280);
    func_02057694((char *) self + 0x1f0);
    func_ov003_0221f1f4((char *) self + 0x150);
    func_ov003_0221f5f4((char *) self + 0x54);
    self->head = data_020da13c;
    func_020ee62c(self);
    return self;
}
