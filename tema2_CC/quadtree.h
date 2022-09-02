#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct QuadtreeNode
{
    unsigned char blue, green, red;
    int32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) QuadtreeNode;

typedef struct TreeNode
{
    QuadtreeNode node;
    struct TreeNode *NV, *NE, *SV, *SE, *parent;
} TreeNode;

typedef struct pixel
{
    unsigned char RED, GREEN, BLUE;
} pixel;

typedef struct tree_situation
{
    int nr_colors;
    int nr_nodes;
} tree_situation;

pixel **interpret_file(FILE *input, int *height, int *width, int *elements)
{
    int i, j;
    char *buffer;
    buffer = (char *)calloc(20, 1);
    char *ptr;
    fread(buffer, 2, 1, input);
    fread(buffer, 4, 1, input);
    *height = strtol(buffer, &ptr, 10);
    fread(buffer, 4, 1, input);
    *width = strtol(buffer, &ptr, 10);
    fread(buffer, 5, 1, input);
    *elements = strtol(buffer, &ptr, 10);

    pixel **grid;
    grid = (pixel **)malloc(*height * sizeof(pixel *));
    for (i = 0; i < *height; i++)
    {
        grid[i] = (pixel *)calloc(*width, sizeof(pixel));
    }

    for (i = 0; i < *height; i++)
    {
        for (j = 0; j < *width; j++)
        {
            fread(buffer, 3, 1, input);
            grid[i][j].RED = (unsigned char)buffer[0];
            grid[i][j].GREEN = (unsigned char)buffer[1];
            grid[i][j].BLUE = (unsigned char)buffer[2];
        }
    }

    free(buffer);
    return grid;
}

void free_image(pixel **grid, int height)
{
    int i;
    for (i = 0; i < height; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

pixel get_RGB(pixel **grid, int size, int x_start, int y_start)
{
    pixel med_RGB;
    long long int mean_red = 0, mean_green = 0, mean_blue = 0;
    int i, j;
    for (i = x_start; i < x_start + size; i++)
    {
        for (j = y_start; j < y_start + size; j++)
        {
            mean_red = mean_red + grid[i][j].RED;
            mean_green = mean_green + grid[i][j].GREEN;
            mean_blue = mean_blue + grid[i][j].BLUE;
        }
    }
    med_RGB.RED = mean_red / (size * size);
    med_RGB.RED = (unsigned char)med_RGB.RED;
    med_RGB.GREEN = mean_green / (size * size);
    med_RGB.GREEN = (unsigned char)med_RGB.GREEN;
    med_RGB.BLUE = mean_blue / (size * size);
    med_RGB.BLUE = (unsigned char)med_RGB.BLUE;
    return med_RGB;
}

int mean(pixel **grid, int size, int x_start, int y_start)
{
    pixel med_RGB = get_RGB(grid, size, x_start, y_start);

    long long int mean = 0;
    long long int help_mean = 0;
    int i, j;
    for (i = x_start; i < x_start + size; i++)
    {
        for (j = y_start; j < y_start + size; j++)
        {
            help_mean = help_mean + (med_RGB.RED - grid[i][j].RED) * (med_RGB.RED - grid[i][j].RED) + (med_RGB.GREEN - grid[i][j].GREEN) * (med_RGB.GREEN - grid[i][j].GREEN) + (med_RGB.BLUE - grid[i][j].BLUE) * (med_RGB.BLUE - grid[i][j].BLUE);
        }
        help_mean = help_mean / size / 3;
        mean = mean + help_mean;
    }
    mean = mean / size;
    return mean;
}

TreeNode *create_node(TreeNode **parent, pixel **grid, int factor, int size,
                      int x_start, int y_start, tree_situation *color_nodes)
{
    TreeNode *new;
    new = (TreeNode *)malloc(sizeof(TreeNode));
    pixel med_RGB = get_RGB(grid, size, x_start, y_start);
    new->node.blue = med_RGB.BLUE;
    new->node.red = med_RGB.RED;
    new->node.green = med_RGB.GREEN;
    new->node.area = size *size;
    if (mean(grid, size, x_start, y_start) > factor)
    {
        new->node.top_left = color_nodes->nr_colors + 1;
        new->node.top_right = color_nodes->nr_colors + 2;
        new->node.bottom_left = color_nodes->nr_colors + 3;
        new->node.bottom_right = color_nodes->nr_colors + 4;
        color_nodes->nr_colors = color_nodes->nr_colors + 4;
    }
    else
    {
        new->node.top_left = -1;
        new->node.top_right = -1;
        new->node.bottom_left = -1;
        new->node.bottom_right = -1;
    }
    new->NV = NULL;
    new->NE = NULL;
    new->SV = NULL;
    new->SE = NULL;
    color_nodes->nr_nodes = color_nodes->nr_nodes + 1;
    new->parent = (TreeNode *)parent;
    new->node.area=size*size;
    return new;
}

void free_tree(TreeNode *root)
{
    if(root==NULL)
    {
        return;
    }
    free_tree(root->NV);
    free_tree(root->NE);
    free_tree(root->SE);
    free_tree(root->SV);
    free(root);
}

void add_nodes(TreeNode **root, pixel **grid, int factor, int size, int x_start, int y_start, tree_situation *color_nodes)
{
    if ((*root)->node.top_left != -1 && (*root)->node.top_right != -1)
    {
        (*root)->NV = create_node(root, grid, factor, size / 2, x_start, y_start, color_nodes);
        (*root)->NE = create_node(root, grid, factor, size / 2, x_start + size / 2, y_start, color_nodes);
        (*root)->SV = create_node(root, grid, factor, size / 2, x_start, y_start + size / 2, color_nodes);
        (*root)->SE = create_node(root, grid, factor, size / 2, x_start + size / 2, y_start + size / 2, color_nodes);
    }
    else
    {
        return;
    }
    add_nodes(&(*root)->NV, grid, factor, size / 2, x_start, y_start, color_nodes);
    add_nodes(&(*root)->NE, grid, factor, size / 2, x_start + size / 2, y_start, color_nodes);
    add_nodes(&(*root)->SV, grid, factor, size / 2, x_start, y_start + size / 2, color_nodes);
    add_nodes(&(*root)->SE, grid, factor, size / 2, x_start + size / 2, y_start + size / 2, color_nodes);
}

void fwrite_node(FILE *output, TreeNode *Tree_node,int *nr_node)
{
    fwrite(&Tree_node->node.blue,1,1,output);
    fwrite(&Tree_node->node.green,1,1,output);
    fwrite(&Tree_node->node.red,1,1,output);
    fwrite(nr_node,4,1,output);
    fwrite(&Tree_node->node.area,4,1,output);
    fwrite(&Tree_node->node.top_left,4,1,output);
    fwrite(&Tree_node->node.top_right,4,1,output);
    fwrite(&Tree_node->node.bottom_right,4,1,output);
    fwrite(&Tree_node->node.bottom_left,4,1,output);
    *nr_node=*nr_node+1; 
}
