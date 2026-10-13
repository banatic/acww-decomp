/* func_02062d7c @ 0x02062d7c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x1c];
} UnkStruct_02062d7c;

extern void func_0206e8c4(void *);

UnkStruct_02062d7c *func_02062d7c(UnkStruct_02062d7c *self)
{
    func_0206e8c4(&self[0]);
    func_0206e8c4(&self[1]);
    func_0206e8c4(&self[2]);
    func_0206e8c4(&self[3]);
    return self;
}
