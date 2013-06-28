//azm_graph.c
#include <stdlib.h>
#include <string.h>
#include"azm_graph.h"


void azm_graph_init(azm_graph_t *graph, void (*destroy)(void *), int (*cmp)(const void *, const void *))
{
    graph->vcount = 0;
    graph->ecount = 0;
    graph->cmp  = cmp;
    graph->destroy = destroy;

    azm_list_init(&graph->adjlists, NULL);

    return ;
}

void azm_graph_destroy(azm_graph_t *graph)
{
    azm_adjlist_t *adjlist;

    while(azm_list_size(&graph->adjlists) > 0){

        if(azm_list_rem_next(&graph->adjlists, NULL, (void**)&adjlist) == 0){

            azm_set_destroy(&adjlist->adjacent);
            if(graph->destroy != NULL){
                graph->destroy(&adjlist->vertex);
            }

            free(adjlist);

        }


    }

    azm_list_destroy(&graph->adjlists);
    memset(graph, 0, sizeof(azm_graph_t));
    return;

}

int azm_graph_ins_vertex(azm_graph_t *graph, const void *data)
{
    azm_adjlist_t *adjlist;
    azm_adjlist_t *tmp_adjlist;
    azm_list_elmt_t *list_iter;

    for(list_iter = azm_list_head(&graph->adjlists); list_iter; list_iter =  azm_list_next(list_iter)){

        tmp_adjlist = (azm_adjlist_t *)azm_list_data(list_iter);
        if(graph->cmp(data, tmp_adjlist->vertex) == 0){
            return 1;

        }
    }

    if((adjlist =(azm_adjlist_t *) malloc(sizeof(azm_adjlist_t))) == NULL)
        return -1;
    azm_set_init(&adjlist->adjacent, graph->destroy, graph->cmp);
    adjlist->vertex = (void *)data;
    if(azm_list_ins_next(graph->adjlists,  azm_list_tail(&graph->adjlists), adjlist) == -1){
        return -1;
    }
    graph->vcount++;


    return 0;
}


int azm_graph_rem_vertex(azm_graph_t *graph, void **data)
{

    azm_adjlist_t *adjlist;
    azm_adjlist_t *tmp_adjlist;
    azm_list_elmt_t *cur_iter;
    azm_list_elmt_t *tmp_iter;
    azm_list_elmt_t *prev_iter = NULL;
    int found;

    for(cur_iter = azm_list_head(&graph->adjlists); cur_iter; cur_iter = azm_list_next(cur_iter)){

        tmp_adjlist = (azm_adjlist_t *)azm_list_data(cur_iter);
        if(azm_set_is_member(&tmp_adjlist->adjacent,  *data))
           return -1;


        if(graph->cmp(&tmp_adjlist->vertex, *data) == 0){
            tmp_iter = cur_iter;
            found = 1;

        }

        if(!found)
            prev_iter = cur_iter;

    }

    if(!found)
        return -1;

    if(azm_set_size(&((azm_adjlist_t *)azm_list_data(tmp_iter))->adjacent)> 0)
        return -1;



    if (azm_list_rem_next(&graph->adjlists, prev_iter, (void **)&adjlist) != 0)
            return -1;
    *data = adjlist->vertex;
    free(adjlist);
    graph->vcount--;
    return 0;

}

int azm_graph_ins_edge(azm_graph_t *graph, const void *data1, const void *data2)
{
    azm_adjlist_t *adjlist;

    azm_list_elmt_t *cur_iter;



    for(cur_iter = azm_list_head(&graph->adjlists); cur_iter; cur_iter = azm_list_next(cur_iter)){

        if(graph->cmp(&((azm_adjlist_t *)azm_list_data(cur_iter))->vertex, data2) == 0)
            break;
    }

    if(cur_iter == NULL)
        return -1;

    for(cur_iter = azm_list_head(&graph->adjlists); cur_iter; cur_iter = azm_list_next(cur_iter)){

        if(graph->cmp(&((azm_adjlist_t *)azm_list_data(cur_iter))->vertex, data1) == 0)
            break;
    }

    if(cur_iter == NULL)
        return -1;


    adjlist = (azm_adjlist_t *)azm_list_data(cur_iter);

    if(azm_set_insert(&adjlist->adjacent, data2 ) != 0)
        return -1;
    graph->ecount++;
    return 0;

}

int azm_graph_rem_edge(azm_graph_t *graph, void *data1, void **data2)
{
    azm_adjlist_t *adjlist;
    azm_list_elmt_t *cur_iter;


    for(cur_iter = azm_list_head(&graph->adjlists); cur_iter; cur_iter = azm_list_next(cur_iter)){

        if(graph->cmp(&((azm_adjlist_t *)azm_list_data(cur_iter))->vertex, data1) == 0)
            break;
    }

    if(cur_iter == NULL)
        return -1;

    adjlist = (azm_adjlist_t *)azm_list_data(cur_iter);
    if(azm_set_remove(&adjlist->adjacent, data2) != 0 )
        return -1;
    graph->ecount--;
    return 0;
}

int azm_graph_adjlist(azm_graph_t *graph, const void *data, azm_adjlist_t **adjlist)
{
    azm_list_elmt_t *cur_iter;

    for(cur_iter = azm_list_head(&graph->adjlists); cur_iter; cur_iter = azm_list_next(cur_iter)){

        if(graph->cmp(&((azm_adjlist_t *)azm_list_data(cur_iter))->vertex, data) == 0)
            break;
    }

    if(cur_iter == NULL)
        return -1;
    *adjlist = (azm_adjlist_t *)azm_list_data(cur_iter);
    return 0;

}

int azm_graph_is_adjacent(const azm_graph_t *graph, const void *data1, const void *data2)
{
    azm_adjlist_t *adjlist;
    azm_list_elmt_t *cur_iter;

    for(cur_iter = azm_list_head(&graph->adjlists); cur_iter; cur_iter = azm_list_next(cur_iter)){

        if(graph->cmp(&((azm_adjlist_t *)azm_list_data(cur_iter))->vertex, data1) == 0)
            break;

    }

    if(cur_iter == NULL)
        return 0;

    adjlist = (azm_adjlist_t *)azm_list_data(cur_iter);
    return azm_set_is_member(&adjlist->adjacent, data2);

}
