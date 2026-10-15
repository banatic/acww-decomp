/* func_02054dd8 @ 0x02054dd8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd0dc;
extern char data_020dd0ec;
extern char data_020dd0fc;
extern void func_02056eb0(void *);
extern void *func_0205517c(void *);
extern void func_020edb3c(void *);
typedef struct {
    void *unk_00;
    char pad_04[0x98];
    void *unk_9C;
    char pad_A0[0x18];
    void *unk_B8;
} UnkStruct_02054dd8;
void *func_02054dd8(void *p)
{
    UnkStruct_02054dd8 *s = (UnkStruct_02054dd8 *) p;
    s->unk_00 = &data_020dd0dc;
    s->unk_9C = &data_020dd0ec;
    s->unk_B8 = &data_020dd0fc;
    func_02056eb0(&s->unk_B8);
    func_0205517c(p);
    func_020edb3c(p);
    return p;
}
