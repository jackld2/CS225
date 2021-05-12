#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList[v.key()].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.emplace(key, v);
  adjList.emplace(key, std::list<edgeListIter>());
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> incident = incidentEdges(key);
  for (auto edgeref: incident) {
    E & edge = edgeref.get();
    removeEdge(edge.source().key(), edge.dest().key());

  }
  adjList.erase(key);
  vertexMap.erase(key);

}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  auto it = edgeList.begin();
  adjList[v1.key()].push_back(it);
  adjList[v2.key()].push_back(it);

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  bool edgeExists = false;
  std::list<edgeListIter> & key1list = adjList.at(key1);
  std::list<edgeListIter> & key2list = adjList.at(key2);
  edgeListIter  edgeitr;
  for (auto it = key1list.begin(); it != key1list.end(); ++it) {
    E & edge = (*(it))->get();
    if (edge.source().key() == key1 && edge.dest().key() == key2) {
      edgeitr = *(it);
      adjList.at(key1).erase(it);
      edgeExists = true;
      break;
    }
    if (!edge.directed()) {
      if (edge.source().key() == key2 && edge.dest().key() == key1) {
        edgeitr = *(it);
        adjList.at(key1).erase(it);
        edgeExists = true;
        break;
      }
    }
  }

  for (auto it = key2list.begin(); it != key2list.end(); ++it) {
    E & edge = (*(it))->get();
    if (edge.source().key() == key1 && edge.dest().key() == key2) {
      adjList.at(key2).erase(it);
      break;
    }
    if (!edge.directed()) {
      if (edge.source().key() == key2 && edge.dest().key() == key1) {
        adjList.at(key2).erase(it);
        break;
      }
    }
  }
  if (edgeExists) {
    edgeList.erase(edgeitr);
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  string key1 = *(it).source().key();
  string key2 = *(it).dest().key();
  removeEdge(key1,key2);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  std::list<edgeListIter> incident = adjList.at(key);

  //auto a = adjList.at(key).at(0);
  for (auto edge: incident) {
    edges.push_back(edge->get());
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  if (adjList.at(key1).size() < adjList.at(key2).size()) {
    for (auto edgeit: adjList.at(key1)) {
      E & edge = edgeit->get();
      if (edge.source().key() == key1 && edge.dest().key() == key2) {
        return true;
      }
      if (!edge.directed()) {
        if (edge.source().key() == key2 && edge.dest().key() == key1) {
          return true;
        }
      }
    }
  }
  else {
    for (auto edgeit: adjList.at(key2)) {
      E & edge = edgeit->get();
      if (edge.source().key() == key1 && edge.dest().key() == key2) {
        return true;
      }
      if (!edge.directed()) {
        if (edge.source().key() == key2 && edge.dest().key() == key1) {
          return true;
        }
      }
    }
  }
  return false;
}
