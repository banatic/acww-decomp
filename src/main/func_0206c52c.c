/* func_0206c52c @ 0x0206c52c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2c];
    char *ptr;
} Self_0206c52c;

typedef struct {
    unsigned char pad_00[0x284];
} Chunk_0206c52c;

extern void func_0206d420(void *self, void *addr);

void func_0206c52c(Self_0206c52c *self)
{
    Chunk_0206c52c *p = (Chunk_0206c52c *) (self->ptr + 0x14b8);
    func_0206d420(self, p + 1);
}
