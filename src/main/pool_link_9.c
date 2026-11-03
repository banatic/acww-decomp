/* pool_link_9: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082fd4 @ 0x02082fd4, 0x18 bytes, Thumb
 * func_02082fbc @ 0x02082fbc, 0x18 bytes, Thumb
 * func_02082f9c @ 0x02082f9c, 0x20 bytes, Thumb
 */

typedef struct {
    void *unk_00;
} UnkStruct_02082f9c;

extern void func_02083100(void *);
extern void func_020830d0(void *obj);
extern void func_020edb3c(void *p);
extern char data_020e1a04[];

void *func_02082fd4(void *p)
{
    func_02083100(p);
    *(int *) p = (int) ((int *) data_020e1a04);
    return p;
}

void *func_02082fbc(void *obj)
{
    *(void **) obj = ((int *) data_020e1a04);
    func_020830d0(obj);
    return obj;
}

void *func_02082f9c(void *p)
{
    UnkStruct_02082f9c *s = p;
    s->unk_00 = data_020e1a04;
    func_020830d0(s);
    func_020edb3c(s);
    return s;
}
