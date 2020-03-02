#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ASCII_SIZE 128

typedef struct _node { //分為左節點跟右節點
    struct _node *left, *right;
    unsigned weight;
    char data;
} node_t;

typedef struct { //
    unsigned size;
    node_t *array[ASCII_SIZE];
} min_heap_t;

typedef struct { //
    int arr[ASCII_SIZE/4];
    int length;
    char data;
}pair_t;

static void swap_node(node_t **a, node_t **b) {
    node_t *t = *a;
    *a = *b;
    *b = t;
}

static void shift_up_2(min_heap_t *heap) {
    int i = 0;
    while(i<heap->size) {
        (heap->array)[i] = (heap->array)[i+2];
        (heap->array)[i+1] = (heap->array)[i+3];
        i++;
    }
    heap->size -= 2;
}

static void add_to_heap(node_t *to, min_heap_t *heap) {
    int pos = heap->size++;
    heap->array[pos] = to;
    if (heap->size > 2) {
        while ((heap->array[pos -1])->weight > (heap->array[pos])->weight) {
            swap_node(&(heap->array[pos-1]), &(heap->array[pos]));
            if(--pos == 0)
                break;
        }
    }
}

static node_t *combine_node_ts(node_t *lighter, node_t *heavier) {
    node_t *new_node = calloc(1,sizeof(node_t));
    new_node->left = lighter;
    new_node->right = heavier;
    new_node->weight = lighter->weight + heavier->weight;
    return new_node;
    
}

static node_t *bulid_hufftree(min_heap_t *heap) {
    while (heap->size > 1) {
        add_to_heap(combine_node_ts(heap->array[0],heap->array[1]),heap);
        shift_up_2(heap);
    }
    return heap->array[0];
    
}

void encode(FILE *in, FILE *out, pair_t *pairs) {
    int curr_size = 0;
    unsigned buffer = 0;
    
    for(;;) {
        int ch = fgetc(in);
        if(ch == EOF)
            break;
        int i = 0;
        
        while (i++ < pairs[ch].length) {
            buffer <<= 1;
            buffer += (pairs[ch].arr)[i];
            curr_size++;
            if(curr_size == 8) {
                fwrite(&buffer, 1, 1, out);
                curr_size = 0;
                buffer = 0;
            }
            i++;
        }
    }
    
    while(curr_size < 0) {
        buffer <<= 1;
        curr_size++;
    }
    
    rewind(in);
    fwrite(&buffer, 1, 1, out);
    fclose(out);
}

void bulid_pairings(node_t *root, int arr[], int top, pair_t *pairs) {
    if(root->left) {
        arr[top] = 0;
        bulid_pairings(root->left, arr, top + 1, pairs);
    }
    if(root->right) {
        arr[top] = 1;
        bulid_pairings(root->right, arr, top + 1, pairs);
    }
    if(!(root->left) && !(root->right)) {
        uint8_t index = root->data;
        printf("%c : ",root->data);
        for(int i = 0; i < top; i++) {
            pairs[index].arr[i] = arr[i];
            printf("%d", arr[i]);
        }
        printf("\n");
        pairs[index].length = top;
        pairs[index].data = root->data;
    }
}

min_heap_t *scan_file(FILE *in) {
    node_t *dictionary = calloc(ASCII_SIZE, sizeof(node_t));
    min_heap_t *heap = calloc(1, sizeof(min_heap_t));
    int ch;
    
    for (;;) {
        if ((ch = fgetc(in)) == EOF)
            break;
        dictionary[ch].weight++;
    }
    
    for (ch = 0; ch < ASCII_SIZE; ch++) {
        if (dictionary[ch].weight == 0)
            continue;
        dictionary[ch].data = ch;
        add_to_heap(&(dictionary[ch]), heap);
    }
    
    rewind(in);
    return heap;
}

int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        printf("Usage: %s <input file>\n", "code.txt");
        return -1;
    }
    
    FILE *in = fopen("code.txt", "r");
    FILE *out = fopen("com.txt", "wb");
    int arr[ASCII_SIZE];
    
    min_heap_t *data_heap = scan_file(in);
    pair_t *pairs = calloc(ASCII_SIZE, sizeof(pair_t));
    bulid_pairings(bulid_hufftree(data_heap), arr, 0, pairs);
    
    printf("Compressing...\n");
    encode(in, out, pairs);    
    
    FILE *read_out = fopen("com.txt", "r");
    fseek(in, 0L, SEEK_END);
    fseek(read_out, 0L, SEEK_END);
    int before = ftell(in);
    int after = ftell(read_out);
    
    double efficiency = 100 - (((double) after / (double) before) * 100);
    printf("AChieved %f %% Compression.\n", efficiency);
    
    fclose(read_out);
    fclose(in);
    free(data_heap);
    free(pairs);
    return 0;
}