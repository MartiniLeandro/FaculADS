#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INVENTORY 100
#define NAME_LEN 40
#define TYPE_LEN 20
#define TOWER_MAX 20

typedef struct {
    char name[NAME_LEN];
    char type[TYPE_LEN];
    int priority;
    int quantity;
} Item;

typedef struct {
    Item items[MAX_INVENTORY];
    int size;
} InventoryArray;

typedef struct Node {
    Item data;
    struct Node *next;
} Node;

typedef struct {
    char part[NAME_LEN];
} TowerPart;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void to_lower_str(char *s) {
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

Item make_item(const char *name, const char *type, int priority, int quantity) {
    Item it;
    strncpy(it.name, name, NAME_LEN-1); it.name[NAME_LEN-1] = '\0';
    strncpy(it.type, type, TYPE_LEN-1); it.type[TYPE_LEN-1] = '\0';
    it.priority = priority;
    it.quantity = quantity;
    return it;
}

void print_item(const Item *it) {
    printf("Nome: %-20s | Tipo: %-10s | Prioridade: %d | Qtde: %d\n",
           it->name, it->type, it->priority, it->quantity);
}

void init_inventory_array(InventoryArray *inv) {
    inv->size = 0;
}

int find_index_by_name(InventoryArray *inv, const char *name) {
    char lower_name[NAME_LEN];
    strncpy(lower_name, name, NAME_LEN-1); lower_name[NAME_LEN-1] = '\0';
    to_lower_str(lower_name);
    for (int i = 0; i < inv->size; ++i) {
        char tmp[NAME_LEN];
        strncpy(tmp, inv->items[i].name, NAME_LEN-1); tmp[NAME_LEN-1] = '\0';
        to_lower_str(tmp);
        if (strcmp(tmp, lower_name) == 0) return i;
    }
    return -1;
}

int add_item_array(InventoryArray *inv, Item it) {
    if (inv->size >= MAX_INVENTORY) return 0;
    int idx = find_index_by_name(inv, it.name);
    if (idx >= 0) {
        inv->items[idx].quantity += it.quantity;
    } else {
        inv->items[inv->size++] = it;
    }
    return 1;
}

int remove_item_array(InventoryArray *inv, const char *name, int q) {
    int idx = find_index_by_name(inv, name);
    if (idx < 0) return 0;
    if (q >= inv->items[idx].quantity) {
        for (int i = idx; i < inv->size-1; ++i) inv->items[i] = inv->items[i+1];
        inv->size--;
    } else {
        inv->items[idx].quantity -= q;
    }
    return 1;
}

void print_inventory_array(InventoryArray *inv) {
    if (inv->size == 0) { printf("Inventário vazio (array).\n"); return; }
    printf("Inventário (array) -- %d itens:\n", inv->size);
    for (int i = 0; i < inv->size; ++i) {
        printf("%2d) ", i+1);
        print_item(&inv->items[i]);
    }
}

Node* create_node(Item it) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->data = it;
    n->next = NULL;
    return n;
}

void add_item_list(Node **head, Item it) {
    Node *cur = *head;
    while (cur) {
        char a[NAME_LEN], b[NAME_LEN];
        strncpy(a, cur->data.name, NAME_LEN-1); a[NAME_LEN-1]='\0';
        strncpy(b, it.name, NAME_LEN-1); b[NAME_LEN-1]='\0';
        to_lower_str(a); to_lower_str(b);
        if (strcmp(a,b)==0) { cur->data.quantity += it.quantity; return; }
        cur = cur->next;
    }
    Node *n = create_node(it);
    n->next = *head;
    *head = n;
}

