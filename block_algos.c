#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int FCFS(int* requests);
int SSTF(int* requests, int requests_count);
int LOOK(int* requests, int requests_count);
int CLOOK(int* requests, int requests_count);
int Compare(const void* a, const void* b);

#define MAX_BLOCK_SIZE 100

int main(int argc, char ** argv) {
  int requests[101]; // 100 max requests + delimeter '-1'
  FILE *fptr;

  fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    printf("file not found\n");
    printf("USAGE: ./run_sim <textfile>\n");
    return 1;
  }
  
  int bytes_read = 5;
  char line[bytes_read]; // 3 digits + \n + \0 => 5 bytes 
  // char *fgets(char *restrict s, int n, FILE *restrict stream);
  int i = 0;
  while (fgets(line, bytes_read, fptr) != NULL) {
    requests[i] = atoi(line);
    i++;
  }
  // indicate end of the requests array
  requests[i] = -1;
  
  int requests_count = 0;
  int j = 0;
  while (requests[j] != -1) {
    requests_count += 1;
    j += 1;
  }
  printf("FCFS Total Seek: %d\n", FCFS(requests));
  printf("SSTF Total Seek: %d\n", SSTF(requests, requests_count));
  printf("LOOK Total Seek: %d\n", LOOK(requests, requests_count));
  printf("C-LOOK Total Seek: %d\n", CLOOK(requests, requests_count));
  return 0;
}


int FCFS(int* requests) {
  FILE* f = fopen("fcfs_steps.csv", "w");
  fprintf(f, "Step,Position\n");

  int total = 0;
  int current_request = requests[0];
  int i = 0;
  int step = 0;

  fprintf(f, "%d,%d\n", step++, current_request); // initial position

  while (requests[i] != -1) {
    int incoming_request = requests[i];
    total += abs(current_request - incoming_request);
    current_request = incoming_request;

    fprintf(f, "%d,%d\n", step++, current_request);
    i++;
  }

  fclose(f);
  return total;
}



int SSTF(int* requests, int requests_count) {
  FILE* f = fopen("sstf_steps.csv", "w");
  fprintf(f, "Step,Position\n");

  int total = 0;
  int current_request = requests[0];
  int visited[MAX_BLOCK_SIZE] = {0};
  int step = 0;

  fprintf(f, "%d,%d\n", step++, current_request);

  for (int i = 0; i < requests_count; i++) {
    int min_diff = INT_MAX;
    int next_request = -1;

    for (int j = 0; j < requests_count; j++) {
      if (!visited[j] && abs(current_request - requests[j]) < min_diff) {
        min_diff = abs(current_request - requests[j]);
        next_request = j;
      }
    }
    total += min_diff;
    current_request = requests[next_request];
    visited[next_request] = 1;

    fprintf(f, "%d,%d\n", step++, current_request);
  }

  fclose(f);
  return total;
}


int Compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int LOOK(int* requests, int requests_count) {
  FILE* f = fopen("look_steps.csv", "w");
  fprintf(f, "Step,Position\n");

  int total = 0;
  int start = requests[0];
  int sorted[MAX_BLOCK_SIZE];
  for (int i = 0; i < requests_count; i++) {
    sorted[i] = requests[i];
  }
  qsort(sorted, requests_count, sizeof(int), Compare);

  int i = 0;
  while (sorted[i] != start) i++;
  int left = i - 1;
  int step = 0;

  fprintf(f, "%d,%d\n", step++, start);

  // Go right
  while (i + 1 < requests_count) {
    total += sorted[i + 1] - sorted[i];
    i++;
    fprintf(f, "%d,%d\n", step++, sorted[i]);
  }

  // Reverse
  total += sorted[i] - sorted[left];
  i = left;
  fprintf(f, "%d,%d\n", step++, sorted[i]);

  while (i > 0) {
    total += sorted[i] - sorted[i - 1];
    i--;
    fprintf(f, "%d,%d\n", step++, sorted[i]);
  }

  fclose(f);
  return total;
}



int CLOOK(int* requests, int requests_count) {
  FILE* f = fopen("clook_steps.csv", "w");
  fprintf(f, "Step,Position\n");

  int total = 0;
  int start = requests[0];
  int sorted[MAX_BLOCK_SIZE];
  for (int i = 0; i < requests_count; i++) {
    sorted[i] = requests[i];
  }
  qsort(sorted, requests_count, sizeof(int), Compare);

  int i = 0;
  while (sorted[i] != start) i++;

  int step = 0;
  fprintf(f, "%d,%d\n", step++, start);

  // Go right
  while (i + 1 < requests_count) {
    total += sorted[i + 1] - sorted[i];
    i++;
    fprintf(f, "%d,%d\n", step++, sorted[i]);
  }

  // Jump to beginning
  total += sorted[i] - sorted[0];
  i = 0;
  fprintf(f, "%d,%d\n", step++, sorted[i]);

  // Continue right from beginning
  while (sorted[i] < start && i + 1 < requests_count) {
    total += sorted[i + 1] - sorted[i];
    i++;
    fprintf(f, "%d,%d\n", step++, sorted[i]);
  }

  fclose(f);
  return total;
}

