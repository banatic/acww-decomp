/* pool_link_12: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02083100 @ 0x02083100, 0x10 bytes, Thumb
 * func_020830f4 @ 0x020830f4, 0xc bytes, Thumb
 * func_020830dc @ 0x020830dc, 0x18 bytes, Thumb
 * func_020830d0 @ 0x020830d0, 0xc bytes, Thumb
 */

struct UnkStruct_02083100 {
    void *unk_00;
    char unk_04;
};

extern void func_020edb3c(void *object);
extern unsigned char data_020e1a2c[];

void func_02083100(struct UnkStruct_02083100 *param)
{
    param->unk_00 = ((char *) data_020e1a2c);
    param->unk_04 = -1;
}

void func_020830f4(void **ptr)
{
    *ptr = ((char *) data_020e1a2c);
}

void *func_020830dc(void *object)
{
    *((unsigned int *) object) = (unsigned int) data_020e1a2c;
    func_020edb3c(object);
    return object;
}

void func_020830d0(char **ptr)
{
    *ptr = ((char *) data_020e1a2c);
}
