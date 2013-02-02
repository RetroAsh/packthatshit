#include <stdio.h>
#include <stdlib.h>
#include <pestruct.h>
#include <peviewer.h>

/*! \arg \c filename name of the PE file
 * \returns 1 if the file is a correct PE one, 0 otherwise
 */
int is_pe(const char *filename)
{
    FILE *pe_file = NULL;
    unsigned int signature = 0;
    int res = 0;
    PIMAGE_DOS_HEADER dos_header = NULL;

    pe_file = fopen(filename, "rb");

    /* Check if the file has been correctly opened */
    if (pe_file == NULL)
    {
        printf("error: cannot open the file\n");
        exit(-1);
    }

    dos_header = (PIMAGE_DOS_HEADER)calloc(1, sizeof(IMAGE_DOS_HEADER));
    /* Read the image dos header of the file */
    fgets((void *)dos_header, sizeof(IMAGE_DOS_HEADER), pe_file);
    /* Check the magic number of the file */
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
    {
        printf("error: not a valid PE file\n");
        exit(-1);
    }
    fseek(pe_file, dos_header->e_lfanew, SEEK_SET);
    /* Check the signature number of the file */
    fgets((void *)&signature, sizeof(unsigned int), pe_file);
    res = (signature == IMAGE_NT_SIGNATURE) ? 1 : 0;

    free(dos_header);
    fclose(pe_file);
    return res;
}
