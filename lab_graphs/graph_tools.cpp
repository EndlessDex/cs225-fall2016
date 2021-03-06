/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <map>
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    for(Vertex vIt : graph.getVertices()) {
        graph.setVertexLabel(vIt, "UNEXPLORED");
        for(Vertex wIt : graph.getAdjacent(vIt)) {
            graph.setEdgeLabel(vIt, wIt, "UNEXPLORED");
        }
    }

    queue<Vertex> bfs;
    bfs.push(graph.getStartingVertex());
    graph.setVertexLabel(bfs.front(), "VISITED");
    int minEdgeWeight = INT_MAX;
    Edge minEdge;
    while (!bfs.empty()) {
        Vertex v = bfs.front();
        bfs.pop();
        for(Vertex w : graph.getAdjacent(v)) {
            if(graph.getVertexLabel(w) == "UNEXPLORED") {
                graph.setVertexLabel(w, "VISITED");
                graph.setEdgeLabel(v, w, "DISCOVERY");
                bfs.push(w);
            }
            else if(graph.getEdgeLabel(v, w) == "UNEXPLORED") {
                graph.setEdgeLabel(v, w, "CROSS");
            }
            if(graph.getEdgeWeight(v, w) < minEdgeWeight) {
                minEdgeWeight = graph.getEdgeWeight(v, w);
                minEdge.source = v;
                minEdge.dest = w;
            }
        }
    }
    graph.setEdgeLabel(minEdge.source, minEdge.dest, "MIN");
    return minEdgeWeight;
}
/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    for(Vertex vIt : graph.getVertices()) {
        graph.setVertexLabel(vIt, "UNEXPLORED");
        for(Vertex wIt : graph.getAdjacent(vIt)) {
            graph.setEdgeLabel(vIt, wIt, "UNEXPLORED");
        }
    }
    map<Vertex, Vertex> path;
    queue<Vertex> bfs;
    bfs.push(start);
    graph.setVertexLabel(bfs.front(), "VISITED");
    while (!bfs.empty()) {
        Vertex v = bfs.front();
        bfs.pop();
        for(Vertex w : graph.getAdjacent(v)) {
            if(graph.getVertexLabel(w) == "UNEXPLORED") {
                path[w] = v;
                graph.setVertexLabel(w, "VISITED");
                graph.setEdgeLabel(v, w, "DISCOVERY");
                bfs.push(w);
            }
            else if(graph.getEdgeLabel(v, w) == "UNEXPLORED") {
                graph.setEdgeLabel(v, w, "CROSS");
            }
        }
    }
    int dist = 0;
    while(end != start) {
        graph.setEdgeLabel(end, path[end], "MINPATH");
        end = path[end];

        dist++;
    }
    return dist;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
}