int remove_item_list(Node **head, const char *name, int q) {
    Node *cur = *head, *prev = NULL;
    char lower_name[NAME_LEN];
    strncpy(lower_name, name, NAME_LEN-1); lower_name[NAME_LEN-1] = '\0';
    to_lower_str(lower_name);
    while (cur) {
        char tmp[NAME_LEN];
        strncpy(tmp, cur->data.name, NAME_LEN-1); tmp[NAME_LEN-1] = '\0';
        to_lower_str(tmp);
        if (strcmp(tmp, lower_name) == 0) {
            if (q >= cur->data.quantity) {
                if (prev) prev->next = cur->next; else *head = cur->next;
                free(cur);
            } else {
                cur->data.quantity -= q;
            }
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

void print_inventory_list(Node *head) {
    if (!head) { printf("Inventário vazio (lista ligada).\n"); return; }
    printf("Inventário (lista ligada):\n");
    int i = 1;
    for (Node *cur = head; cur; cur = cur->next, ++i) {
        printf("%2d) ", i);
        print_item(&cur->data);
    }
}

void free_list(Node **head) {
    Node *cur = *head;
    while (cur) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    *head = NULL;
}

int list_to_array(Node *head, Item *arr, int maxlen) {
    int i = 0;
    for (Node *cur = head; cur && i < maxlen; cur = cur->next) {
        arr[i++] = cur->data;
    }
    return i;
}

typedef enum { KEY_NAME, KEY_TYPE, KEY_PRIORITY } SortKey;

int compare_items(const Item *a, const Item *b, SortKey key) {
    if (key == KEY_NAME) {
        char A[NAME_LEN], B[NAME_LEN];
        strncpy(A, a->name, NAME_LEN-1); A[NAME_LEN-1]='\0';
        strncpy(B, b->name, NAME_LEN-1); B[NAME_LEN-1]='\0';
        to_lower_str(A); to_lower_str(B);
        return strcmp(A,B);
    } else if (key == KEY_TYPE) {
        char A[TYPE_LEN], B[TYPE_LEN];
        strncpy(A, a->type, TYPE_LEN-1); A[TYPE_LEN-1]='\0';
        strncpy(B, b->type, TYPE_LEN-1); B[TYPE_LEN-1]='\0';
        to_lower_str(A); to_lower_str(B);
        return strcmp(A,B);
    } else {
        return (a->priority - b->priority);
    }
}

void selection_sort(Item *arr, int n, SortKey key) {
    for (int i = 0; i < n-1; ++i) {
        int min_idx = i;
        for (int j = i+1; j < n; ++j) {
            if (compare_items(&arr[j], &arr[min_idx], key) < 0) min_idx = j;
        }
        if (min_idx != i) {
            Item tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

int binary_search_by_name(Item *arr, int n, const char *name) {
    int l = 0, r = n-1;
    char target[NAME_LEN];
    strncpy(target, name, NAME_LEN-1); target[NAME_LEN-1] = '\0';
    to_lower_str(target);
    while (l <= r) {
        int mid = (l + r) / 2;
        char midname[NAME_LEN];
        strncpy(midname, arr[mid].name, NAME_LEN-1); midname[NAME_LEN-1] = '\0';
        to_lower_str(midname);
        int cmp = strcmp(midname, target);
        if (cmp == 0) return mid;
        else if (cmp < 0) l = mid+1;
        else r = mid-1;
    }
    return -1;
}

typedef struct {
    TowerPart parts[TOWER_MAX];
    int size;
} Tower;

void init_tower(Tower *t) { t->size = 0; }

int add_part_to_tower(Tower *t, const char *part) {
    if (t->size >= TOWER_MAX) return 0;
    strncpy(t->parts[t->size].part, part, NAME_LEN-1);
    t->parts[t->size].part[NAME_LEN-1] = '\0';
    t->size++;
    return 1;
}

void print_tower(Tower *t) {
    if (t->size == 0) { printf("Torre vazia.\n"); return; }
    printf("Torre de Fuga (de baixo para cima):\n");
    for (int i = 0; i < t->size; ++i) {
        printf("%2d) %s\n", i+1, t->parts[i].part);
    }
}

void seed_items(InventoryArray *invArr, Node **invList) {
    Item a[] = {
        make_item("Maca", "Alimento", 2, 5),
        make_item("Agua", "Alimento", 1, 3),
        make_item("Faca", "Arma", 1, 1),
        make_item("Cordao", "Ferramenta", 2, 2),
        make_item("Madeira", "Componente", 3, 10),
        make_item("Prego", "Componente", 3, 20),
        make_item("Motor", "Componente", 1, 1),
        make_item("Tela", "Componente", 2, 2),
    };
    int n = sizeof(a)/sizeof(a[0]);
    for (int i = 0; i < n; ++i) {
        add_item_array(invArr, a[i]);
        add_item_list(invList, a[i]);
    }
}

void build_tower_interactive(Tower *tower, InventoryArray *inv) {
    printf("Construir Torre de Fuga: escolha componentes do inventário (array).\n");
    print_inventory_array(inv);
    while (1) {
        printf("Digite o nome do item para adicionar à torre (ou 'fim' para terminar): ");
        char name[NAME_LEN];
        if (fgets(name, NAME_LEN, stdin) == NULL) return;
        name[strcspn(name, "\n")] = 0;
        if (strcmp(name, "fim") == 0) break;
        int idx = find_index_by_name(inv, name);
        if (idx < 0) { printf("Item não encontrado.\n"); continue; }
        if (inv->items[idx].quantity <= 0) { printf("Sem quantidade disponível.\n"); continue; }
        add_part_to_tower(tower, inv->items[idx].name);
        remove_item_array(inv, name, 1);
        printf("Adicionado '%s' à torre. (%d restantes)\n", name, (idx >= 0 && idx < inv->size)? inv->items[idx].quantity : 0);
    }
    printf("Construção da torre concluída.\n");
}

void demo_escape_simulation(InventoryArray *inv) {
    Tower tower;
    init_tower(&tower);
    build_tower_interactive(&tower, inv);
    print_tower(&tower);
    printf("Simulação: torre construída.\n");
    int hasMotor = 0, hasTela = 0;
    for (int i = 0; i < tower.size; ++i) {
        char tmp[NAME_LEN];
        strncpy(tmp, tower.parts[i].part, NAME_LEN-1); tmp[NAME_LEN-1] = '\0';
        to_lower_str(tmp);
        if (strstr(tmp, "motor")) hasMotor = 1;
        if (strstr(tmp, "tela")) hasTela = 1;
    }
    if (hasMotor && hasTela) printf("Fuga bem-sucedida!\n");
    else printf("Fuga falhou.\n");
}

void menu_inventory_array(InventoryArray *inv) {
    while (1) {
        printf("\n--- Menu: Inventário (Array) ---\n");
        printf("1) Listar inventário\n");
        printf("2) Adicionar item\n");
        printf("3) Remover item (quantidade)\n");
        printf("4) Ordenar inventário (Selection Sort)\n");
        printf("5) Busca binária por nome\n");
        printf("6) Voltar\n");
        printf("Escolha: ");
        int choice;
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();
        if (choice == 1) print_inventory_array(inv);
        else if (choice == 2) {
            char name[NAME_LEN], type[TYPE_LEN];
            int prio, q;
            printf("Nome do item: "); fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")] = 0;
            printf("Tipo: "); fgets(type, TYPE_LEN, stdin); type[strcspn(type,"\n")] = 0;
            printf("Prioridade: "); scanf("%d", &prio); clear_input_buffer();
            printf("Quantidade: "); scanf("%d", &q); clear_input_buffer();
            add_item_array(inv, make_item(name, type, prio, q));
            printf("Item adicionado.\n");
        }
        else if (choice == 3) {
            char name[NAME_LEN];
            int q;
            printf("Nome do item a remover: "); fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")] = 0;
            printf("Quantidade a remover: "); scanf("%d", &q); clear_input_buffer();
            if (remove_item_array(inv, name, q)) printf("Removido.\n"); else printf("Item não encontrado.\n");
        }
        else if (choice == 4) {
            printf("Ordenar por: 1) Nome 2) Tipo 3) Prioridade : ");
            int k = 1; scanf("%d",&k); clear_input_buffer();
            SortKey key = (k==2)?KEY_TYPE:(k==3)?KEY_PRIORITY:KEY_NAME;
            selection_sort(inv->items, inv->size, key);
            printf("Ordenado.\n");
        }
        else if (choice == 5) {
            char name[NAME_LEN];
            printf("Nome a buscar: "); fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")] = 0;
            int idx = binary_search_by_name(inv->items, inv->size, name);
            if (idx >= 0) { printf("Encontrado na posição %d: ", idx+1); print_item(&inv->items[idx]); }
            else printf("Não encontrado.\n");
        }
        else if (choice == 6) break;
    }
}

void menu_inventory_list(Node **head) {
    while (1) {
        printf("\n--- Menu: Inventário (Lista Ligada) ---\n");
        printf("1) Listar inventário\n");
        printf("2) Adicionar item\n");
        printf("3) Remover item (quantidade)\n");
        printf("4) Converter lista -> array\n");
        printf("5) Voltar\n");
        printf("Escolha: ");
        int choice;
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();
        if (choice == 1) print_inventory_list(*head);
        else if (choice == 2) {
            char name[NAME_LEN], type[TYPE_LEN];
            int prio, q;
            printf("Nome: "); fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")] = 0;
            printf("Tipo: "); fgets(type, TYPE_LEN, stdin); type[strcspn(type,"\n")] = 0;
            printf("Prioridade: "); scanf("%d", &prio); clear_input_buffer();
            printf("Quantidade: "); scanf("%d", &q); clear_input_buffer();
            add_item_list(head, make_item(name, type, prio, q));
            printf("Item adicionado.\n");
        }
        else if (choice == 3) {
            char name[NAME_LEN];
            int q;
            printf("Nome: "); fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")] = 0;
            printf("Quantidade: "); scanf("%d",&q); clear_input_buffer();
            if (remove_item_list(head, name, q)) printf("Removido.\n"); else printf("Item não encontrado.\n");
        }
        else if (choice == 4) {
            Item arr[MAX_INVENTORY];
            int n = list_to_array(*head, arr, MAX_INVENTORY);
            printf("Array (%d itens):\n", n);
            for (int i = 0; i < n; ++i) {
                printf("%2d) ", i+1); print_item(&arr[i]);
            }
        }
        else if (choice == 5) break;
    }
}

void compare_array_list(InventoryArray *invArr, Node *invList) {
    printf("\n--- Comparação Array x Lista ---\n");
    printf("Tamanho array: %d\n", invArr->size);
    int listSize = 0;
    for (Node *cur = invList; cur; cur = cur->next) ++listSize;
    printf("Tamanho lista: %d\n", listSize);
    printf("Digite o nome do item para comparação: ");
    char name[NAME_LEN];
    fgets(name, NAME_LEN, stdin); name[strcspn(name,"\n")] = 0;
    int foundArray = -1;
    for (int i = 0; i < invArr->size; ++i) {
        char a[NAME_LEN]; strncpy(a, invArr->items[i].name, NAME_LEN-1); a[NAME_LEN-1]='\0'; to_lower_str(a);
        char b[NAME_LEN]; strncpy(b, name, NAME_LEN-1); b[NAME_LEN-1]='\0'; to_lower_str(b);
        if (strcmp(a,b) == 0) { foundArray = i; break; }
    }
    int stepsArray = (foundArray==-1)?invArr->size:(foundArray+1);

    int stepsList = 0;
    Node *cur = invList;
    int foundList = 0;
    while (cur) {
        ++stepsList;
        char a[NAME_LEN]; strncpy(a, cur->data.name, NAME_LEN-1); a[NAME_LEN-1]='\0'; to_lower_str(a);
        char b[NAME_LEN]; strncpy(b, name, NAME_LEN-1); b[NAME_LEN-1]='\0'; to_lower_str(b);
        if (strcmp(a,b)==0) { foundList = 1; break; }
        cur = cur->next;
    }
    printf("Array -> passos: %d (%s)\n", stepsArray, (foundArray==-1)?"não encontrado":"encontrado");
    printf("Lista -> passos: %d (%s)\n", stepsList, foundList?"encontrado":"não encontrado");
}

int main(void) {
    InventoryArray invArr;
    Node *invList = NULL;
    init_inventory_array(&invArr);
    seed_items(&invArr, &invList);

    printf("Bem-vindo ao desafio: Sobrevivência na Ilha!\n");

    while (1) {
        printf("\n===== Menu Principal =====\n");
        printf("1) Inventário (array)\n");
        printf("2) Inventário (lista ligada)\n");
        printf("3) Comparar array x lista\n");
        printf("4) Construir torre de fuga\n");
        printf("5) Mostrar inventários\n");
        printf("6) Sair\n");
        printf("Escolha: ");
        int mainChoice;
        if (scanf("%d", &mainChoice) != 1) { clear_input_buffer(); continue; }
        clear_input_buffer();
        if (mainChoice == 1) menu_inventory_array(&invArr);
        else if (mainChoice == 2) menu_inventory_list(&invList);
        else if (mainChoice == 3) compare_array_list(&invArr, invList);
        else if (mainChoice == 4) demo_escape_simulation(&invArr);
        else if (mainChoice == 5) {
            printf("\n-- Inventário (array) --\n");
            print_inventory_array(&invArr);
            printf("\n-- Inventário (lista) --\n");
            print_inventory_list(invList);
        }
        else if (mainChoice == 6) {
            printf("Saindo...\n");
            break;
        }
    }

    free_list(&invList);
    return 0;
}
