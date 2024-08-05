########################################################
#
# Name: Shayde Tamura
#
# Assignment: 5
#
# Instructor: Brook Conner
#
# Date: August 4, 2024
#
# File: scenario2.py
#
# Description:
#  Program that highlights interesting users that can be 
#  sorted by different attributes in a graph.
#
########################################################

import nextworkx as nx
import matplot.lib.pyplot as plt
from typing import Dict, Union, List
import pandas as pd
import numpy as np


class SocialMediaNetwork:
    def __init__(self):
        # Initialize an empty graph
        self.graph = nx.Graph()

    def add_user(self, user_name: str, attributes: Dict[str, Union[str, int]]):
        # Add a user node with attributes
        self.graph.add_node(user_name, type='user', **attributes)
    
    def add_post(self, post_id: str, content: str):
        # Add a post node with content
        self.graph.add_node(post_id, type='post', content=content)
    
    def add_authorship(self, user_name: str, post_id: str):
        # Add an edge from user to post to show the author
        self.graph.add_edge(user_name, post_id, relationship='authorship')

    def add_viewing(self, user_name: str, post_id: str):
        # Add an edge from user to post to show viewership
        self.graph.add_edge(user_name, post_id, relationship='viewing')

    def calculate_pagerank(self):
        # Calculate PageRank scores for all nodes
        pagerank_scores = nx.pagerank(self.graph)
        # Filter out only the user nodes' scores
        return {node: score for node, score in pagerank_scores.items() if self.graph.nodes[node]['type'] == 'user'}

    def filter_users_by_attributes(self, criteria: Dict[str, Union[str, int]]):
        filtered_users = []
        # Iterate over all nodes and filter users based on criteria
        for node, data in self.graph.nodes(data=True):
            if data['type'] == 'user':
                match = all(data.get(attr) == value for attr, value in criteria.items())
                if match:
                    filtered_users.append(node)
        return filtered_users

    def visualize_graph(self, highlight_nodes: List[str] = []):
        # Use a spring layout for the graph
        pos = nx.spring_layout(self.graph)
        node_colors = []
        node_sizes = []
        edge_colors = []

        for node, data in self.graph.nodes(data=True):
            # Color and size nodes based on type and whether they are highlighted
            if data['type'] == 'user':
                if node in highlight_nodes:
                    node_colors.append('red')
                    node_sizes.append(300)
                else:
                    node_colors.append('lightblue')
                    node_sizes.append(100)
            else:
                node_colors.append('lightgray')
                node_sizes.append(50)

        for edge, data in self.graph.edges(data=True):
            # Color edges based on relationship type
            if data['relationship'] == 'authorship':
                edge_colors.append('green')
            else:
                edge_colors.append('blue')

        # Draws the graph
        nx.draw(self.graph, pos, with_labels=True, node_color=node_colors, node_size=node_sizes, edge_color=edge_colors, alpha=0.6)
        plt.show()

# Example usage
network = SocialMediaNetwork()
network.add_user('john_doe', {'age': 30, 'gender': 'male', 'location': 'NY'})
network.add_user('jane_smith', {'age': 25, 'gender': 'female', 'location': 'CA'})
network.add_user('bob_jones', {'age': 35, 'gender': 'male', 'location': 'NY'})

network.add_post('post1', 'Loving the sunny weather today!')
network.add_post('post2', 'Had a great time at the beach.')
network.add_post('post3', 'Work is hectic, but I love my job.')

network.add_authorship('john_doe', 'post1')
network.add_authorship('jane_smith', 'post2')
network.add_authorship('bob_jones', 'post3')

network.add_viewing('jane_smith', 'post1')
network.add_viewing('bob_jones', 'post2')

pagerank_scores = network.calculate_pagerank()
print(f"PageRank scores: {pagerank_scores}")

criteria = {'gender': 'female'}
highlight_users = network.filter_users_by_attributes(criteria)
print(f"Filtered users by criteria: {highlight_users}")

network.visualize_graph(highlight_nodes=highlight_users)
