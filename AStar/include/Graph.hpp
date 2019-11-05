/**
 *
 * @class IA::Graph
 * @brief Simple Symmetric Graph Representation
 *
 * @details This class represents a simple graph storing cost
 * and heuristics, where C(i,j) = C(j,i) and C(i,i) = 0
 * @note Unreachable distance is represented by -1
 *
 * @author Javier Alonso Delgado
 *
 * @date 2019/16/10
 *
*/

#pragma once

#include <iostream>
#include <vector>

namespace IA
{

class Graph
{
    using vertex_t = int;
    using distance_t = float;
    const float INF = -1;

    private:
        size_t vertex_ = 0;                 /**< Number of vertex of the graph. */
        size_t edge_ = 0;                   /**< Number of edges of the graph. */
        std::vector<distance_t> cost_;       /**< Vector to store costs between nodes. */
        std::vector<distance_t> heuristic_;  /**< Vector to store heuristic of a node. */

    public:
        /**
         * @brief Default constructor
         * @details Initialize an empty graph
         */
        Graph() = default;

        /**
         * @brief Getter function for vertex_ parameter
         * @return Number of vertex
         */
        size_t vertex() const { return vertex_; }
        /**
         * @brief Getter function for edge_ parameter
         * @return Number of edges
         */
        size_t edge() const { return edge_; }
        /**
         * @brief Getter function for cost between 2 nodes
         * @param start -> Initial node
         * @param goal -> Next node
         * @see get_pos
         * @return Distance between nodes
         */
        distance_t get_cost(vertex_t start, vertex_t goal) const;
        /**
         * @brief Getter function for heuristic of one node to the end
         * @param current -> node
         * @return Heuristic of the node
         */
        distance_t heuristic(vertex_t current) const;

        /**
         * @brief Reads and initialize an empty graph
         * @param isCost -> File storing cost information
         * @param isHeuristic -> File storing heuristic information
         */
        void read(std::istream& isCost, std::istream& isHeuristic);
        /**
         * @brief Write the graph information
         * @param os -> Output stream
         * @param rhs -> Graph to be written out
         * @return Output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Graph& rhs);

        /**
         * @brief Getter for node's neighbors
         * @param current -> node
         * @return array of nodes
         */
        std::vector<vertex_t> neighbors(vertex_t current) const;

    private:
        /**
         * @brief Getter for array index
         * @details This function converts an upper diagonal symmetric matrix
         * index into an one dimensional array index
         * @param i -> row coordinate
         * @param j -> column coordinate
         * @return cost from node i to j
         */
        size_t get_pos(size_t i, size_t j) const;
};

void Graph::read(std::istream& isCost, std::istream& isHeuristic)
{
    float currentNumber;

    isCost >> vertex_;
    for(size_t i = 0; i < (vertex_*(vertex_-1)/2); ++i)
    {
        isCost >> currentNumber;
        if(currentNumber != -1) edge_++;
        cost_.emplace_back(currentNumber);
    }

    isHeuristic >> vertex_;
    for(size_t i = 0; i < vertex_; ++i)
    {
        isHeuristic >> currentNumber;
        heuristic_.emplace_back(currentNumber);
    }
}

std::ostream& operator<<(std::ostream& os, const Graph& rhs)
{
    os << rhs.vertex_ << std::endl;

    for(const auto& i: rhs.cost_)
    {
        os << i << '\n';
    }

    os << std::endl;
    os << rhs.vertex_ << std::endl;

    for(const auto& i: rhs.heuristic_)
    {
        os << i << '\n';
    }

    return os;
}

size_t Graph::get_pos(size_t i, size_t j) const
{
    return (vertex_*(vertex_-1)/2) - (vertex_-i)*((vertex_-i)-1)/2 + j - i - 1;
}

std::vector<Graph::vertex_t> Graph::neighbors(vertex_t current) const
{
    std::vector<vertex_t> neighbors;

    for(int i = 0; i < vertex_; ++i)
    {
        if(get_cost(current, i) != INF && i != current)
        {
            neighbors.push_back(i);
        }
    }
    neighbors.shrink_to_fit();

    return neighbors;
}

Graph::distance_t Graph::get_cost(vertex_t start, vertex_t goal) const
{
    if(goal < start) std::swap(start, goal);
    return (start == goal)? 0 : cost_.at(get_pos(start, goal));
}

Graph::distance_t Graph::heuristic(vertex_t current) const
{
    return heuristic_.at(current);
}

} //namespace IA


