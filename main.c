#include <stdio.h>
#include <stdlib.h>

char memory[8192];
typedef struct _memory_node
{
 size_t memsize;
 struct _memory_node *next;
 void *address;
} memory_node;

memory_node *free_list = (memory_node*)memory;
static int initialized=0;
void init(void)
{
    free_list->next=NULL;
    free_list->memsize=8192 - sizeof(*free_list);
    free_list->address=memory+sizeof(*free_list);
}
void *my_malloc(size_t tam)
{
    if(!initialized)
    {
        init();
        initialized=1;
    }
    while(free_list)
    {
        if(free_list->memsize<tam)
        {
            void *address = free_list->address;
            memory_node *new_node = (memory_node*)(char*)address+tam;
            new_node = free_list;
            new_node->memsize = free_list->memsize-tam;
            free_list=new_node->next;
            printf("Memoria Address: %d\n",address);
        }
        else
        {
            printf("Limite de memoria excedido\n");
            break;

        }
    printf("Memoria Asignada: %d\n",tam);
    my_free(8192);
    }
}
void my_free(void *data)
{
char *tmp = data-sizeof(memory_node);
memory_node *metadata = (memory_node*)tmp;
printf("Memoria Liberada: %d",metadata);
}
int main()
{
    my_malloc(8192);
    return 0;
}
