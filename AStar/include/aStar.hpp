#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "Graph.hpp"

namespace IA
{

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& rhs);

class Node
{
    private:
        int id_ = 0;
        float costSoFar_ = 0;
        float heuristic_ = 0;
        Node *parent_ = nullptr;

    public:
        Node(int id, float cost, float heur, Node *parent) :
                id_(id), costSoFar_(cost), heuristic_(heur), parent_(parent) {}

        int id()             const { return id_; }
        float g()            const { return costSoFar_; }
        float heuristic()    const { return heuristic_; }
        const Node* parent() const { return parent_; }

        friend bool operator<(const Node& lhs, const Node& rhs)  { return lhs.f() < rhs.f(); }
        friend bool operator>(const Node& lhs, const Node& rhs)  { return rhs < lhs; }
        friend bool operator==(const Node& lhs, const Node& rhs) { return lhs.f() == rhs.f(); }

    private:
        float f() const { return costSoFar_ + heuristic_; }
};


class aStar
{
    using priority_queue_t = std::priority_queue<Node, std::vector<Node>, std::greater<>>;
    using vector_ptr_t = std::vector<std::unique_ptr<Node>>;
    using location_t = int;

    private:
        const Graph graph_;
        std::vector<location_t> optimalPath_{};
        float pathDistance_ = 0.0;
        size_t generatedNodes_ = 0;
        vector_ptr_t visitedNodes_{};
        bool solution_ = true;

    public:
        explicit aStar(Graph G) : graph_(std::move(G)) {}

        void search(int start, int goal);
        void random_search(int start, int goal); 

        friend std::ostream& operator<<(std::ostream& os, const aStar& rhs);

        void clear();


    private:
        void extract_best_node(priority_queue_t& nodeQueue);
        void generate_children(priority_queue_t& nodeQueue);
        bool is_in_branch(location_t child, const Node* parent) const;
        void generate_path(const Node& current);

        void extract_first_random_node(int start);
        void extract_best_random_node(priority_queue_t& nodeQueue);

        float h(location_t current) const { return graph_.heuristic(current); }
        float c(location_t parent, location_t child) const { return graph_.get_cost(parent, child); }
};

void aStar::search(int start, int goal)
{
    priority_queue_t nodeQueue((std::greater<>()));

    nodeQueue.emplace(start, 0, h(start), nullptr);
    generatedNodes_++;

    while(!nodeQueue.empty() && nodeQueue.top().id() != goal)
    {
        extract_best_node(nodeQueue);
        generate_children(nodeQueue);
    }
    visitedNodes_.emplace_back(std::make_unique<Node>(nodeQueue.top()));
    pathDistance_ = nodeQueue.top().g();
    generate_path(nodeQueue.top());
}

void aStar::random_search(int start, int goal)
{
    Node startNode(start, 0, h(start), nullptr);

    visitedNodes_.emplace_back(std::make_unique<Node>(startNode));
    generatedNodes_++;

    extract_first_random_node(start);

    while(visitedNodes_.back()->id() != goal)
    {
        priority_queue_t nodeQueue((std::greater<>()));
        auto children_generated = [&nodeQueue] { return !nodeQueue.empty(); };

        generate_children(nodeQueue);

        if(children_generated())
        {
            extract_best_random_node(nodeQueue);
        }
        else
        {
            solution_ = false;
            return;
        }
    }

    pathDistance_ = visitedNodes_.back()->g();
    generate_path(*visitedNodes_.back().get());
}

void aStar::extract_first_random_node(int start)
{
    auto children = graph_.neighbors(start);
    generatedNodes_ += children.size();
    int randChild = children[rand() % children.size()];

    Node firstChildNode(randChild, c(start, randChild), h(randChild), visitedNodes_.back().get());
    visitedNodes_.emplace_back(std::make_unique<Node>(firstChildNode));
}

void aStar::extract_best_random_node(priority_queue_t& nodeQueue)
{
    Node firstBest = nodeQueue.top(); nodeQueue.pop();
    if(!nodeQueue.empty())
    {
        Node secondBest = nodeQueue.top(); nodeQueue.pop();
        int randChoose = rand() % 2;
        visitedNodes_.emplace_back(std::make_unique<Node>(randChoose == 1 ? firstBest : secondBest));
    }
    else
    {
        visitedNodes_.emplace_back(std::make_unique<Node>(firstBest));
    }
}

void aStar::clear()
{
    optimalPath_.clear();
    pathDistance_ = 0.0;
    generatedNodes_ = 0;
    visitedNodes_.clear();
    solution_ = true;
}

void aStar::extract_best_node(priority_queue_t& nodeQueue)
{
    visitedNodes_.emplace_back(std::make_unique<Node>(nodeQueue.top()));
    nodeQueue.pop();
}

void aStar::generate_children(priority_queue_t& nodeQueue)
{
    const auto& parent = visitedNodes_.back();
    for(const auto& child: graph_.neighbors(parent->id()))
    {
        if(!is_in_branch(child, parent.get()))
        {
            nodeQueue.emplace(child, parent->g() + c(parent->id(), child), h(child), parent.get());
            generatedNodes_++;
        }
    }
}

bool aStar::is_in_branch(location_t child, const Node *parent) const
{
    while(parent != nullptr && parent->id() != child)
    {
        parent = parent->parent();
    }
    return parent != nullptr;
}

void aStar::generate_path(const Node& current)
{
    if(current.parent() == nullptr)
    {
        optimalPath_.push_back(current.id());
    }
    else
    {
        generate_path(*current.parent());
        optimalPath_.push_back(current.id());
    }
}

std::ostream& operator<<(std::ostream& os, const aStar& rhs)
{
    os << "Graph Info: " << rhs.graph_.vertex() << " vertex | " << rhs.graph_.edge() << " edge" << std::endl;

    if(!rhs.solution_)
    {
        os << "No solution found!";
        return os;
    }

    os << "Optimal Path: " << rhs.optimalPath_ << std::endl;

    os << "Path length: " << rhs.pathDistance_ << std::endl;

    os << "Generated Nodes: " << rhs.generatedNodes_ << std::endl;

    os << "Visited Nodes: " << rhs.visitedNodes_.size() << std::endl;

    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& rhs)
{
    for(size_t i = 0; i < rhs.size() - 1; ++i)
    {
        os << rhs[i] + 1 << " -> ";
    }
    os << rhs.back() + 1;

    return os;
}

} //namespace IA