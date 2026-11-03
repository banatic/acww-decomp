/* pool_link_6: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082e78 @ 0x02082e78, 0x18 bytes, Thumb
 * func_02082e60 @ 0x02082e60, 0x18 bytes, Thumb
 * func_02082e40 @ 0x02082e40, 0x20 bytes, Thumb
 */

struct UnkStruct_02082e40 {
    void *unk_00;
};

extern void func_02083100(void *arg);
extern void func_020830d0(void *obj);
extern char data_020e1a7c[];
extern void func_020edb3c(struct UnkStruct_02082e40 *p);

void *func_02082e78(void *this)
{
    func_02083100(this);
    *(void **) this = (void *) ((char *) data_020e1a7c);
    return this;
}

void *func_02082e60(void *obj)
{
    *(void **) obj = data_020e1a7c;
    func_020830d0(obj);
    return obj;
}

struct UnkStruct_02082e40 *func_02082e40(struct UnkStruct_02082e40 *p)
{
    p->unk_00 = ((char *) data_020e1a7c);
    func_020830d0((void *) p);
    func_020edb3c(p);
    return p;
}
