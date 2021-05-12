#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <iostream>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */



template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::map<std::string, std::string> vertexLabels;
  std::map<std::pair<std::string, std::string>, std::string> edgeLabels;
  std::map<std::string,std::string> preds;
  std::list<std::string> path;
  for (auto p: vertexMap) {
    vertexLabels.emplace(p.first, "UNDISCOVERED");
  }
  for (auto p: edgeList) {
    Edge e = p.get();
    std::pair<std::string,std::string> s(e.source().key(), e.dest().key());
    std::pair<std::string,std::string> r(e.dest().key(), e.source().key());
    edgeLabels.emplace(s, "UNDISCOVERED");
    edgeLabels.emplace(r, "UNDISCOVERED");
  }

  //PRINTOUT
  //std::cout<<"vertexLabels:"<<std::endl;
  // for (auto p: vertexLabels) {
  //   std::cout<< " "<<p.first<< ": " <<p.second<<std::endl;
  // }
  // std::cout<<"edgeLabels:"<<std::endl;
  // for (auto p: edgeLabels) {
  //   std::cout<< " "<<p.first.first<<","<<p.first.second<< ": " <<p.second<<std::endl;
  // }

  string v = start;
  string label = "UNDISCOVERED";
  if (label == "UNDISCOVERED") {
    std::queue<string> q;
    vertexLabels.at(v) = "DISCOVERED";
    //std::cout<<"discovered vertex: " <<v<<std::endl;
    q.push(v);
    preds.emplace(v, "STARTPOINT");
    //std::cout<<"PUSHED: " << v <<std::endl;
    while (!q.empty()) {
      v = q.front();
      //std::cout<<"POPPED: " << v<<std::endl;
      q.pop();

      //std::cout<<"ADJACENTS FOR " << v <<": ";
      //geting adjacents of v
      std::vector<string> adjacents;
      std::list<E_byRef> iedges = incidentEdges(v);
      for (auto edgeref: iedges) {
        Edge m = edgeref.get();
        string source = m.source().key();
        string dest = m.dest().key();
        if (source != v && isAdjacent(source, v)) {
          //std::cout<< source<<", ";
          adjacents.push_back(source);
        }
        if (dest != v && isAdjacent(dest, v)) {
          //std::cout<< dest<<", ";
          adjacents.push_back(dest);
        }
      }
    //  std::cout<<std::endl;
      for (auto w: adjacents) {
        if (vertexLabels.at(w) == "UNDISCOVERED") {
          edgeLabels.at(std::pair<string,string>(v,w)) = "DISCOVERY";
          edgeLabels.at(std::pair<string,string>(w,v)) = "DISCOVERY";
          //std::cout<<"discovery edge: " <<v<<","<<w<<std::endl;
          vertexLabels.at(w) = "DISCOVERED";
          //std::cout<<"discovered vertex: " <<w<<std::endl;
          q.push(w);
          preds.emplace(w, v);
          //std::cout<<"PUSHED: " << w<<std::endl;
        }
        else if (edgeLabels.at(std::pair<string,string>(v,w)) == "UNDISCOVERED") {
          edgeLabels.at(std::pair<string,string>(v,w)) = "CROSS";
          edgeLabels.at(std::pair<string,string>(w,v)) = "CROSS";
          //std::cout<<"cross edge: " <<v<<","<<w<<std::endl;
        }
      }
    }
    //std::cout <<"EXITED WHILE LOOP" <<std::endl;
  }

  // std::cout<<"Preds:"<<std::endl;
  // for (auto p: preds) {
  //   std::cout<< " "<<p.first<<": " <<p.second<<std::endl;
  // }
  string cur = end;
  while (cur != "STARTPOINT") {
    path.push_front(cur);
    cur = preds.at(cur);
  }
  return path;
}





//WITH UNCONNECTED GRAPH TRAVERSAL

