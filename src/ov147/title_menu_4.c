/* title_menu_4: 4 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_02299ae8 @ 0x02299ae8, 0x18 bytes, Thumb
 * func_ov147_02299ad0 @ 0x02299ad0, 0x18 bytes, Thumb
 * func_ov147_02299ab0 @ 0x02299ab0, 0x20 bytes, Thumb
 * func_ov147_02299aac @ 0x02299aac, 0x4 bytes, Thumb
 */

extern void *func_02066a30(void *p);
extern char data_ov147_0229aae4[];
extern void *func_02066994(void *);
extern void func_020edb3c(void *);

void *func_ov147_02299ae8(void *p)
{
    func_02066a30(p);
    *(void **) p = data_ov147_0229aae4;
    return p;
}

void *func_ov147_02299ad0(void *self)
{
    *(void **) self = ((int *) data_ov147_0229aae4);
    func_02066994(self);
    return self;
}

void *func_ov147_02299ab0(void *obj)
{
    void *p;
    p = ((char *) data_ov147_0229aae4);
    *((void **) obj) = p;
    func_02066994(obj);
    func_020edb3c(obj);
    return obj;
}

void func_ov147_02299aac(int *p0, int p1)
{
    p0[18] = p1;
}
