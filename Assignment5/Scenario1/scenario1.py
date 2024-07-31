########################################################
#
#  Name: Adam Graham
#
#  Assignment: 5
#
#  Instructor: Brook Conner
#
#  Date: July 31, 2024
#
#  File: scenario1.py
#
#  Description:
#   Program that searches through various social media posts
#   and sorts them by total views into a bar chart.
#
########################################################

import networkx as nx
import matplotlib.pyplot as plt
import heapq
import numpy as np


class User:
    def __init__(self, username):
        self.username = username
        self.connections = []
        self.authored_posts = []
        self.read_posts = []
        self.comments = []

    def view_post(self, post, batch_size):
        self.read_posts.append(post)
        post.add_view(batch_size)


class Post:
    def __init__(self, author, content):
        self.author = author
        self.content = content
        self.comments = []
        self.views = 0  # Initialize views as an integer

    def add_view(self, batch_size):
        self.views += batch_size  # Increment views by the batch size


def bfs(G, start_node):
    visited = set()
    queue = [start_node]
    pq = []
    count = 0  # tie-breaker count

    while queue:
        node = queue.pop(0)
        if node not in visited:
            visited.add(node)
            # If the node is a post
            if isinstance(node, Post):
                # Add the post and its view count to the priority queue
                heapq.heappush(pq, (-node.views, count, node))
                count += 1  # increment the tie-breaker count
            # Add unvisited neighbors to the queue
            for neighbor in G.neighbors(node):
                if neighbor not in visited:
                    queue.append(neighbor)
    return pq


def get_top_posts(pq):
    top_posts = heapq.nsmallest(10, pq)
    # Convert views back to positive
    top_posts = [(views * -1, post) for views, _, post in top_posts]
    return top_posts


def visualize_bar_chart_with_curve(top_posts):
    # Extract data
    post_names = [post.content for _, post in top_posts]
    view_counts = [views for views, _ in top_posts]

    # Convert view counts to a NumPy array
    x = np.arange(len(view_counts))  # x-axis: post indices
    y = np.array(view_counts)  # y-axis: view counts

    # Fit a polynomial curve (degree 2 for quadratic)
    coeffs = np.polyfit(x, y, deg=2)
    poly = np.poly1d(coeffs)

    # Generate x values for the fit
    x_fit = np.linspace(0, len(view_counts) - 1, 100)
    y_fit = poly(x_fit)

    # Create a bar chart
    plt.figure(figsize=(10, 6))
    plt.bar(post_names, view_counts, label='View Counts')

    # Plot the fitted curve
    plt.plot(x_fit, y_fit, color='red', linestyle='--', label='Fitted Curve')

    # Labels and title
    plt.xlabel('Posts')
    plt.ylabel('Number of Views (Thousands)')
    plt.title('Most Popular Posts')

    # Rotate x labels if they are long
    plt.xticks(rotation=45, ha='right')

    # Show legend
    plt.legend()

    # Show the plot
    plt.tight_layout()
    plt.show()


def main():
    # Create users and posts
    user1 = User('User1')
    user2 = User('User2')
    user3 = User('User3')
    user4 = User('User4')
    user5 = User('User5')
    user6 = User('User6')
    user7 = User('User7')
    user8 = User('User8')
    user9 = User('User9')
    user10 = User('User10')

    post1 = Post(user1, 'See you later')
    post2 = Post(user2, 'New video is out!')
    post3 = Post(user3, "What's up!")
    post4 = Post(user4, "Setting up account.")
    post5 = Post(user5, "Logging off for a bit")
    post6 = Post(user6, "Great show!")
    post7 = Post(user7, "Sorry")
    post8 = Post(user8, "You guys want something?")
    post9 = Post(user9, "New cool tech vid is up")
    post10 = Post(user10, "Watch this space")

    # Users view posts
    user1.view_post(post1, batch_size=32321)
    user2.view_post(post2, batch_size=32133)
    user3.view_post(post3, batch_size=90679)
    user4.view_post(post4, batch_size=55390)
    user5.view_post(post5, batch_size=10041)
    user6.view_post(post6, batch_size=85700)
    user7.view_post(post7, batch_size=67530)
    user8.view_post(post8, batch_size=2121)
    user9.view_post(post9, batch_size=4050)
    user10.view_post(post10, batch_size=110062)

    # Create a graph
    G = nx.Graph()

    # Add nodes to the graph
    G.add_node(user1)
    G.add_node(user2)
    G.add_node(user3)
    G.add_node(user4)
    G.add_node(user5)
    G.add_node(user6)
    G.add_node(user7)
    G.add_node(user8)
    G.add_node(user9)
    G.add_node(user10)

    G.add_node(post1)
    G.add_node(post2)
    G.add_node(post3)
    G.add_node(post4)
    G.add_node(post4)
    G.add_node(post6)
    G.add_node(post7)
    G.add_node(post8)
    G.add_node(post9)
    G.add_node(post10)

    # Add edges between users and their posts
    G.add_edge(user1, post1)
    G.add_edge(user2, post2)
    G.add_edge(user3, post3)
    G.add_edge(user4, post4)
    G.add_edge(user5, post5)
    G.add_edge(user6, post6)
    G.add_edge(user7, post7)
    G.add_edge(user8, post8)
    G.add_edge(user9, post9)
    G.add_edge(user10, post10)

    # User-user connections
    G.add_edge(user1, user2)
    G.add_edge(user2, user3)
    G.add_edge(user1, user4)
    G.add_edge(user4, user5)
    G.add_edge(user2, user6)
    G.add_edge(user5, user7)
    G.add_edge(user3, user8)
    G.add_edge(user8, user9)
    G.add_edge(user7, user10)

    pq = bfs(G, user1)
    top_posts = get_top_posts(pq)
    visualize_bar_chart_with_curve(top_posts)


# Execute main function
if __name__ == "__main__":
    main()
