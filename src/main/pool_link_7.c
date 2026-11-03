/* pool_link_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082eec @ 0x02082eec, 0x18 bytes, Thumb
 * func_02082ed4 @ 0x02082ed4, 0x18 bytes, Thumb
 * func_02082eb4 @ 0x02082eb4, 0x20 bytes, Thumb
 */

typedef struct {
    void *vtable;
} UnkStruct_02082eb4;

extern void func_02083100(void *p);
extern void func_020830d0(void *);
extern char data_020e1a54[];
extern void func_020edb3c(void *this);

void *func_02082eec(void *param)
{
    func_02083100(param);
    *(void **) param = ((char *) data_020e1a54);
    return param;
}

void *func_02082ed4(void *obj)
{
    *(char **) obj = data_020e1a54;
    func_020830d0(obj);
    return obj;
}

UnkStruct_02082eb4 *func_02082eb4(UnkStruct_02082eb4 *this)
{
    this->vtable = ((UnkStruct_02082eb4 *) data_020e1a54);
    func_020830d0(this);
    func_020edb3c(this);
    return this;
}
