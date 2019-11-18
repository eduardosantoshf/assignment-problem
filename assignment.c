////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AED, 2019/2020
//
// Pedro Bastos 93150
// Eduardo Santos 93107
// José Vaz 88903
//
// Brute-force solution of the assignment problem (https://en.wikipedia.org/wiki/Assignment_problem)
//
// Compile with "cc -Wall -O2 assignment.c -lm" or equivalent
//
// In the assignment problem we will solve here we have n agents and n tasks; assigning agent
//   a
// to task
//   t
// costs
//   cost[a][t]
// The goal of the problem is to assign one agent to each task such that the total cost is minimized
// The total cost is the sum of the costs
//
// Things to do:
//   0. (mandatory)
//      Place the student numbers and names at the top of this file   [DONE]
//   1. (highly recommended)
//      Read and understand this code [DONE]
//   2. (mandatory)
//      Modify the function generate_all_permutations to solve the assignment problem [DONE]
//      Compute the best and worst solutions for all problems with sizes n=2,...,14 and for each
//      student number of the group  
//   3. (mandatory)
//      Calculate and display an histogram of the number of occurrences of each cost [DONE]
//      Does it follow approximately a normal distribution?
//      Note that the maximum possible cost is n * t_range
//   4. (optional)
//      For each problem size, and each student number of the group, generate one million (or more!)
//      random permutations and compute the best and worst solutions found in this way; compare
//      these solutions with the ones found in item 2
//      Compare the histogram computed in item 3 with the histogram computed using the random
//      permutations
//   5. (optional)
//      Try to improve the execution time of the program (use the branch-and-bound technique)
//   6. (optional)
//      Surprise us, by doing something more!
//   7. (mandatory)
//      Write a report explaining what you did and presenting your results
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//#define NDEBUG  // uncomment to skip disable asserts (makes the code slightly faster)
#include <assert.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// problem data
//
// max_n ........ maximum problem size
// cost[a][t] ... cost of assigning agent a to task t
//

//
// if your compiler complains about srandom() and random(), replace #if 0 by #if 1
//
#if 0
# define srandom srand
# define random  rand
#endif

#define max_n    32           // do not change this (maximum number of agents, and tasks)
#define range    20           // do not change this (for the pseudo-random generation of costs)
#define t_range  (3 * range)  // do not change this (maximum cost of an assignment)

static int cost[max_n][max_n];
static int seed; // place a student number here!

static void init_costs(int n)
{
  if(n == -3)
  { // special case (example for n=3)
    cost[0][0] = 3; cost[0][1] = 8; cost[0][2] = 6;
    cost[1][0] = 4; cost[1][1] = 7; cost[1][2] = 5;
    cost[2][0] = 5; cost[2][1] = 7; cost[2][2] = 5;
    return;
  }
  if(n == -5)
  { // special case (example for n=5)
    cost[0][0] = 27; cost[0][1] = 27; cost[0][2] = 25; cost[0][3] = 41; cost[0][4] = 24;
    cost[1][0] = 28; cost[1][1] = 26; cost[1][2] = 47; cost[1][3] = 38; cost[1][4] = 21;
    cost[2][0] = 22; cost[2][1] = 48; cost[2][2] = 26; cost[2][3] = 14; cost[2][4] = 24;
    cost[3][0] = 32; cost[3][1] = 31; cost[3][2] =  9; cost[3][3] = 41; cost[3][4] = 36;
    cost[4][0] = 24; cost[4][1] = 34; cost[4][2] = 30; cost[4][3] = 35; cost[4][4] = 45;
    return;
  }
  assert(n >= 1 && n <= max_n);
  srandom((unsigned int)seed * (unsigned int)max_n + (unsigned int)n);
  for(int a = 0;a < n;a++)
    for(int t = 0;t < n;t++)
      cost[a][t] = 3 + (random() % range) + (random() % range) + (random() % range); // [3,3*range]
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// code to measure the elapsed time used by a program fragment (an almost copy of elapsed_time.h)
//
// use as follows:
//
//   (void)elapsed_time();
//   // put your code to be time measured here
//   dt = elapsed_time();
//   // put morecode to be time measured here
//   dt = elapsed_time();
//
// elapsed_time() measures the CPU time between consecutive calls
//

#if defined(__linux__) || defined(__APPLE__)

//
// GNU/Linux and MacOS code to measure elapsed time
//

#include <time.h>

static double elapsed_time(void)
{
  static struct timespec last_time,current_time;

  last_time = current_time;
  if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&current_time) != 0)
    return -1.0; // clock_gettime() failed!!!
  return            ((double)current_time.tv_sec - (double)last_time.tv_sec)
         + 1.0e-9 * ((double)current_time.tv_nsec - (double)last_time.tv_nsec);
}

