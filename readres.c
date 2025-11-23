#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file.res>\n", argv[0]);
        exit(1);
    }
    
    // Open the first file
    FILE* fptr1 = fopen(argv[1], "rb");
    if (!fptr1)
    {
        fprintf(stderr, "Error: Could not open %s\n", argv[1]);
        exit(1);
    }
    
    // Get size of first file
    fseek(fptr1, 0, SEEK_END);
    uint32_t sz1 = ftell(fptr1);
    fseek(fptr1, 0, SEEK_SET);
    
    // Construct the answer filename
    char answer_filename[256];
    strcpy(answer_filename, argv[1]);
    
    // Find the last occurrence of ".res" and insert "Answer" before it
    char* dot_pos = strstr(answer_filename, ".res");
    if (dot_pos)
    {
        // Shift the ".res" part to make room for "Answer"
        memmove(dot_pos + 6, dot_pos, strlen(dot_pos) + 1);
        memcpy(dot_pos, "Answer", 6);
    }
    
    // Try to open the answer file
    FILE* fptr2 = fopen(answer_filename, "rb");
    uint32_t sz2 = 0;
    int has_answer = 0;
    
    if (fptr2)
    {
        has_answer = 1;
        fseek(fptr2, 0, SEEK_END);
        sz2 = ftell(fptr2);
        fseek(fptr2, 0, SEEK_SET);
        printf("Comparing %s with %s\n\n", argv[1], answer_filename);
    }
    else
    {
        printf("Answer file not found, showing %s only\n\n", argv[1]);
    }
    
    // Compare line by line
    uint32_t line = 0;
    uint32_t differences = 0;
    uint32_t reg1, reg2;
    
    while (line < sz1/4 || (has_answer && line < sz2/4))
    {
        int has_reg1 = (line < sz1/4) && (fread(&reg1, sizeof(uint32_t), 1, fptr1) == 1);
        int has_reg2 = has_answer && (line < sz2/4) && (fread(&reg2, sizeof(uint32_t), 1, fptr2) == 1);
        
        if (has_answer)
        {
            if (has_reg1 && has_reg2)
            {
                if (reg1 == reg2)
                {
                    printf("line %d: %08x [MATCH]\n", line, reg1);
                }
                else
                {
                    printf("line %d: %08x vs %08x [DIFFER]\n", line, reg1, reg2);
                    differences++;
                }
            }
            else if (has_reg1 && !has_reg2)
            {
                printf("line %d: %08x vs [MISSING] [DIFFER]\n", line, reg1);
                differences++;
            }
            else if (!has_reg1 && has_reg2)
            {
                printf("line %d: [MISSING] vs %08x [DIFFER]\n", line, reg2);
                differences++;
            }
        }
        else
        {
            if (has_reg1)
            {
                printf("line %d: %08x\n", line, reg1);
            }
        }
        
        line++;
    }
    
    if (has_answer)
    {
        printf("\n");
        if (differences == 0)
        {
            printf("All lines match! ✓\n");
        }
        else
        {
            printf("Found %u difference(s)\n", differences);
        }
    }
    
    fclose(fptr1);
    if (fptr2) fclose(fptr2);
    
    return 0;
}
