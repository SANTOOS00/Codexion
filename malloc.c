




#include "codexion.h"




void *mallocs(void *type)
{
    static t_malloc arry_point;
    printf("%d", sizeof(t_malloc));


}



int main()
{
    mallocs((void *)'s');
}