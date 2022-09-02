#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadtree.h"
#include <stdint.h>

int main(int argc, char *argv[])
{
    argc = argc + 1;
    FILE *input;
    input = fopen(argv[3], "rb");
    if (strstr(argv[1], "-c") != NULL)
    {
        char *ptr;
        int factor;
        factor = strtol(argv[2], &ptr, 10);
        printf("%d\n", factor);

        int height, width, elements;
        
        char *buffer;
        buffer = (char *)calloc(100, 1);

        pixel **grid;
        grid=interpret_file(input, &height, &width, &elements);
        //tre sa comprimez fiecare nod functie de parcurgere+ functie de comprimare nod

        tree_situation color_nodes;
        color_nodes.nr_colors=0;
        color_nodes.nr_nodes=0;
        TreeNode *root;
        root=create_node(NULL,grid,factor,height,0,0,&color_nodes);
        add_nodes(&root,grid,factor,height,0,0,&color_nodes);
        printf("%d %d\n",color_nodes.nr_colors,color_nodes.nr_nodes);

        FILE *output;
        output=fopen(argv[4],"wb");
        fwrite(&color_nodes,sizeof(tree_situation),1,output);
        int i=0;
        fwrite_node(output,root,&i);

        free_image(grid, height);
        free_tree(root);
        free(buffer);
        fclose(output);
        goto lala;
    }

    if (strstr(argv[1], "-d") != NULL)
    {
        printf("ai nimerit frate\n");
        goto lala;
    }

    if (strstr(argv[1], "-m") != NULL)
    {
        printf("aia e baiiii\n");
        goto lala;
    }

lala:
    fclose(input);
    return 0;
}
