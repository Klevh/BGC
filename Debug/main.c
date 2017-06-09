#include "../BGC.h"

/* for test purpose only, do not touch _BGCollector manually if you are not sure of what you are doing */
void displayBGC(){
  cell_t * current = _BGCollector;

  while(current){
    printf("cell of size %lu : %p\n",current->size,current->object);
    current=current->next;
  }
}

int main(){
  int * tab1 = mallocBGC(3*sizeof(*tab1));
  int   i;

  for(i=0;i<3;++i){
    tab1[i]=i;
  }

  printf("My variable is %p of size %lu\n",(void*)tab1,3*sizeof(*tab1));
  displayBGC();
  putchar('\n');

  /* adding lots of variables */
  for(i = 0;i < 10; ++i){
    printf("Adding of size %lu : %p\n",i*sizeof(int),callocBGC(i,sizeof(int)));
  }
  putchar('\n');
  
  /* realloc then removing tab1 */
  tab1=reallocBGC(tab1,12*sizeof(int));
  printf("Realloc tab1 result : %p\n",(void*)tab1);
  printf("Removing first variable (%p) : 0 == %d\n",(void*)tab1,freeBGC(tab1));
  putchar('\n');
  
  /* display result */
  displayBGC();
  putchar('\n');

  /* clean BGC */
  puts("Cleaning ...");
  cleanBGC();
  puts("BGC result (nothing is expected, something is bad) :");
  displayBGC();

  return 0;
}
