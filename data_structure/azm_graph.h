//azm_graph.h
#ifndef _AZM_GRAPH_H_
#define _AZM_GRAPH_H_

#include"azm_list.h"
#include"azm_set.h"

typedef struct azm_adjlist_s
{
    void *vertex;
    azm_set_t adjacent;
} azm_adjlist_t;


typedef struct azm_graph_s
{
    int vcount;
    int ecount;

    int (*cmp)(const void *, const void *);
    void (*destroy)(void *);

    azm_list_t adjlists;

} azm_graph_t;

void azm_graph_init(azm_graph_t *graph, void (*destroy)(void *), int (*cmp)(const void *, const void *));
void azm_graph_destroy(azm_graph_t *graph);

int azm_graph_ins_vertex(azm_graph_t *graph, const void *data);
int azm_graph_rem_vertex(azm_graph_t *graph, void **data);

int azm_graph_ins_edge(azm_graph_t *graph, const void *data1, const void *data2);
int azm_graph_rem_edge(azm_graph_t *graph, void *data1, void **data2);

int azm_graph_adjlist(azm_graph_t *graph, const void *data, azm_adjlist_t **adjlist);
int azm_graph_is_adjacent(const azm_graph_t *graph, const void *data1, const void *data2);

#define azm_graph_adjlists(graph) ((graph)->adjlists)
#define azm_graph_ecount(graph) ((graph)->ecount)
#define azm_graph_vcount(graph) ((graph)->vcount)


#endif
