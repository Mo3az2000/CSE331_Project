import networkx as nx
import matplotlib.pyplot as plt

class GraphVisualization:

    def __init__(self):

        self.visual = []

    def visualize(self):

        G = nx.DiGraph()

        G.add_edges_from(self.visual)

        nx.draw_networkx(G, with_labels=True, edgecolors='blue', node_color='lightgray', node_size=1000, connectionstyle='arc3, rad = 0.1')

        plt.show()

    def addEdgesFromFile(self):

        f = open("edges.txt", 'r')

        for line in f:

            (e1,e2) = line.split()

            self.visual.append((e1, e2))

        print(self.visual)

# Driver code
G = GraphVisualization()
G.addEdgesFromFile()
G.visualize()
