/* The build's label (build_time.h). */
#include "build_time.h"

#include "clean.h"

/* An FSFile of the SDK's file system: only its address is used here. */
typedef struct BuildTimeFile {
    unsigned char bytes[0x4c];
} BuildTimeFile;

extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const void *path);
extern int FS_ReadFile(void *file, const void *dst, int size);
extern int FS_CloseFile(void *file);

extern const char data_020da4c4[]; /* "/BUILDTIME" */
extern unsigned char data_021c5914[BUILD_TIME_SIZE];

/* func_02037f74: the file's first 32 bytes read into data_021c5914, when it opens; left as
 * they were otherwise. */
void BuildTime_Load(void)
{
    BuildTimeFile file;

    FS_InitFile(&file);
    if (FS_OpenFile(&file, data_020da4c4) == 1) {
        FS_ReadFile(&file, data_021c5914, BUILD_TIME_SIZE);
        FS_CloseFile(&file);
    }
}
CLEAN_AS(func_02037f74, BuildTime_Load)
