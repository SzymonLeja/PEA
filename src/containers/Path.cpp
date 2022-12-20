//
// Created by kacper on 21.10.2022.
//

#include "DynamicArray.tpp"
#include "../../inc/containers/Path.h"

Path::Path() {
    path = new DynamicArray<int>();
    cost = 0;
}

Path::Path(const DynamicArray<int> &vertices, int cost) : cost(cost) {
    path = new DynamicArray<int>();

    for (int index = 0; index < vertices.getSize(); ++index) {
        path->addBack(vertices.at(index));
    }
}

Path::~Path() {
    delete path;
}

void Path::addVertex(int vertex, int vertexCost) {
    path->addBack(vertex);
    cost += vertexCost;
}

void Path::addVertex(int vertex) {
    path->addBack(vertex);
}

void Path::setCost(int totalCost) {
    this->cost = totalCost;
}

std::string Path::toString() {
    std::string path_str;

    for (int iterator = 0; iterator < path->getSize(); iterator++) {
        auto vertex_str = std::to_string(path->at(iterator));

        path_str.append(vertex_str)
                .append(" -> ");
    }
    path_str.append(" end")
            .append("\nTotal cost: ")
            .append(std::to_string(cost));

    return path_str;
}

int Path::getCost() {
    return cost;
}
