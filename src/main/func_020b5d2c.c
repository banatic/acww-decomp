/* func_020b5d2c @ 0x020b5d2c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
#pragma thumb

typedef union {
    int a;
    int b;
    int c;
} UnkStruct_020b5d2c;

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5574[];

void *func_020b5d2c(void *obj)
{
    UnkStruct_020b5d2c *u = (UnkStruct_020b5d2c *) obj;
    u->a = (unsigned int) data_020e5574;
    u->b = (unsigned int) data_020e3c94;
    u->c = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
