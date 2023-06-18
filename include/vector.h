#ifndef D223B251_6EF0_4076_8F96_BE23FEF52489
#define D223B251_6EF0_4076_8F96_BE23FEF52489

#include <stdbool.h>
#include <stdlib.h>

#define FROM(T, name) __##name##T
#define NEW(T) (T *)malloc(sizeof(T))

#define usingVector(T, _)                                                      \
    typedef struct FROM(_, Vector) FROM(_, Vector);                            \
    typedef struct FROM(_, Node) FROM(_, Node);                                \
                                                                               \
    typedef struct FROM(_, Node)                                               \
    {                                                                          \
        FROM(_, Node) * next;                                                  \
        FROM(_, Node) * prev;                                                  \
        T value;                                                               \
    } FROM(_, Node);                                                           \
                                                                               \
    typedef struct FROM(_, Vector)                                             \
    {                                                                          \
        size_t size;                                                           \
        FROM(_, Node) * begin;                                                 \
        FROM(_, Node) * end;                                                   \
                                                                               \
        FROM(_, Node) * (*seek)(const FROM(_, Vector) *, size_t index);        \
        FROM(_, Node) * (*rseek)(const FROM(_, Vector) *, size_t index);       \
                                                                               \
        T *(*get)(FROM(_, Vector) *, size_t index);                            \
        void (*emplace_back)(FROM(_, Vector) *, T obj);                        \
        void (*emplace_front)(FROM(_, Vector) *, T obj);                       \
        void (*emplace)(FROM(_, Vector) *, size_t index, T obj);               \
        void (*clear)(FROM(_, Vector) *);                                      \
        void (*erase)(FROM(_, Vector) *, size_t index);                        \
    } FROM(_, Vector);                                                         \
                                                                               \
    FROM(_, Node) * FROM(_, seek)(const FROM(_, Vector) * self, size_t index)  \
    {                                                                          \
        if (index >= self->size)                                               \
            printf("ERROR: Index out of bounds.\n");                           \
                                                                               \
        FROM(_, Node) *current_node = self->begin;                             \
        size_t current_index = 0;                                              \
        while (current_index != index)                                         \
        {                                                                      \
            current_node = current_node->next;                                 \
            current_index++;                                                   \
        }                                                                      \
        return current_node;                                                   \
    }                                                                          \
                                                                               \
    FROM(_, Node) * FROM(_, rseek)(const FROM(_, Vector) * self, size_t index) \
    {                                                                          \
        if (index >= self->size)                                               \
            printf("ERROR: Index out of bounds.\n");                           \
                                                                               \
        FROM(_, Node) *current_node = self->end;                               \
        size_t current_index = 0;                                              \
        while (current_index != index)                                         \
        {                                                                      \
            current_node = current_node->prev;                                 \
            current_index++;                                                   \
        }                                                                      \
        return current_node;                                                   \
    }                                                                          \
                                                                               \
    T *FROM(_, get)(FROM(_, Vector) * self, size_t index)                      \
    {                                                                          \
        return &self->seek(self, index)->value;                                \
    }                                                                          \
                                                                               \
    void FROM(_, emplace_back)(FROM(_, Vector) * self, T obj)                  \
    {                                                                          \
        FROM(_, Node) *new_node = NEW(FROM(_, Node));                          \
        if (self->size == 0)                                                   \
        {                                                                      \
            self->end = self->begin = new_node;                                \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            self->end->next = new_node;                                        \
            new_node->prev = self->end;                                        \
            self->end = new_node;                                              \
        }                                                                      \
        new_node->value = obj;                                                 \
        self->size++;                                                          \
    }                                                                          \
                                                                               \
    void FROM(_, emplace_front)(FROM(_, Vector) * self, T obj)                 \
    {                                                                          \
        FROM(_, Node) *new_node = NEW(FROM(_, Node));                          \
        if (self->size == 0)                                                   \
        {                                                                      \
            self->end = self->begin = new_node;                                \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            self->begin->prev = new_node;                                      \
            new_node->next = self->begin;                                      \
            self->begin = new_node;                                            \
        }                                                                      \
        new_node->value = obj;                                                 \
        self->size++;                                                          \
    }                                                                          \
                                                                               \
    void FROM(_, emplace)(FROM(_, Vector) * self, size_t index, T obj)         \
    {                                                                          \
        if (index == self->size)                                               \
        {                                                                      \
            self->emplace_back(self, obj);                                     \
            return;                                                            \
        }                                                                      \
        if (index == 0)                                                        \
        {                                                                      \
            self->emplace_front(self, obj);                                    \
            return;                                                            \
        }                                                                      \
        FROM(_, Node) *current_node = self->seek(self, index);                 \
        FROM(_, Node) *new_node = NEW(FROM(_, Node));                          \
        new_node->prev = current_node->prev;                                   \
        if (current_node->prev != NULL)                                        \
            current_node->prev->next = new_node;                               \
        current_node->prev = new_node;                                         \
        new_node->next = current_node;                                         \
        new_node->value = obj;                                                 \
        self->size++;                                                          \
    }                                                                          \
                                                                               \
    void FROM(_, clear)(FROM(_, Vector) * self)                                \
    {                                                                          \
        FROM(_, Node) *current_node = self->begin;                             \
        while (current_node != NULL)                                           \
        {                                                                      \
            FROM(_, Node) *tmp = current_node->next;                           \
            free(current_node);                                                \
            current_node = NULL;                                               \
            current_node = tmp;                                                \
        }                                                                      \
        self->size = 0;                                                        \
    }                                                                          \
                                                                               \
    void FROM(_, erase)(FROM(_, Vector) * self, size_t index)                  \
    {                                                                          \
        FROM(_, Node) *current_node = self->seek(self, index);                 \
        if (current_node->prev != NULL)                                        \
            current_node->prev->next = current_node->next;                     \
        else                                                                   \
            self->begin = current_node->next;                                  \
                                                                               \
        if (current_node->next != NULL)                                        \
            current_node->next->prev = current_node->prev;                     \
        else                                                                   \
            self->end = current_node->prev;                                    \
                                                                               \
        free(current_node);                                                    \
        self->size--;                                                          \
    }                                                                          \
    typedef struct FROM(_, Vector) _

#define DefaultVector(_)            \
    {                               \
        0,                          \
            NULL,                   \
            NULL,                   \
            FROM(_, seek),          \
            FROM(_, rseek),         \
            FROM(_, get),           \
            FROM(_, emplace_back),  \
            FROM(_, emplace_front), \
            FROM(_, emplace),       \
            FROM(_, clear),         \
            FROM(_, erase),         \
    }

#endif /* D223B251_6EF0_4076_8F96_BE23FEF52489 */