// template <class V, class E>
// std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
//   std::map<std::string, std::string> vertexLabels;
//   std::map<std::pair<std::string, std::string>, std::string> edgeLabels;
//   std::map<std::string,std::string> preds;
//   std::list<std::string> path;
//   for (auto p: vertexMap) {
//     vertexLabels.emplace(p.first, "UNDISCOVERED");
//   }
//   for (auto p: edgeList) {
//     Edge e = p.get();
//     std::pair<std::string,std::string> s(e.source().key(), e.dest().key());
//     std::pair<std::string,std::string> r(e.dest().key(), e.source().key());
//     edgeLabels.emplace(s, "UNDISCOVERED");
//     edgeLabels.emplace(r, "UNDISCOVERED");
//   }
//
//   //PRINTOUT
//   std::cout<<"vertexLabels:"<<std::endl;
//   for (auto p: vertexLabels) {
//     std::cout<< " "<<p.first<< ": " <<p.second<<std::endl;
//   }
//   std::cout<<"edgeLabels:"<<std::endl;
//   for (auto p: edgeLabels) {
//     std::cout<< " "<<p.first.first<<","<<p.first.second<< ": " <<p.second<<std::endl;
//   }
//
//   for (auto p: vertexLabels) {
//     string v = p.first;
//     std::cout<<"LOOP: " <<v<<std::endl;
//     string label = p.second;
//     if (label == "UNDISCOVERED") {
//       std::queue<string> q;
//       vertexLabels.at(v) = "DISCOVERED";
//       std::cout<<"discovered vertex: " <<v<<std::endl;
//       q.push(v);
//       preds.emplace(v, "STARTPOINT");
//       std::cout<<"PUSHED: " << v <<std::endl;
//       while (!q.empty()) {
//         v = q.front();
//         std::cout<<"POPPED: " << v<<std::endl;
//         q.pop();
//
//         std::cout<<"ADJACENTS FOR " << v <<": ";
//         //geting adjacents of v
//         std::vector<string> adjacents;
//         std::list<E_byRef> iedges = incidentEdges(v);
//         for (auto edgeref: iedges) {
//           Edge m = edgeref.get();
//           string source = m.source().key();
//           string dest = m.dest().key();
//           if (source != v && isAdjacent(source, v)) {
//             std::cout<< source<<", ";
//             adjacents.push_back(source);
//           }
//           if (dest != v && isAdjacent(dest, v)) {
//             std::cout<< dest<<", ";
//             adjacents.push_back(dest);
//           }
//         }
//         std::cout<<std::endl;
//         for (auto w: adjacents) {
//           if (vertexLabels.at(w) == "UNDISCOVERED") {
//             edgeLabels.at(std::pair<string,string>(v,w)) = "DISCOVERY";
//             edgeLabels.at(std::pair<string,string>(w,v)) = "DISCOVERY";
//             std::cout<<"discovery edge: " <<v<<","<<w<<std::endl;
//             vertexLabels.at(w) = "DISCOVERED";
//             std::cout<<"discovered vertex: " <<w<<std::endl;
//             q.push(w);
//             preds.emplace(w, v);
//             std::cout<<"PUSHED: " << w<<std::endl;
//           }
//           else if (edgeLabels.at(std::pair<string,string>(v,w)) == "UNDISCOVERED") {
//             edgeLabels.at(std::pair<string,string>(v,w)) = "CROSS";
//             edgeLabels.at(std::pair<string,string>(w,v)) = "CROSS";
//             std::cout<<"cross edge: " <<v<<","<<w<<std::endl;
//           }
//         }
//       }
//       std::cout <<"EXITED WHILE LOOP" <<std::endl;
//
//     }
//   }
//
//   std::cout<<"Preds:"<<std::endl;
//   for (auto p: preds) {
//     std::cout<< " "<<p.first<<": " <<p.second<<std::endl;
//   }
//   string cur = start
//   return path;
// }
