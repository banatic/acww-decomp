/* func_02082f9c @ 0x02082f9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_02082f9c;

extern void func_020830d0(void *p);
extern void func_020edb3c(void *p);
extern char data_020e1a04[];

void *func_02082f9c(void *p)
{
    UnkStruct_02082f9c *s = p;
    s->unk_00 = data_020e1a04;
    func_020830d0(s);
    func_020edb3c(s);
    return s;
}
