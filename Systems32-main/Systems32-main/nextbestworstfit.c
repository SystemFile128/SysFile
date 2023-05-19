#include<stdio.h>
#include<stdlib.h>

typedef struct Process {
    int pid;
    int size;
} Process;

typedef struct Partition {
    int pid;
    int size;
    struct Partition* prev;
    struct Partition* next;
} Partition;

Partition* create_partition_list(int* partition_sizes, int n) {
    Partition* head = NULL;
    Partition* tail = NULL;
    for (int i = 0; i < n; i++) {
        Partition* partition = (Partition*)malloc(sizeof(Partition));
        partition->pid = 0;
        partition->size = partition_sizes[i];
        partition->prev = tail;
        partition->next = NULL;
        if (tail != NULL)
            tail->next = partition;
        tail = partition;
        if (head == NULL)
            head = partition;
    }
    return head;
}

void print_partitions(Partition* head) {
    printf("Partitions: ");
    Partition* current = head;
    while (current != NULL) {
        printf("[%d:%d] ", current->pid, current->size);
        current = current->next;
    }
    printf("\n");
}

void first_fit(Partition* head, Process* processes, int m) {
    for (int i = 0; i < m; i++) {
        int pid = i + 1;
        Partition* current = head;
        while (current != NULL) {
            if (current->pid == 0 && current->size >= processes[i].size) {
                current->pid = pid;
                if (current->size > processes[i].size) {
                    Partition* new_partition = (Partition*)malloc(sizeof(Partition));
                    new_partition->pid = 0;
                    new_partition->size = current->size - processes[i].size;
                    new_partition->prev = current;
                    new_partition->next = current->next;
                    if (current->next != NULL)
                        current->next->prev = new_partition;
                    current->next = new_partition;
                    current->size = processes[i].size;
                }
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("Process %d cannot be allocated\n", pid);
        }
    }
}

void next_fit(Partition* head, Process* processes, int m) {
    Partition* current = head;
    for (int i = 0; i < m; i++) {
        int pid = i + 1;
        int flag = 0;
        while (current != NULL) {
            if (current->pid == 0 && current->size >= processes[i].size) {
                current->pid = pid;
                if (current->size > processes[i].size) {
                    Partition* new_partition = (Partition*)malloc(sizeof(Partition));
                    new_partition->pid = 0;
                    new_partition->size = current->size - processes[i].size;
                    new_partition->prev = current;
                    new_partition->next = current->next;
                    if (current->next != NULL)
                        current->next->prev = new_partition;
                    current->next = new_partition;
                    current->size = processes[i].size;
                }
                flag = 1;
                break;
            }
            current = current->next;
            if (current == NULL)
                current = head;
        }
        if (flag == 0) {
            printf("Process %d cannot be allocated\n", pid);
        }
    }
}

void worst_fit(Partition* head, Process* processes, int m) {
    for (int i = 0; i < m; i++) {
        int pid = i + 1;
        Partition* current = head;
        Partition* worst = NULL;
        while (current != NULL) {
            if (current->pid == 0 && current->size >= processes[i].size) {
                if (worst == NULL || worst->size < current->size)
                    worst = current;
            }
            current = current->next;
        }
        if (worst != NULL) {
            worst->pid = pid;
            if (worst->size > processes[i].size) {
                Partition* new_partition = (Partition*)malloc(sizeof(Partition));
                new_partition->pid = 0;
                new_partition->size = worst->size - processes[i].size;
                new_partition->prev = worst;
                new_partition->next = worst->next;
                if (worst->next != NULL)
                    worst->next->prev = new_partition;
                else
                    worst->next = new_partition;
                worst->next = new_partition;
                worst->size = processes[i].size;
            }
        } else {
            printf("Process %d cannot be allocated\n", pid);
        }
    }
}

void best_fit(Partition* head, Process* processes, int m) {
    for (int i = 0; i < m; i++) {
        int pid = i + 1;
        Partition* current = head;
        Partition* best = NULL;
        while (current != NULL) {
            if (current->pid == 0 && current->size >= processes[i].size) {
                if (best == NULL || best->size > current->size)
                    best = current;
            }
            current = current->next;
        }
        if (best != NULL) {
            best->pid = pid;
            if (best->size > processes[i].size) {
                Partition* new_partition = (Partition*)malloc(sizeof(Partition));
                new_partition->pid = 0;
                new_partition->size = best->size - processes[i].size;
                new_partition->prev = best;
                new_partition->next = best->next;
                if (best->next != NULL)
                    best->next->prev = new_partition;
                else
                    best->next = new_partition;
                best->next = new_partition;
                best->size = processes[i].size;
            }
        } else {
            printf("Process %d cannot be allocated\n", pid);
        }
    }
}

int main() {
    int n, m;
    printf("Enter the number of memory partitions: ");
    scanf("%d", &n);
    int partition_sizes[n];
    printf("Enter the sizes of the memory partitions: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &partition_sizes[i]);
    Partition* partition_head = create_partition_list(partition_sizes, n);
    printf("Enter the number of processes: ");
    scanf("%d", &m);
    Process processes[m];
    printf("Enter the sizes of the processes: ");
    for (int i = 0; i < m; i++) {
        int size;
        scanf("%d", &size);
        processes[i].pid = i + 1;
        processes[i].size = size;
    }
    int choice;
    printf("Choose the memory allocation algorithm:\n");
    printf("1. First fit\n");
    printf("2. Next fit\n");
    printf("3. Worst fit\n");
    printf("4. Best fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            first_fit(partition_head, processes, m);
            break;
        case 2:
            next_fit(partition_head, processes, m);
            break;
        case 3:
            worst_fit(partition_head, processes, m);
            break;
        case 4:
            best_fit(partition_head, processes, m);
            break;
        default:
            printf("Invalid choice\n");
            return 0;
    }
    printf("\nPartition\tSize\tProcess\n");
    Partition* current = partition_head;
    while (current != NULL) {
        if (current->pid == 0)
            printf("%d\t\t%d\t%s\n", current->pid, current->size, "Free");
        else
            printf("%d\t\t%d\t%d\n", current->pid, current->size, current->pid);
        current = current->next;
    }
    return 0;
}