#endif

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)

//
// Microsoft Windows code to measure elapsed time
//

#include <windows.h>

static double elapsed_time(void)
{
  static LARGE_INTEGER frequency,last_time,current_time;
  static int first_time = 1;

  if(first_time != 0)
  {
    QueryPerformanceFrequency(&frequency);
    first_time = 0;
  }
  last_time = current_time;
  QueryPerformanceCounter(&current_time);
  return (double)(current_time.QuadPart - last_time.QuadPart) / (double)frequency.QuadPart;
}

#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// function to generate a pseudo-random permutation
//

void random_permutation(int n,int t[n])
{
  assert(n >= 1 && n <= 1000000);
  for(int i = 0;i < n;i++)
    t[i] = i;
  for(int i = n - 1;i > 0;i--)
  {
    int j = (int)floor((double)(i + 1) * (double)random() / (1.0 + (double)RAND_MAX)); // range 0..i
    assert(j >= 0 && j <= i);
    int k = t[i];
    t[i] = t[j];
    t[j] = k;

  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// place to store best and worst solutions (also code to print them)
//

static int min_cost,min_cost_assignment[max_n]; // smallest cost information
static int max_cost,max_cost_assignment[max_n]; // largest cost information
static long n_visited; // number of permutations visited (examined)
static int histogram[max_n*t_range];// place your histogram global variable here
static double cpu_time;

#define minus_inf  -1000000000  // a very small integer
#define plus_inf   +1000000000  // a very large integer

#include <string.h>

static void reset_solutions(void)
{
  min_cost = plus_inf;
  max_cost = minus_inf;
  n_visited = 0l;
  memset(histogram, 0, max_n*t_range*sizeof(histogram[0])); // place your histogram initialization code here
  cpu_time = 0.0;
}

static void reset_solutions_without_histogram(void)
{
  min_cost = plus_inf;
  max_cost = minus_inf;
  n_visited = 0l;
  cpu_time = 0.0;
}

#define show_info_1        (1 << 0)
#define show_info_2        (1 << 1)
#define show_costs         (1 << 2)
#define show_min_solution  (1 << 3)
#define show_max_solution  (1 << 4)
#define show_histogram     (1 << 5)
#define show_all           (0xFFFF)

static void show_solutions(int n,char *header,int what_to_show)
{
  printf("%s\n",header);
  if((what_to_show & show_info_1) != 0)
  {
    printf("  seed .......... %d\n",seed);
    printf("  n ............. %d\n",n);
  }
  if((what_to_show & show_info_2) != 0)
  {
    printf("  visited ....... %ld\n",n_visited);
    printf("  cpu time ...... %.3fs\n",cpu_time);
  }
  if((what_to_show & show_costs) != 0)
  {
    printf("  costs .........");
    for(int a = 0;a < n;a++)
    {
      for(int t = 0;t < n;t++)
        printf(" %2d",cost[a][t]);
      printf("\n%s",(a < n - 1) ? "                 " : "");
    }
    printf("\n");
  }
  if((what_to_show & show_min_solution) != 0)
  {
    printf("  min cost ...... %d\n",min_cost);
    if(min_cost != plus_inf)
    {
      printf("  assignement ...");
      for(int i = 0;i < n;i++)
        printf(" %d",min_cost_assignment[i]);
      printf("\n");
    }
  }
  if((what_to_show & show_max_solution) != 0)
  {
    printf("  max cost ...... %d\n",max_cost);
    if(max_cost != minus_inf)
    {
      printf("  assignement ...");
      for(int i = 0;i < n;i++)
        printf(" %d",max_cost_assignment[i]);
      printf("\n");
    }
    printf("\n");
  }
  if((what_to_show & show_histogram) != 0)
  {
    printf("  histogram  .... ");
    for(int i=min_cost; i <= max_cost; i++){
      printf("%s", (i != min_cost) ? "                  " : ""); // para o print ficar alinhado
      printf("[%d] = %d",i, histogram[i]);
      printf("\n");
    }
  }
}




int custo_permutacao(int n, int assignment[n]) //calcula e retorna o custo de uma permutação, dado um assignment de tamanho n
{
  int custo = 0;

  for(int i=0;i <n; i++){
    custo += cost[i][assignment[i]]; //para cada linha (cost[i]) adiciona à variável 'custo' o valor de assignment[i]
  }

  return custo;
}


void write_file(int * numOcorrencias, char *nomeFicheiro){ // escreve num ficheiro os valores do histograma

     FILE *fp;

     char *output = nomeFicheiro;
     int tamanho = sizeof(histogram)/sizeof(histogram[0]);

     int tamanho2 = max_cost - min_cost; // tamanho do array dos custos

     int custos[tamanho2];
      for(int k=0; k <= tamanho2; k++){
        custos[k] = min_cost + k; // cria o array dos custos desde o mínimo custo até ao máximo custo
      }

      int numOcorrencias_semZeros[tamanho2]; 
      int indice = 0;
      for(int i=0; i <= tamanho; i++){
        if(numOcorrencias[i] != 0 || (numOcorrencias[i] == 0 && i >min_cost && i < max_cost)){ //retira os zeros do histograma que estão fora do intervalo de custos
          numOcorrencias_semZeros[indice] = numOcorrencias[i]; 
          indice++;
        }
      }
 

     fp=fopen(output,"w");


     for(int n=0;n <= tamanho2 ;n++) {

        fprintf(fp,"%d\t%d\n", custos[n], numOcorrencias_semZeros[n]);    // escreve os 2 arrays no ficheiro, separados por tab
     }

 

     fclose(fp);

}

void write_file_custos(int * array, char *nomeFicheiro){ // escreve no ficheiro o array dos custos minimos/ máximos

     FILE *fp;

     char *output = nomeFicheiro;

     int n;

     fp=fopen(output,"w");

     for(n=0;n < 14;n++) {
     
        fprintf(fp,"%d\n", array[n]);
      
     }

     fclose(fp);

 
}

void write_file_cputime(double * array, char *nomeFicheiro){ // escreve no ficheiro  o array dos tempos de execução dos algoritmos

     FILE *fp;

     char *output = nomeFicheiro;

     int n;

     fp=fopen(output,"w");

     for(n=0;n < 14;n++) {
     
        fprintf(fp,"%f\n", array[n]);
      
     }

     fclose(fp);

 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// code used to generate all permutations of n objects
//
// n ........ number of objects
// m ........ index where changes occur (a[0], ..., a[m-1] will not be changed)
// a[idx] ... the number of the object placed in position idx
//
// TODO: modify the following function to solve the assignment problem
//




static void generate_all_permutations(int n,int m,int a[n])
{
  if(m < n - 1)
  {
    //
    // not yet at the end; try all possibilities for a[m]
    //
    for(int i = m;i < n;i++)
    {
      
#define swap(i,j)  do { int t = a[i]; a[i] = a[j]; a[j] = t; } while(0)
      swap(i,m);                            // exchange a[i] with a[m]
      generate_all_permutations(n,m + 1,a); // recurse
      swap(i,m);                            // undo the exchange of a[i] with a[m]
#undef swap
    }

  }
  else
  {
    //
    // visit the permutation (TODO: change this ...)
    //
    n_visited++;

    

    if(custo_permutacao(n, a) < min_cost){  
      min_cost = custo_permutacao(n, a); 
    
    for(int i=0; i<n; i++){
      min_cost_assignment[i] = a[i]; // coloca o assignment correspondente ao mínimo custo
    }
  }

    if(custo_permutacao(n, a) > max_cost){
      max_cost = custo_permutacao(n, a);
    
    for(int i=0; i<n; i++){
      max_cost_assignment[i] = a[i]; // same as minimum cost but for the maximum cost

    }
  }

    histogram[custo_permutacao(n, a)]+=1; // incrementa 1 ao histogram[cost]

  }
  
}

static void generate_all_permutations_branch_and_bound(int n, int m, int a[n], int custo_parcial){
   if (min_cost < custo_parcial + 3*(m-n + 3)) // pra cada custo parcial, soma o custo mínimo das restantes e se já for maior que o custo minimo atual,                                       
    return;                                    // dá return e passa para a permutação seguinte
  if(m < n - 1)
  {
    //
    // not yet at the end; try all possibilities for a[m]
    //
    for(int i = m;i < n;i++)
    {
       
#define swap(i,j)  do { int t = a[i]; a[i] = a[j]; a[j] = t; } while(0)
      swap(i,m); 
                                // exchange a[i] with a[m]
      generate_all_permutations_branch_and_bound(n,m + 1,a, custo_parcial + cost[m][a[m]]); // recurse
      swap(i,m);                            // undo the exchange of a[i] with a[m]
#undef swap
    }
  }
  else
  {
    //
    // visit the permutation (TODO: change this ...)
    //
    
    int custo_total = custo_parcial + cost[m][a[m]];
    
    if(custo_total < min_cost){ 
      min_cost = custo_total; 
    
    for(int i=0; i<n; i++){
      min_cost_assignment[i] = a[i]; 
    }
  }
  n_visited++;

  }
   
}





////////////////////////////////////////////////////////////////////////////////////////////////////
//
// main program
//

int main(int argc,char **argv)
{
  if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'e')
  {
    seed = 0;
    {
      int n = 3;
      init_costs(-3); // costs for the example with n = 3
      int a[n];
      for(int i = 0;i < n;i++)
        a[i] = i;
      reset_solutions();
      (void)elapsed_time();
      generate_all_permutations(n,0,a);
      cpu_time = elapsed_time();
      show_solutions(n,"Example for n=3",show_all);
      printf("\n");
    }
    {
      int n = 5;
      init_costs(-5); // costs for the example with n = 5
      int a[n];
      for(int i = 0;i < n;i++)
        a[i] = i;
      reset_solutions();
      (void)elapsed_time();
      generate_all_permutations(n,0,a);
      cpu_time = elapsed_time();
      show_solutions(n,"Example for n=5",show_all);
      return 0;
    }
  }
  if(argc == 2)
  {
    seed = atoi(argv[1]); // seed = student number
    if(seed >= 0 && seed <= 1000000)
    {
      int custos_minimos[14];
      int custos_maximos[14];
      double cputime_bruteforce[14];
      double cputime_BnB[14];
      double cputime_RandomPerm[14];
      for(int n = 1;n <= 14;n++)
      {
        init_costs(n);
        show_solutions(n,"Problem statement",show_info_1 | show_costs);
        //
        // 2.
        //

        if(n <= 14) // use a smaller limit here while developing your code
        {
          int a[n];
          for(int i = 0;i < n;i++)
            a[i] = i; // initial permutation
          reset_solutions();
          (void)elapsed_time();
          generate_all_permutations(n,0,a);
          cpu_time = elapsed_time();
          show_solutions(n,"Brute force",show_info_2 | show_min_solution | show_max_solution | show_histogram);
          
        }
        if(n==13) { 
          char dest[50] = "n_13_";
          strcat(dest, argv[1]);
          strcat(dest, ".txt"); 

          write_file(histogram, dest); // escreve no ficheiro para o nmec passado como argumento, para n = 13
          
       }
       if(n==14){
          char dest[50] = "n_14_";
          strcat(dest, argv[1]);
          strcat(dest, ".txt"); 

          write_file(histogram, dest); // escreve no ficheiro para o nmec passado como argumento, para n = 14

       }
       custos_minimos[n-1] = min_cost; // coloca no array de custos_minimos o custo minimo para cada n
       custos_maximos[n-1] = max_cost; // coloca no array de custos_maximos o custo maximo para cada n
       cputime_bruteforce[n-1] = cpu_time; // coloca no array de cputime_bruteforce o tempo de execução do brute force para cada n



        // place here your code that solves the problem with branch-and-bound
        //
#if 1
        if(n <= 14) // use a smaller limit here while developing your code
        {
          int a[n];
          for(int i = 0;i < n;i++)
            a[i] = i; // initial permutation
          reset_solutions_without_histogram();
          (void)elapsed_time();
          generate_all_permutations_branch_and_bound(n,0,a,0);
          cpu_time = elapsed_time();
          show_solutions(n,"Brute force with branch-and-bound",show_info_2 | show_min_solution);
          printf("\n");
        }
        cputime_BnB[n-1] = cpu_time; // coloca no array de cputime_BnB o tempo de execução do branch and bound para cada n

#endif
        //
        // place here your code that generates the random permutations
        //
       if(n <= 14){
        int a[n];
          
          reset_solutions_without_histogram();
          (void)elapsed_time();
          
          for(int i=1; i<1000000; i++){
            
            random_permutation(n,a);
            if(custo_permutacao(n, a) < min_cost){ 
              min_cost = custo_permutacao(n, a); 
            
            for(int i=0; i<n; i++){
              min_cost_assignment[i] = a[i]; // places the assignment with the minimum cost for each n 
              }
            }

            if(custo_permutacao(n, a) > max_cost){
              max_cost = custo_permutacao(n, a);
            
            for(int i=0; i<n; i++){
              max_cost_assignment[i] = a[i]; // same as minimum cost but for the maximum cost
              }
            }
          }
          cpu_time = elapsed_time();
          show_solutions(n,"Brute force Random Permutations",show_info_2 | show_min_solution | show_max_solution);

          }    
          cputime_RandomPerm[n-1] = cpu_time;    // coloca no array de cputime_RandomPerm o tempo de execução do random permutations para cada n

        

        //
        // ...
        //

        //
        // done
        //
        printf("\n");
      }
      char dest[1024];
      memset(dest, 0, sizeof(dest)); //coloca o array vazio
      strcat(dest, argv[1]); // para ir buscar o nmec passado como argumento
      write_file_custos(custos_minimos, strcat(dest,"_custos_minimos.txt")); //escreve no ficheiro os custos minimos para o nmec passado como argumento

      memset(dest, 0, sizeof(dest)); //coloca o array vazio
      strcat(dest, argv[1]); // para ir buscar o nmec passado como argumento
      write_file_custos(custos_maximos, strcat(dest,"_custos_maximos.txt")); //escreve no ficheiro os custos maximos para o nmec passado como argumento

      memset(dest, 0, sizeof(dest)); //coloca o array vazio
      strcat(dest, argv[1]); // para ir buscar o nmec passado como argumento
      write_file_cputime(cputime_bruteforce, strcat(dest,"_cputime_bf.txt")); //escreve no ficheiro os tempos de execução do brute force para o nmec passado como argumento

      memset(dest, 0, sizeof(dest)); //coloca o array vazio
      strcat(dest, argv[1]); // para ir buscar o nmec passado como argumento
      write_file_cputime(cputime_BnB, strcat(dest,"_cputime_BnB.txt")); //escreve no ficheiro os tempos de execução do branch and bound para o nmec passado como argumento

      memset(dest, 0, sizeof(dest)); //coloca o array vazio
      strcat(dest, argv[1]); // para ir buscar o nmec passado como argumento
      write_file_cputime(cputime_RandomPerm, strcat(dest,"_cputime_RandomPerm.txt")); //escreve no ficheiro os tempos de execução do random permutations para o nmec passado como argumento
      return 0;
    }
    
  }
  fprintf(stderr,"usage: %s -e              # for the examples\n",argv[0]);
  fprintf(stderr,"usage: %s student_number\n",argv[0]);
  return 1;
}
